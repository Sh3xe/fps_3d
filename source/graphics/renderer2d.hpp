#pragma once

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "defines.hpp"

#include "window.hpp"
#include "api/shader.hpp"
#include "api/framebuffer.hpp"
#include "api/vertex_array.hpp"
#include "api/texture2d.hpp"

#include <list>
#include <map>
#include <string>

class Renderer2D
{
public:
	struct StyledRectangle
	{
		uint32_t width, height, x, y;
		uint32_t border_size;
		Color background_color;
		Color border_color;
	};

	struct Text
	{
		std::string content;
		Color color;
		uint32_t size;
	};

	Renderer2D( Window &window );
	~Renderer2D();

	inline bool is_valid() const { return m_valid; }

	void clear();

	void submit( const StyledRectangle &rect, int z_index );

	void submit(const Text& text, int z_index);

	void finish();

private:
	void render_rectangle(const StyledRectangle& rect);

	void render_text(const Text& text);

	void initialize_rect_vertex_array();

	bool initialize_character_map();

	enum class RenderPacketType
	{
		RECTANGLE, 
		TEXT 
	};

	struct RenderPacket
	{
		RenderPacket(const StyledRectangle& styled_rectangle, int z_index):
			z_index(z_index),
			type(RenderPacketType::RECTANGLE),
			styled_rectangle(styled_rectangle)
		{
		}

		RenderPacket(const Text& text, int z_index):
			z_index(z_index),
			type(RenderPacketType::TEXT),
			text(text)
		{
		}

		~RenderPacket() {}

		RenderPacketType type;
		int z_index;
		union
		{
			StyledRectangle styled_rectangle;
			Text text;
		};
	};

	struct Character
	{
		Ref<Texture2D> texture;
		glm::ivec2 size;
		glm::ivec2 bearing;
		uint32_t advance;
	};

	bool m_valid = false;
	Window& m_window;
	std::list<RenderPacket> m_render_packets;

	Shader m_rect_shader;
	VertexArray m_rect_buffer;

	Shader m_text_shader;
	uint32_t m_text_vao, m_text_vbo;
	std::map<char, Character> m_charmap;
};