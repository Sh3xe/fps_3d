#include "grass.hpp"
#include <iostream>

struct GrassVertex
{
    float x, y, z;
    int32_t color_id;
};

static constexpr GrassVertex grass_vertices[] =
{
	GrassVertex{ 0, 0,0.0256555, 0 },
	GrassVertex{ -0.000438882, 0.301262,-5.34706e-05, 3 },
	GrassVertex{ 0, 0,-0.0256555, 0 },
	GrassVertex{ -0, 0.276709,0.00487871, 2 },
	GrassVertex{ -0, 0.235294,0.0100761, 2 },
	GrassVertex{ -0, 0.180032,0.0167276, 1 },
	GrassVertex{ 0, 0.124769,0.0197405, 1 },
	GrassVertex{ 0, 0.0588235,0.0226518, 1 },
	GrassVertex{ 0, 0.0588235,-0.0226518, 1 },
	GrassVertex{ 0, 0.124769,-0.0197405, 1 },
	GrassVertex{ -0, 0.180032,-0.0167276, 1 },
	GrassVertex{ -0, 0.235294,-0.0100761, 2 },
	GrassVertex{ -0, 0.276709,-0.00487871, 2 }
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
	float fac = 0.3f / 1.70f;
	for (const auto& g : grass_vertices)
	{
		std::cout << "GrassVertex{ " << g.x * fac << ", " << g.y * fac << "," << g.z * fac << ", " << g.color_id << " }\n";
	}

	setup_positions(position, plane_size);
    setup_vao();
}

void GrassVolume::setup_positions( const glm::vec3 &position, const glm::vec2 &plane_size )
{	
	if (m_params.density == 0)
		m_params.density = 1;

	float blade_per_meter = sqrtf((float)m_params.density);

	float dx = 1.0f / blade_per_meter;
	float dy = 1.0f / blade_per_meter;

	m_positions.clear();
	for(size_t i = 0; i < blade_per_meter * plane_size.x + 1; ++i)
	for (size_t j = 0; j < blade_per_meter * plane_size.y + 1; ++j)
	{
		m_positions.emplace_back(position + glm::vec3{dx*i, 0.0f, dy*j});
	}

	m_position_buffer = std::make_shared<VertexBuffer>(m_positions.data(), m_positions.size() * sizeof(glm::vec3));
}

void GrassVolume::setup_vao()
{
	m_vertex_array.set_index_buffer(grass_blade_indices);
	m_vertex_array.add_vertex_buffer(grass_blade_vertices, {
        LayoutDescription(0, 3, offsetof(GrassVertex, x), sizeof(GrassVertex), LayoutDataType::FLOAT, false), 
        LayoutDescription(1, 1, offsetof(GrassVertex, color_id), sizeof(GrassVertex), LayoutDataType::INT, false)
	});
	m_vertex_array.add_vertex_buffer( m_position_buffer, {
        LayoutDescription(2, 3, 0, 3*sizeof(float), LayoutDataType::FLOAT, true)
    });
}