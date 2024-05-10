#include "renderer2d.hpp"
#include <glad/glad.h>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer2D::Renderer2D(Window &window):
	m_rect_shader("resources/shaders/rectangle.vert.glsl", "resources/shaders/rectangle.frag.glsl"),
	m_text_shader("resources/shaders/text.vert.glsl", "resources/shaders/text.frag.glsl"),
	m_window(window)
{
	initialize_rect_vertex_array();
	bool charmap_loaded = initialize_character_map();
	m_valid = m_rect_shader.is_valid() && charmap_loaded && m_text_shader.is_valid();
}

Renderer2D::~Renderer2D()
{
	glDeleteBuffers(1, &m_text_vbo);
	glDeleteVertexArrays(1, &m_text_vao);
}

void Renderer2D::clear()
{
	// TODO: comment gérer les contextes?
	m_window.make_context_current();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	m_render_packets.clear();
	m_projection = glm::ortho(0.0f, (float)m_window.get_width(), 0.0f, (float)m_window.get_height());

	m_text_shader.bind();
	m_text_shader.set_mat4("projection", glm::value_ptr(m_projection));
	m_text_shader.unbind();

	FrameBuffer::unbind();
}

void Renderer2D::submit( const StyledRectangle &rect, int z_index )
{
	m_render_packets.emplace_back(rect, z_index);
}

void Renderer2D::submit(const Text& text, int z_index)
{
	m_render_packets.emplace_back(text, z_index);
}

void Renderer2D::render_rectangle(const StyledRectangle& rect)
{
	m_rect_shader.bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// converts between pixel coordinates and Normalized Device Coordinates ([-1,1]*[-1,1])
	float ndc_border_size_x = (2.0f * (float)rect.border_size) / (float)m_window.get_width();
	float ndc_border_size_y = (2.0f * (float)rect.border_size) / (float)m_window.get_height();

	float ndc_pos_x = ((float)rect.x / (float)m_window.get_width()) * 2.0f - 1.0f;
	float ndc_pos_y = ((float)rect.y / (float)m_window.get_height()) * 2.0f - 1.0f;

	// these are the "scale factors" that converts [0,1]^2 rect into [width, height] rect in NDC
	float ndc_size_x = ((float)rect.width / (float)m_window.get_width()) * 2.0f;
	float ndc_size_y = ((float)rect.height / (float)m_window.get_height()) * 2.0f;

	// pass the values to the shader
	m_rect_shader.set_vec4("u_params.bg_color",
		(float)rect.background_color.r / 255.0f,
		(float)rect.background_color.g / 255.0f,
		(float)rect.background_color.b / 255.0f,
		(float)rect.background_color.a / 255.0f
	);

	m_rect_shader.set_vec4("u_params.border_color",
		(float)rect.border_color.r / 255.0f,
		(float)rect.border_color.g / 255.0f,
		(float)rect.border_color.b / 255.0f,
		(float)rect.border_color.a / 255.0f
	);

	m_rect_shader.set_vec2("u_params.border", ndc_border_size_x, ndc_border_size_y);

	m_rect_shader.set_vec2("u_params.position", ndc_pos_x, ndc_pos_y);
	m_rect_shader.set_vec2("u_params.size", ndc_size_x, ndc_size_y);

	// render the rectangle
	m_rect_buffer.bind();
	glDisable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_BLEND);
	m_rect_shader.unbind();
}

