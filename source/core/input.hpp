#pragma once

#include <SDL.h>

#include "vvtypes.hpp"
#include <string>
#include <functional>
#include <map>

enum class MouseButton
{
	left,
	right,
	middle,
	x1,
	x2,
	none
};

using Callback = std::function< void( MouseButton ) >;

class Input
{
public:
	inline bool get_key(SDL_Scancode key) { return m_keys[key]; }
	std::pair<bool, bool> get_mouse_state();

	void handle_keyup( SDL_Scancode key );
	void handle_keydown( SDL_Scancode key );
	void set_mouse_pos(int32_t x, int32_t y);
	void add_mouse_pos(int32_t x, int32_t y);
	void set_mouse_state( bool rc, bool lc );

	inline const int32_t get_mouse_x() const { return m_mouse_x; }
	inline const int32_t get_mouse_y() const { return m_mouse_y; }

	void on_click( MouseButton b );
	void add_click_callback( const Callback &f, const std::string &name );
	void remove_click_callback( const std::string &name );

private:
	std::map<SDL_Scancode, bool> m_keys;
	std::map<std::string, Callback> m_callbacks;
	std::pair<bool, bool> m_click_state;
	int32_t m_mouse_x = 0.0f, m_mouse_y = 0.0f;
};

MouseButton button_from_sdl_enum( uint8_t sdl_enum );