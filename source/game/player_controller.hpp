#pragma once

#include <glm/glm.hpp>

#include "core/camera.hpp"
#include "core/input.hpp"

class PlayerController 
{
public:
	PlayerController();

	inline Camera &get_cam() { return m_camera; };
	void update( Input &input, float s_dt );

private:
	// angle
	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
	float m_sensitivity = 0.001f;

	Camera m_camera;
	glm::vec3 m_base_position;
};