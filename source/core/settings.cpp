#include "settings.hpp"

#include "core/config.hpp"
#include "core/logger.hpp"

Opt<Settings> load_settings_from_file( const std::string &path )
{
	Config cfg { path };
	if( !cfg ) return {};

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
		VV_DEBUG( e.what() );
		VV_WARN("Fichier de configuration invalide");
	}

	return settings;
}