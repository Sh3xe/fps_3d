#pragma once

#include "defines.hpp"
#include <string>

struct Settings
{
	uint32_t width = 1920;
	uint32_t height = 1080;
	bool fps_cap = true;
	bool fullscreen = false;
	uint32_t fps = 30;
	float sensitivity = 0.05f;
	std::string title = "FPS";
};

Opt<Settings> load_settings_from_file( const std::string &path );