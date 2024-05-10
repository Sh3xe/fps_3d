#include "state_menu.hpp"
#include "core/logger.hpp"

MenuState::MenuState(Application *app):
	m_renderer(app->window()),
	m_2d_renderer(app->window()),
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
	m_2d_renderer.clear();
	m_renderer.clear(m_camera);

	m_2d_renderer.submit(m_rect, 5);
	m_2d_renderer.submit(m_text, 0);
	m_2d_renderer.finish();

	m_renderer.finish();
}

void MenuState::on_create()
{
	/*m_model.load_from_file("resources/models/backpack/backpack.obj");
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

	if( !(cubemap_ptr->is_valid()) )
	{
		VV_WARN("cannot load cubemap texture");
	}
	else 
	{
		m_renderer.set_skybox( cubemap_ptr );
	}

	m_rect.background_color = Color(200, 200, 200, 128);
	m_rect.border_color = Color(255, 255, 255, 255);
	m_rect.border_size = 2;
	m_rect.x = 540;
	m_rect.y = 260;
	m_rect.width = 200;
	m_rect.height = 200;

	m_text.color = Color(255, 255, 0, 255);
	m_text.content = "Bonjour!!";
	m_text.position = { 200, 200 };
	m_text.size = 50;
	*/

	m_menu.add_tab("Jeu");
	m_menu.add_tab("Parametres");
	m_menu.add_tab("Credits");

	m_menu["Credits"].add_widget(new ui::Text("Bonjour, je m'appelle Arnaud PELISSIER et c'est moi qui ai code ce jeu.."));

	m_menu["Jeu"].add_widget(new ui::Button("Jouer", [&]() {
		VV_TRACE("Le joueur à appuiyé sur 'jouer'");
		}));
}

void MenuState::on_shutdown()
{
}