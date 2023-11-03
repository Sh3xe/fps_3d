#include "camera.hpp"
#include <glm/ext.hpp>

glm::mat4 Camera::get_mvp() const
{
	//TODO: change aspect ratio
	return glm::perspective(fov, 16.0f/9.0f, near, far) * glm::lookAt(position, center, up);
}

glm::mat4 Camera::get_view() const
{
	return glm::lookAt(position, center, up);
}

glm::mat4 Camera::get_projection() const
{
	return glm::perspective(fov, 16.0f/9.0f, near, far);
}
