#include "player_controller.hpp"

PlayerController::PlayerController()
{

}

void PlayerController::update( Input &input, float s_dt )
{
	// player's position
	const glm::vec3 view_dir = glm::normalize(m_camera.position - m_camera.center);
	const glm::vec3 view_right = glm::normalize( glm::cross(m_camera.up, view_dir) );

	if( input.get_key(SDL_SCANCODE_W) )
		m_camera.position += view_dir * s_dt;
	if( input.get_key(SDL_SCANCODE_S) )
		m_camera.position -= view_dir * s_dt;
	if( input.get_key(SDL_SCANCODE_D) )
		m_camera.position += view_right * s_dt;
	if( input.get_key(SDL_SCANCODE_A) )
		m_camera.position -= view_right * s_dt;
}