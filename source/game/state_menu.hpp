#pragma once

#include "state_base.hpp"
#include "graphics/model.hpp"
#include "graphics/renderer3d.hpp"
#include "graphics/renderer2d.hpp"
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
	Renderer2D::StyledRectangle m_rect;
	Renderer2D::Text m_text;

	PlayerController m_controller;
	Renderer3D m_renderer;
	Renderer2D m_2d_renderer;
	Model m_model;
	float m_time {0.0f};
	Camera m_camera;
};