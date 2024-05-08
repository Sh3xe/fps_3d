#pragma once

#include "state_base.hpp"
#include "graphics/model.hpp"
#include "graphics/renderer3d.hpp"
#include "core/camera.hpp"
#include "graphics/grass.hpp"
#include "player_controller.hpp"

class MenuState: public State 
{
public:
	MenuState(Application *app);
	~MenuState();

	void on_update( float s_dt );
	void on_create();
	void on_shutdown();
	
private:
	PlayerController m_controller;
	Renderer3D m_renderer;
	Model m_model;
	float m_time {0.0f};
	Camera m_camera;
};