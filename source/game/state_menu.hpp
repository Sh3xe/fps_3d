#pragma once

#include "state_base.hpp"
#include "graphics/model.hpp"

class MenuState: public State 
{
public:
	MenuState(Application *app);

	void on_update( float s_dt );
	void on_create();
	void on_shutdown();
	
private:
	Model m_model;
	int m_id;
};