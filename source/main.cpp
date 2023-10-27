#include "application.hpp"
#include "game/state_menu.hpp"
#include "core/logger.hpp"

int main()
{
	Settings settings = load_settings_from_file("resources/config/settings.txt").value_or( Settings() );

	Application app {settings};

	if( !app )
	{
		VV_ERROR("Cannot create application");
		return 1;
	}

	app.set_state( new MenuState(&app) );
	app.run();

	return 0;
}