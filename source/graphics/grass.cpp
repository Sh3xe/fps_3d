#include "grass.hpp"

struct GrassVertex
{
    float x, y, z;
    uint32_t color_id;
};

static constexpr GrassVertex grass_vertices[] =
{
    GrassVertex{0.000000, 0.000000, 0.145381, 0},
    GrassVertex{-0.002487, 1.707150, -0.000303, 3},
    GrassVertex{0.000000, 0.000000, -0.145381, 0},
    GrassVertex{-0.000000, 1.568015, 0.027646, 1},
    GrassVertex{-0.000000, 1.333333, 0.057098, 2},
    GrassVertex{-0.000000, 1.020179, 0.094790, 1},
    GrassVertex{0.000000, 0.707025, 0.111863, 1},
    GrassVertex{0.000000, 0.333333, 0.128360, 2},
    GrassVertex{0.000000, 0.333333, -0.128360, 2},
    GrassVertex{0.000000, 0.707025, -0.111863, 1},
    GrassVertex{-0.000000, 1.020179, -0.094790, 1},
    GrassVertex{-0.000000, 1.333333, -0.057098, 2},
    GrassVertex{-0.000000, 1.568015, -0.027646, 1}
};

static constexpr uint32_t grass_indices[] =
{
    7, 0, 2, 2, 7, 8,
    1, 3, 12,
    3, 4, 11, 11, 3, 12,
    4, 5, 10, 4, 10, 11,
    5, 6, 9, 5, 9, 10,
    6, 7, 8, 6, 8, 9
};

Ref<IndexBuffer> GrassVolume::grass_blade_indices;
Ref<VertexBuffer> GrassVolume::grass_blade_vertices;

GrassVolume::GrassVolume( const glm::vec3 &position, const glm::vec2 &plane_size, const GrassParameters &params ):
	m_params(params)
{
    if( grass_blade_vertices == nullptr )
    {
        grass_blade_indices = std::make_shared<IndexBuffer>( grass_indices, 33 );
        grass_blade_vertices = std::make_shared<VertexBuffer>( grass_vertices, sizeof(grass_vertices));
    }

	setup_positions(position, plane_size);
    setup_vao();
}

void GrassVolume::setup_positions( const glm::vec3 &position, const glm::vec2 &plane_size )
{	
	float dx = plane_size.x / (float)m_params.density;
	float dy = plane_size.y / (float)m_params.density;

	m_positions.clear();
	for(size_t i = 0; i < m_params.density; ++i)
	for(size_t j = 0; j < m_params.density; ++j)
	{
		m_positions.emplace_back(position + glm::vec3{dx*i, 0.0f, dy*j});
	}

	m_position_buffer = std::make_shared<VertexBuffer>(m_positions.data(), m_positions.size() * sizeof(glm::vec3));
}

void GrassVolume::setup_vao()
{
	m_vertex_array.set_index_buffer(grass_blade_indices);
	m_vertex_array.add_vertex_buffer(grass_blade_vertices, {LayoutDescription(0, 3, offsetof(GrassVertex, x), sizeof
	(GrassVertex), LayoutDataType::FLOAT, false), LayoutDescription(1, 1, offsetof(GrassVertex, color_id), sizeof
	(GrassVertex), LayoutDataType::UINT, false)});
	m_vertex_array.add_vertex_buffer( m_position_buffer, {LayoutDescription(2, 3, 0, 3*sizeof(float), LayoutDataType::FLOAT, true)});
}