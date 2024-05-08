#pragma once

#include "defines.hpp"

class SkyboxModel
{
public:
	friend class Renderer3D;

	SkyboxModel();
	~SkyboxModel();

	void bind();
	void unbind();

private:
	uint32_t m_vao;
	uint32_t m_vbo;
};