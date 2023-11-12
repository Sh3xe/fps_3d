#include "state_menu.hpp"
#include "core/logger.hpp"

MenuState::MenuState(Application *app):
	m_renderer(app->window()),
	m_grass_volume( glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{1.0f, 1.0f}, GrassParameters{} ),
	State(app)
{
}

void MenuState::on_update( float s_dt )
{
	m_time += s_dt;
	m_camera.position = glm::vec3{cosf(m_time), 0.0f, sinf(m_time)} * (5.0f + 2.0f*cosf(m_time));	
	m_renderer.clear(m_camera);
	m_renderer.render(m_grass_volume);
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
	
	auto cubemap_ptr = std::make_shared<CubemapTexture>(
		"resources/textures/cubemap_default/px.jpg",
		"resources/textures/cubemap_default/nx.jpg",
		"resources/textures/cubemap_default/py.jpg",
		"resources/textures/cubemap_default/ny.jpg",
		"resources/textures/cubemap_default/pz.jpg",
		"resources/textures/cubemap_default/nz.jpg"
	);

	if( !(*cubemap_ptr) )
	{
		VV_WARN("cannot load cubemap texture");
	}
	else 
	{
		m_renderer.set_skybox( cubemap_ptr );
	}
}

void MenuState::on_shutdown()
{
}