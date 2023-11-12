#pragma once

#include "vvtypes.hpp"
#include "api/texture2d.hpp"
// #include "api/vertex_array.hpp"
#include <vector>

struct NamedTexture
{
	Texture2D texture;
	std::string type;
};

struct Vertex
{
	float px, py, pz;
	float nx, ny, nz;
	float tx, ty, tz;
	float btx, bty, btz;
	float tex, tey;
};

class Mesh
{
public:
	friend class Renderer3D;
	friend class Model;

	Mesh(
		const std::vector<Vertex> &vertices,
		const std::vector<uint32_t> &indices,
		const std::vector<Ref<NamedTexture>> m_textures );

	~Mesh();

private:
	/*
	static std::vector<LayoutDescription> mesh_description()
	{
		return {
			LayoutDescription{0, 3, offsetof(Vertex, px), sizeof(Vertex),LayoutDataType::FLOAT},
			LayoutDescription{1, 3, offsetof(Vertex, nx), sizeof(Vertex),LayoutDataType::FLOAT},
			LayoutDescription{2, 3, offsetof(Vertex, tx), sizeof(Vertex),LayoutDataType::FLOAT},
			LayoutDescription{3, 3, offsetof(Vertex, btx), sizeof(Vertex),LayoutDataType::FLOAT},
			LayoutDescription{4, 2, offsetof(Vertex, tex), sizeof(Vertex),LayoutDataType::FLOAT},
		};
	} */

	void setup();

	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	std::vector<Ref<NamedTexture>> m_textures;
	uint32_t m_vao, m_vbo, m_ebo;
};