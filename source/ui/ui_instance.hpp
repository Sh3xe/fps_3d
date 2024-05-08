#pragma once

#include "../graphics/window.hpp"
#include "../graphics/renderer2d.hpp"

class UIInstance
{
public:

	void update(float s_dt, const Window &window);
	void render(const Renderer2D &renderer);
};