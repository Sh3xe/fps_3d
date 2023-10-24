#include "state_menu.hpp"
#include "core/logger.hpp"

MenuState::MenuState(Application *app):
	State(app)
{
}

void MenuState::on_update( float s_dt )
{
/*
	m_time += s_dt;
	m_camera.set_position( glm::vec3{cos(time), sin(time), 0.0} );
	
	m_renderer.begin_scene();
	m_renderer.push(m_crate);
	m_renderer.end_scene(m_camera);
*/
}

void MenuState::on_create()
{
	m_model.load_from_file("resources/models/backpack/backpack.obj");
	VV_INFO("salut");
/*
	m_crate = Model::load_from_file(path).value_or( Model::default_cube() );
*/
}

void MenuState::on_shutdown()
{
/*

*/
}