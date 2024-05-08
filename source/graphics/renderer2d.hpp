#pragma once

#include "defines.hpp"
#include "api/shader.hpp"

struct StyledRectangle
{
	uint32_t width, height, x, y;
	uint32_t border_size, border_radius;
	Color background_color;
	Color border_color;
};

class Renderer2D
{
public:
	Renderer2D();

	inline bool is_valid() const { return m_valid; }

	void clear();

	void submit( const StyledRectangle &rect, int z_index );

	void finish();

private:
	bool m_valid = false;
	Shader m_rect_shader;
};