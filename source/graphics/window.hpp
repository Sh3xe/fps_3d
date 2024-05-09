#pragma once

#include "sdl_include.hpp"
#include "core/input.hpp"

class Window
{
public:
	friend class Renderer3D;
	friend class Renderer2D;

	Window(uint32_t width, uint32_t height, bool fullscreen);
	~Window();
	
	inline bool is_valid() const { return m_valid; }

	uint32_t get_width() const { return m_width; }
	uint32_t get_height() const { return m_height; }

	bool should_close() const { return m_should_close; }
	void poll_events();
	Input &get_input() { return m_input; }
	void resize( uint32_t width, uint32_t height );

private:
	void make_context_current();
	void swap_buffers();

	bool initialize(uint32_t width, uint32_t height, bool fullscreen);

	bool m_valid = false;
	bool m_should_close = false;
	uint32_t m_width{ 0 }, m_height{ 0 };
	Input m_input;

	SDL_Window *m_window;
	SDL_GLContext m_context;
};