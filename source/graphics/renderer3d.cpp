#include "renderer3d.hpp"
#include "api/gldebug.hpp"
#include <glad/glad.h>
#include <glm/ext.hpp>

static constexpr float cube_vertices[] =
{       
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

Renderer3D::Renderer3D(Window &window):
	m_window(window),
	m_mesh_shader("resources/shaders/mesh.vert.glsl", "resources/shaders/mesh.frag.glsl"),
	m_skybox_shader("resources/shaders/skybox.vert.glsl", "resources/shaders/skybox.frag.glsl"),
	m_grass_shader("resources/shaders/grass.vert.glsl", "resources/shaders/grass.frag.glsl")
{
	// initialize skybox data
	m_skybox_vertices.add_vertex_buffer(
		std::make_shared<VertexBuffer>( (void*)&cube_vertices, sizeof(cube_vertices)),
		{LayoutDescription(0, 3, 0, 3*4, LayoutDataType::FLOAT)} );
	m_valid = m_mesh_shader && m_skybox_shader && m_grass_shader;
}

Renderer3D::~Renderer3D()
{
}

void Renderer3D::clear( const Camera &camera )
{
	m_window.make_context_current();

	// precalculate camera matrices
	m_camera = camera;
	m_cam_view = camera.get_view();
	m_cam_proj = camera.get_projection();

	auto skybow_view = glm::mat4(glm::mat3(m_cam_view));

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// draw skybox
	if( m_skybox_texture != nullptr )
	{
		log_gl_errors();
		glDepthMask( GL_FALSE );

		m_skybox_shader.bind();
		m_skybox_vertices.bind();
		m_skybox_texture->bind();
		log_gl_errors();
		m_skybox_shader.set_mat4("u_view", glm::value_ptr(skybow_view));
		m_skybox_shader.set_mat4("u_projection", glm::value_ptr(m_cam_proj));
		m_skybox_shader.set_int("u_skybox_texture", 0);
		glActiveTexture(GL_TEXTURE0);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		log_gl_errors();

		m_skybox_texture->unbind();
		m_skybox_vertices.unbind();
		m_skybox_shader.unbind();
		log_gl_errors();

		glDepthMask( GL_TRUE );
	}
	else 
	{
		VV_WARN("No skybox attached to the renderer");
	}
}

void Renderer3D::render( const Model &model )
{
	log_gl_errors();

	auto mvp = m_camera.get_mvp();

	m_mesh_shader.bind();
	m_mesh_shader.set_mat4("u_mvp", glm::value_ptr(mvp));

	for(auto &mesh: model.m_meshes)
	{
		uint32_t spec_count = 1, diff_count = 1;
		for(uint32_t i = 0; i < mesh->m_textures.size(); ++i )
		{
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			std::string name = mesh->m_textures[i]->type;
			if(name == "diffuse")
				number = std::to_string(diff_count++);
			else if(name == "specular")
				number = std::to_string(spec_count++);

			m_mesh_shader.set_int(("u_texture_" + name + number).c_str(), i);
			mesh->m_textures[i]->texture.bind();
		}	
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(mesh->m_vao);
		glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		log_gl_errors();
	}
}

void Renderer3D::render( const Mesh &mesh )
{
	m_mesh_shader.bind();
	auto mvp = m_camera.get_mvp();
	m_mesh_shader.set_mat4("u_mvp", glm::value_ptr(mvp));

	uint32_t spec_count = 1, diff_count = 1;
	for(uint32_t i = 0; i < mesh.m_textures.size(); ++i )
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = mesh.m_textures[i]->type;
		if(name == "diffuse")
			number = std::to_string(diff_count++);
		else if(name == "specular")
			number = std::to_string(spec_count++);

		m_mesh_shader.set_int(("u_texture_" + name + number).c_str(), i);
		mesh.m_textures[i]->texture.bind();
	}	
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(mesh.m_vao);
	glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer3D::render( const GrassVolume &grass )
{
	auto mvp = m_camera.get_mvp();
	m_grass_shader.bind();
	m_grass_shader.set_mat4("u_mvp", glm::value_ptr(mvp));

	auto col = grass.m_params.bottom_color;

	glm::vec3 colors[4] = {grass.m_params.bottom_color, grass.m_params.base_color, grass.m_params.top_color, grass.m_params.tip_color};

	m_grass_shader.set_vec3_arr("u_colors[4]", (float*)colors, 4);

	grass.m_vertex_array.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 33, GL_UNSIGNED_INT, 0, grass.m_positions.size());
	m_grass_shader.unbind();
}

void Renderer3D::finish( )
{
	m_window.swap_buffers();
}

void Renderer3D::set_skybox( const Ref<CubemapTexture> &texture )
{
	m_skybox_texture = texture;
}