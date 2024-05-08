#include "renderer2d.hpp"

Renderer2D::Renderer2D():
	m_rect_shader("resources/shaders/rect.vert.glsl", "resources/shaders/rect.vert.glsl")
{
	m_valid = m_rect_shader.is_valid();
}

void Renderer2D::clear()
{

}

void Renderer2D::submit( const StyledRectangle &rect, int z_index )
{

}

void Renderer2D::finish()
{

}