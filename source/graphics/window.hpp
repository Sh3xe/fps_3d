#pragma once

#include <SDL2/SDL.h>
#include "core/input.hpp"

class Window
{
public:
	friend class Renderer;

	Window(uint32_t width, uint32_t height, bool fullscreen);
	~Window();
	
	operator bool() const { return m_valid; }

	bool should_close() const { return m_should_close; }
	void poll_events();
	Input &get_input() { return m_input; }
	void resize( uint32_t width, uint32_t height );

private:
	void make_context_current();

	bool initialize(uint32_t width, uint32_t height, bool fullscreen);

	bool m_valid = false;
	bool m_should_close = false;
	Input m_input;

	SDL_Window *m_window;
	SDL_GLContext m_context;
};