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
	float m_pitch;
	float m_yaw;

	Camera m_camera;
	glm::vec3 m_base_positon;
};