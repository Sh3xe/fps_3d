#pragma once

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 position {0.0f, 0.0f, 1.0f};
	glm::vec3 direction {0.0f, 0.0f, 0.0f};
	glm::vec3 up {0.0f, 1.0f, 0.0f};
	float fov { 1.4f };
	float near { 0.001f };
	float far { 200.0f };
	float aspect_ratio = { 16.0f / 9.0f };

	glm::mat4 view;
	glm::mat4 projection;

	void calculate_view();
	void calculate_projection();
};