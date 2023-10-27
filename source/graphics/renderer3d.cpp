#include "renderer3d.hpp"
#include "gldebug.hpp"
#include <glad/glad.h>
#include <glm/ext.hpp>

Renderer3D::Renderer3D(Window &window):
	m_window(window),
	m_mesh_shader("resources/shaders/mesh.vert.glsl", "resources/shaders/mesh.frag.glsl")
{
	m_valid = static_cast<bool>(m_mesh_shader);
}

Renderer3D::~Renderer3D()
{

}

void Renderer3D::clear( const Camera &camera )
{
	m_window.make_context_current();
	m_camera = camera;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
}

void Renderer3D::finish( )
{
	m_window.swap_buffers();
}
