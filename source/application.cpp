#include "application.hpp"
#include "core/logger.hpp"
#include "game/state_base.hpp"

#include <chrono>
#include <thread>


Application::Application( const Settings &settings ):
	m_window(settings.width, settings.height, settings.fullscreen),
	m_settings(settings)
{
	m_valid = static_cast<bool>(m_window);
}

Application::~Application()
{
	// make sure that on_create() and on_shutdown() are alwase called in that order
	if(m_pending_state != nullptr)
	{
		if(m_state_require_init)
			m_pending_state->on_create();
		m_pending_state->on_shutdown();
	}

	if(m_current_state != nullptr)
		m_current_state->on_shutdown();
}

void Application::run()
{
	if( m_current_state == nullptr )
	{
		VV_WARN("Application started with no state attached");
	}

	float s_dt = 0.01f;

	while( !m_window.should_close() )
	{
		if(m_state_require_init)
			init_pending_state();
		
		m_window.get_input().get_key(SDL_SCANCODE_A);
		m_window.poll_events();
		m_current_state->on_update(s_dt);

		std::this_thread::sleep_for( std::chrono::milliseconds(250) );
	}
}

void Application::init_pending_state()
{
	// should crash if not the case
	assert(m_pending_state != nullptr);

	if( m_current_state != nullptr )
		m_current_state->on_shutdown();

	m_current_state = m_pending_state;
	m_pending_state = nullptr;
	m_current_state->on_create();
	
	m_state_require_init = false;
}

void Application::set_state( State *state )
{
	// handle the case where set_state is called two times within a frame
	if( m_pending_state != nullptr )
	{
		VV_WARN("Two set_state() within one frame");
		m_pending_state->on_create();
		m_pending_state->on_shutdown();
		m_pending_state = nullptr;
	}

	m_pending_state = state;
	m_state_require_init = true;
}