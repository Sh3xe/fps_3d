#pragma once 
#include "framebuffer.hpp"
#include <glad/glad.h>

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
{
	glGenFramebuffers(1, &m_id);
	attach_color(width, height);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void FrameBuffer::attach_color(uint32_t width, uint32_t height)
{
	// generates the opengl texture object
	uint32_t texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// buffer specification
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	// binding to the frambuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0); 
}