#pragma once

#include "defines.hpp"

#include "core/camera.hpp"
#include "api/shader.hpp"
#include "api/cubemap_texture.hpp"
#include "api/vertex_array.hpp"

#include "window.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "grass.hpp"

//TODO: UTILISER DES POINTEURS PARTAGEES POUR TOUS LES OBJETS OPENGL!!!!!!!

/*
#include "animated_model.hpp"
*/

class Renderer3D
{
public:
	Renderer3D(Window &window);
	~Renderer3D();

	inline bool is_valid() const { return m_valid; }

	void clear( const Camera &camera );
	void render( const Model &model );
	void render( const Mesh &mesh );
	void render( const GrassVolume &grass );
	void finish();
	void set_skybox( const Ref<CubemapTexture> &texture );

/*
	void render(animated_model); // animation and time shall be in animated_model
	void render(grass);
	void render(water)
*/

private:
	Window &m_window;

	Shader m_mesh_shader;
	Shader m_skybox_shader;
	Shader m_grass_shader;

	// skybox data
	Ref<CubemapTexture> m_skybox_texture;
	VertexArray m_skybox_vertices;

    // grass data
	Camera m_camera;
	glm::mat4 m_mvp;
	bool m_valid = false;
/*
	Shader m_animated_model_shader;
	Shader m_water_shader;
	Shader m_postprocess_shader;
	RenderBuffer m_renderbuffer;
*/
};