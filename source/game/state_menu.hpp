#pragma once

#include "state_base.hpp"
#include "ui/menu.hpp"

class MenuState: public State 
{
public:
	MenuState(Application *app);
	~MenuState();

	void on_update( float s_dt );
	void on_create();
	void on_shutdown();
	
private:
	ui::Menu m_menu;
	Renderer2D m_renderer;
};