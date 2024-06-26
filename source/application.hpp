#pragma once

#include "defines.hpp"
#include "core/settings.hpp"
#include "graphics/window.hpp"
//#include "graphics/renderer.hpp"

class State;

class Application
{
public:
	Application(const Settings &settings);
	~Application();

	bool is_valid() const { return m_valid; }

	void run();
	void set_state( State *state );

	Settings &settings() { return m_settings; }
	Window &window() { return m_window; }

private:
	void init_pending_state();

	bool m_running = true;
	bool m_valid = false;
	State *m_current_state = nullptr;
	State *m_pending_state = nullptr;
	bool m_state_require_init = false;
	Settings m_settings;
	Window m_window;
	// Renderer m_renderer;
};