#include "player_controller.hpp"

PlayerController::PlayerController():
	m_base_position(0.0f, 0.0f, 0.0f)
{

}

void PlayerController::update( Input &input, float s_dt )
{
	// player's position
	const glm::vec3 front = glm::normalize(glm::vec3{ m_camera.direction.x, 0.0f, m_camera.direction.z });
	const glm::vec3 view_right = glm::normalize( -glm::cross(m_camera.up, m_camera.direction) );

	if( input.is_keyup(SDL_SCANCODE_W) )
		m_base_position += front * s_dt;
	if (input.is_keyup(SDL_SCANCODE_S))
		m_base_position -= front * s_dt;
	if( input.is_keyup(SDL_SCANCODE_D) )
		m_base_position += view_right * s_dt;
	if( input.is_keyup(SDL_SCANCODE_A) )
		m_base_position -= view_right * s_dt;
	if (input.is_keyup(SDL_SCANCODE_LSHIFT))
		m_base_position -= m_camera.up * s_dt;
	if (input.is_keyup(SDL_SCANCODE_SPACE))
		m_base_position += m_camera.up * s_dt;

	m_camera.position = m_base_position;
	m_camera.position.y += 1.75f;

	// player's orientation
	m_yaw += (float)input.mouse_dx() * m_sensitivity;
	m_pitch -= (float)input.mouse_dy() * m_sensitivity;

	if (m_pitch > 1.5f) m_pitch = 1.5f;
	if (m_pitch < -1.5f) m_pitch = -1.5f;

	glm::vec3 yaw_proj{ cosf(m_yaw), 0.0f, sinf(m_yaw) };
	m_camera.direction = cosf(m_pitch) * yaw_proj + sinf(m_pitch) * glm::vec3{ 0.0f, 1.0f, 0.0f };
}