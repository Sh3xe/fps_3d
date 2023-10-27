#include "window.hpp"
#include "core/logger.hpp"
#include <stb_image.h>
#include <glad/glad.h>

static bool is_graphics_initialized = false;

bool Window::initialize(uint32_t width, uint32_t height, bool fullscreen)
{
	//TODO: mettre SDL_Init et gladLoad... dans une fonction init_graphics et l'appeler une seule fois, SDL_GL_Context et SDL_Window peuvent êtres créer plusieurs fois...
	assert(!is_graphics_initialized);

	int res = SDL_Init( SDL_INIT_EVERYTHING );
	if( res != 0 )
	{
		VV_ERROR("Cannot initialize SDL:\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_window = SDL_CreateWindow(
		"FPS Data",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL | ( fullscreen ? SDL_WINDOW_FULLSCREEN: 0 )
	);

	m_context = SDL_GL_CreateContext(m_window);

	if(!gladLoadGLLoader( (GLADloadproc)SDL_GL_GetProcAddress ))
	{
		VV_ERROR("Cannot load GLAD (OpenGL)");
		return false;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height );

	is_graphics_initialized = true;
	VV_DEBUG("Initialized graphics");
	stbi_set_flip_vertically_on_load(true);
	return true;
}

Window::Window(uint32_t width, uint32_t height, bool fullscreen)
{
	m_valid = initialize(width, height, fullscreen);
}

Window::~Window()
{
	VV_DEBUG("Shutting down window");
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::poll_events()
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		switch(event.type)
		{
		case SDL_QUIT:
			m_should_close = true;
			break;
		case SDL_KEYDOWN:
			//VV_INFO("handle_keydown", event.key.keysym.scancode);
			m_input.handle_keydown(event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			//VV_INFO("handle_keyup");
			m_input.handle_keyup(event.key.keysym.scancode);
			break;
		default: break;
		}
	}
}

void Window::make_context_current()
{
	SDL_GL_MakeCurrent(m_window, m_context);
}

void Window::resize( uint32_t width, uint32_t height )
{
	glViewport(0, 0, width, height );
}

void Window::swap_buffers()
{
	SDL_GL_SwapWindow(m_window);
}