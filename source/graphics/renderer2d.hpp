#pragma once

#include "defines.hpp"

#include "window.hpp"
#include "api/shader.hpp"
#include "api/framebuffer.hpp"
#include "api/vertex_array.hpp"

#include <list>

class Renderer2D
{
public:
	struct StyledRectangle
	{
		StyledRectangle() = default;

		uint32_t width, height, x, y;
		uint32_t border_size;
		Color background_color;
		Color border_color;
	};

	Renderer2D( Window &window );

	inline bool is_valid() const { return m_valid; }

	void clear();

	void submit( const StyledRectangle &rect, int z_index );

	void finish();

private:
	void render_rectangle(const StyledRectangle& rect);

	void initialize_rect_vertex_array();

	enum class RenderPacketType
	{
		RECTANGLE, 
		// TEXT, 
	};

	struct RenderPacket
	{
		RenderPacket() = default;
		RenderPacketType type;
		int z_index;
		union
		{
			StyledRectangle styled_rectangle;
		};
	};

	Window& m_window;

	bool m_valid = false;
	Shader m_rect_shader;
	std::list<RenderPacket> m_render_packets;
	VertexArray m_rect_buffer;
};