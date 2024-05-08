#include "state_menu.hpp"
#include "core/logger.hpp"

MenuState::MenuState(Application *app):
	m_renderer(app->window()),
	m_grass_volume( glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{32.0f, 32.0f}, GrassParameters{} ),
	State(app)
{
}
   
MenuState::~MenuState()
{
	
}

void MenuState::on_update( float s_dt )
{
	// controller
	m_controller.update(m_app->window().get_input(), s_dt);
	m_camera = m_controller.get_cam();

	// drawing
	m_renderer.clear(m_camera);
	m_renderer.finish();
}

void MenuState::on_create()
{
	/*m_model.load_from_file("resources/models/backpack/backpack.obj");
	if( !m_model )
	{
		VV_WARN("impossible de charger le modèle");
	}*/
	
	auto cubemap_ptr = std::make_shared<CubemapTexture>(
		"resources/textures/cubemap_default/px.jpg",
		"resources/textures/cubemap_default/nx.jpg",
		"resources/textures/cubemap_default/py.jpg",
		"resources/textures/cubemap_default/ny.jpg",
		"resources/textures/cubemap_default/pz.jpg",
		"resources/textures/cubemap_default/nz.jpg"
	);

	if( !(cubemap_ptr->is_valid()) )
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