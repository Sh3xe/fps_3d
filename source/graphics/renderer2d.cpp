#include "renderer2d.hpp"
#include <glad/glad.h>
#include <algorithm>

Renderer2D::Renderer2D(Window &window):
	m_rect_shader("resources/shaders/rectangle.vert.glsl", "resources/shaders/rectangle.frag.glsl"),
	m_window(window)
{
	initialize_rect_vertex_array();
	m_valid = m_rect_shader.is_valid();
}

void Renderer2D::clear()
{
	// TODO: comment gérer les contextes?
	m_window.make_context_current();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	m_render_packets.clear();

	FrameBuffer::unbind();
}

void Renderer2D::submit( const StyledRectangle &rect, int z_index )
{
	Renderer2D::RenderPacket packet;
	packet.type = Renderer2D::RenderPacketType::RECTANGLE;
	packet.z_index = z_index;
	packet.styled_rectangle = rect;
	m_render_packets.push_back(packet);
}

void Renderer2D::render_rectangle(const StyledRectangle& rect)
{
	m_rect_shader.bind();

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

	m_rect_shader.unbind();
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
