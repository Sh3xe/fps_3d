#include "application.hpp"
#include "core/logger.hpp"
#include "game/state_base.hpp"
#include "core/timer.hpp"
#include "graphics/api/gldebug.hpp"

#include <chrono>
#include <thread>

using float_second = std::chrono::duration<float, std::ratio<1,1>>;

Application::Application( const Settings &settings ):
	m_window(settings.width, settings.height, settings.fullscreen),
	m_settings(settings)
{
	m_valid = m_window.is_valid();

	if(settings.fps == 0)
	{
		m_settings.fps = 30;
		VV_WARN("settings.fps = 0; Setting fps to 30");
	}
}

Application::~Application()
{
	// make sure that on_create() and on_shutdown() are alwase called in that order
	if(m_pending_state != nullptr)
	{
		if(m_state_require_init)
			m_pending_state->on_create();
		m_pending_state->on_shutdown();
		delete m_pending_state;
	}

	if(m_current_state != nullptr)
	{
		m_current_state->on_shutdown();
		delete m_current_state;
	}
}

void Application::run()
{
	// variables for delta time calculation
	// should not be 0 because this value will be used the first frame as the actual delta time
	float dt_second = 0.01f;
	float target_dt_second = 1.0f / (float)m_settings.fps;
	auto target_duration = float_second{target_dt_second};
	auto previous = std::chrono::system_clock().now();
	auto current = std::chrono::system_clock().now();

	while( !m_window.should_close() && m_running )
	{
		// state initialization
		if(m_state_require_init)
			init_pending_state();
		
		// delta time calculation
		previous = std::chrono::system_clock().now();

		// game update
		m_window.poll_events();
		m_current_state->on_update(dt_second);

		// delta time calculation
		current = std::chrono::system_clock().now();
		auto delta_time = current - previous;
		dt_second = float_second{delta_time}.count();

		// fps limitation
		if( m_settings.fps_cap && delta_time < target_duration )
		{
			std::this_thread::sleep_for( target_duration - delta_time );
			dt_second = target_dt_second;
		}
	}
}

void Application::init_pending_state()
{
	// should crash if not the case
	assert(m_pending_state != nullptr);

	if( m_current_state != nullptr )
	{
		m_current_state->on_shutdown();
		delete m_current_state;
	}

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
		delete m_pending_state;
		m_pending_state = nullptr;
	}

	m_pending_state = state;
	m_state_require_init = true;
}