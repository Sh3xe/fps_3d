#pragma once

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 position {0.0f, 0.0f, 1.0f};
	glm::vec3 center   {0.0f, 0.0f, 0.0f};
	glm::vec3 up       {0.0f, 1.0f, 0.0f};
	float fov          {3.14f/2.0f};
	float near         { 0.001f };
	float far          { 100.0f };

	glm::mat4 get_mvp() const;
	glm::mat4 get_view() const;
	glm::mat4 get_projection() const;
};