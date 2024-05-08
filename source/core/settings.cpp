#include "settings.hpp"

#include "core/config.hpp"
#include "core/logger.hpp"

Opt<Settings> load_settings_from_file( const std::string &path )
{
	Config cfg { path };
	if( !cfg.is_valid() )
	{
		VV_ERROR("Cannot load settings at ", path);
	}

	Settings settings;
	try
	{
		settings.fps_cap = cfg.get_bool("fps_cap");
		settings.fullscreen = cfg.get_bool("fullscreen");

		settings.fps = cfg.get_int("fps");
		settings.width = cfg.get_int("window_width");
		settings.height = cfg.get_int("window_height");
	
		settings.title = cfg.get_str("title");
	
		settings.sensitivity = cfg.get_float("sensitivity");
	}
	catch(const std::exception& e)
	{
		VV_WARN("Fichier de configuration invalide");
		VV_DEBUG( e.what() );
	}

	VV_INFO("Settings:");
	VV_INFO("FPS=", settings.fps);
	VV_INFO("FPS_CAP=", settings.fps_cap);
	VV_INFO("FULLSCREEN=", settings.fullscreen);
	VV_INFO("WIDTH=", settings.width);
	VV_INFO("HEIGHT=", settings.height);
	VV_INFO("SENSITIVITY=", settings.sensitivity);
	VV_INFO("TITLE=", settings.title);

	return settings;
}