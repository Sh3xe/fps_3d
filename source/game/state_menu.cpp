#include "state_menu.hpp"
#include "core/logger.hpp"

MenuState::MenuState(Application *app):
	m_renderer(app->window()),
	State(app)
{
}

void MenuState::on_update( float s_dt )
{
	m_time += s_dt;
	m_camera.position = glm::vec3{cosf(m_time) * 4.0f, 0.0f, sinf(m_time) * 4.0f,};	
	m_renderer.clear(m_camera);
	m_renderer.render(m_model);
	m_renderer.finish();
}

void MenuState::on_create()
{
	m_model.load_from_file("resources/models/backpack/backpack.obj");
	if( !m_model )
	{
		VV_WARN("impossible de charger le modèle");
	}
}

void MenuState::on_shutdown()
{
/*

*/
}