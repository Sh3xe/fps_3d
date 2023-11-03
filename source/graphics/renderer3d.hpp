#pragma once

#include "api/shader.hpp"
#include "window.hpp"
#include "api/cubemap_texture.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "core/camera.hpp"
#include "skybox_data.hpp"

//TODO: UTILISER DES POINTEURS PARTAGEES POUR TOUS LES OBJETS OPENGL!!!!!!!

/*
#include "animated_model.hpp"
*/

class Renderer3D
{
public:
	Renderer3D(Window &window);
	~Renderer3D();

	inline operator bool() const { return m_valid; }

	void clear( const Camera &camera );
	void render( const Model &model );
	void render( const Mesh &mesh );
	void finish();
	void set_skybox( Ref<CubemapTexture> texture );

/*
	void render(animated_model); // animation and time shall be in animated_model
	void render(grass);
	void render(water)
*/

private:
	Window &m_window;

	Shader m_mesh_shader;
	Shader m_skybox_shader;

	Ref<CubemapTexture> m_skybox_texture;
	SkyboxModel m_skybox_model;
	Camera m_camera;
	glm::mat4 m_mvp;
	bool m_valid = false;

/*
	Shader m_animated_model_shader;
	Shader m_model_shader;
	Shader m_grass_shader;
	Shader m_water_shader;
	Shader m_postprocess_shader;
	RenderBuffer m_renderbuffer;
*/
};