void Renderer2D::render_text(const Text& text)
{
	m_text_shader.bind();

	m_text_shader.set_vec3("texture_color", text.color.r, text.color.g, text.color.b);
	m_text_shader.set_int("text", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_text_vao);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float current_x = text.position.x;
	float current_y = text.position.y;
	float scale = (float)text.size / (float)pixel_height;

	for (unsigned char c : text.content)
	{
		// find the graphical data associated with a given char
		auto char_it = m_charmap.find(c);
		Character graphic_char;

		if (char_it == m_charmap.end())
		{
			VV_WARN("Cannot load the char with id '", (uint32_t)c, "'");
			graphic_char = m_charmap[(unsigned char)'a'];
		}
		else
		{
			graphic_char = char_it->second;
		}

		float xpos = current_x + graphic_char.bearing.x * scale;
		float ypos = current_y - (graphic_char.size.y - graphic_char.bearing.y) * scale;
		float width = graphic_char.size.x * scale;
		float height = graphic_char.size.y * scale;

		// set the texture
		float vertices[4 * 6] = {
			xpos      , ypos+height , 0.0f, 0.0f,
			xpos+width, ypos+height , 1.0f, 0.0f,
			xpos+width, ypos        , 1.0f, 1.0f,
			xpos      , ypos+height , 0.0f, 0.0f,
			xpos+width, ypos        , 1.0f, 1.0f,
			xpos      , ypos        , 0.0f, 1.0f,
		};

		graphic_char.texture->bind();

		glBindBuffer(GL_ARRAY_BUFFER, m_text_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		// draw the quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		current_x += scale * ((graphic_char.advance) >> 6);
	}

	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer2D::finish()
{
	m_render_packets.sort([&](const Renderer2D::RenderPacket& left, const Renderer2D::RenderPacket& right) -> bool {
		return left.z_index < right.z_index;
		});

	for (const auto& packet : m_render_packets)
	{
		switch (packet.type)
		{
		case Renderer2D::RenderPacketType::RECTANGLE:
			render_rectangle(packet.styled_rectangle);
			break;
		case RenderPacketType::TEXT:
			render_text(packet.text);
			break;
		default:
			assert(false && "packet.type n'est pas une valeure prise en charge");
			break;
		}
	}

	FrameBuffer::unbind();
	m_render_packets.clear();
}

void Renderer2D::initialize_rect_vertex_array()
{
	static constexpr float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	constexpr size_t indices_count = 6;

	static constexpr uint32_t indices[indices_count] = {
		0, 1, 3,
		0, 3, 2
	};

	auto vertex_buffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	auto index_buffer = std::make_shared<IndexBuffer>(indices, indices_count);
	m_rect_buffer.add_vertex_buffer(vertex_buffer, {
		LayoutDescription(0, 2, 0, 2*sizeof(float), LayoutDataType::FLOAT)
		});
	m_rect_buffer.set_index_buffer(index_buffer);
}

bool Renderer2D::initialize_character_map()
{
	// initializes the freetype library
	FT_Library freetype_lib;
	FT_Error err = FT_Init_FreeType(&freetype_lib);

	if (err)
	{
		VV_ERROR("Cannot load the freetype library");
		return false;
	}

	// load a font
	FT_Face face;
	err = FT_New_Face(freetype_lib, "../resources/fonts/cmunrm.ttf", 0, &face);

	if (err)
	{
		VV_ERROR("Cannot load the \"../resources/fonts/cmunrm.ttf\"");
		return false;
	}

	// store all the necessary characters
	FT_Set_Pixel_Sizes(face, 0, pixel_height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; ++c)
	{
		err = FT_Load_Char(face, c, FT_LOAD_RENDER);

		if (err)
		{
			VV_WARN("Cannot load '", c, "' character");
		}

		Character current_char;
		current_char.texture = Ref<Texture2D>(new Texture2D());

		current_char.texture->create_from_memory(
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			GL_RED,
			(face->glyph->bitmap.buffer)
		);

		current_char.advance = face->glyph->advance.x;
		current_char.size.x = face->glyph->bitmap.width;
		current_char.size.y = face->glyph->bitmap.rows;
		current_char.bearing.x = face->glyph->bitmap_left;
		current_char.bearing.y = face->glyph->bitmap_top;

		m_charmap.insert(std::make_pair(c, current_char) );
	}

	FT_Done_Face(face);
	FT_Done_FreeType(freetype_lib);

	// create the open objects for the quad
	glGenVertexArrays(1, &m_text_vao);
	glGenBuffers(1, &m_text_vbo);
	glBindVertexArray(m_text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_text_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}
