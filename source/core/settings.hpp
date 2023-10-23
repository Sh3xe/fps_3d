#pragma once

#include "vvtypes.hpp"
#include <string>

struct Settings
{
	int width = 1920;
	int height = 1080;
	bool fps_cap = true;
	bool fullscreen = false;
	int fps = 30;
	float sensitivity = 0.05f;
	std::string title = "FPS_Data";
};

Opt<Settings> load_settings_from_file( const std::string &path );