#pragma once

#include "vvtypes.hpp"
#include "api/vertex_array.hpp"
#include <vector>
#include <glm/glm.hpp>

struct GrassParameters
{
	uint32_t density = 4;
	float max_height = 0.2f;
	float wind_power = 1.0f;
	glm::vec3 base_color   { 3.0/255.0  , 59.0/255.0 , 0.0/255.0   };
	glm::vec3 bottom_color { 14.0/255.0 , 191.0/255.0, 100.0/255.0 };
	glm::vec3 top_color    { 142.0/255.0, 218.0/255.0, 136.0/255.0 };
	glm::vec3 tip_color    { 227.0/255.0, 255.0/255.0, 243.0/255.0 };
};

class GrassVolume
{
public:
	friend class Renderer3D;

	GrassVolume( const glm::vec3 &position, const glm::vec2 &plane_size, const GrassParameters &params );
	~GrassVolume() {}

private:
	void setup_positions( const glm::vec3 &position, const glm::vec2 &plane_size );
	void setup_vao();

	GrassParameters m_params {};
	Ref<VertexBuffer> m_position_buffer {nullptr};
    VertexArray m_vertex_array;
	std::vector<glm::vec3> m_positions;

    static Ref<IndexBuffer> grass_blade_indices;
    static Ref<VertexBuffer> grass_blade_vertices;
};