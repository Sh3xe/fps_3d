#include "mesh.hpp"
#include "api/gldebug.hpp"
#include <glad/glad.h>
#include <assert.h>

Mesh::Mesh(
	const std::vector<Vertex> &vertices,
	const std::vector<uint32_t> &indices,
	const std::vector<Ref<NamedTexture>> &textures ):
	m_vertices(vertices),
	m_indices(indices),
	m_textures(textures)
{
	setup();
}

Mesh::~Mesh()
{
	VV_TRACE("~Mesh");
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_vbo);
}

void Mesh::setup()
{
	if( m_vertices.size() == 0 || m_indices.size() == 0 )
	{
		VV_WARN("Initialization of empty mesh");
	}

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_ebo);
	glGenBuffers(1, &m_vbo);
	log_gl_errors();

	glBindVertexArray(m_vao);

	// Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	// Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Data layout

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, px));
	// normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nx));
	// tangent
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tx));
	// bitangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, btx));
	// texture
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

	glBindVertexArray(0);
}