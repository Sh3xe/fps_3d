#include "camera.hpp"
#include <glm/ext.hpp>

void Camera::calculate_view()
{
	view = glm::lookAt(position, position + direction, up);
}

void Camera::calculate_projection()
{
	projection = glm::perspective(fov, aspect_ratio, near, far);
}