#pragma once 
#include "framebuffer.hpp"
#include "graphics/api/gldebug.hpp"
#include <glad/glad.h>

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height):
	m_width(width), m_height(height)
{
	// create the object
	glGenFramebuffers(1, &m_id);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteTextures(1, &m_stencil_text_id);
	glDeleteTextures(1, &m_depth_stencil_text_id);
	glDeleteTextures(1, &m_depth_text_id);
	glDeleteTextures(1, &m_color_text_id);
	glDeleteBuffers(1, &m_id);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bind() const
{
	assert(m_valid);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

FrameBuffer& FrameBuffer::attach_depth_stencil()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// generates the opengl texture object
	glGenTextures(1, &m_depth_stencil_text_id);
	glBindTexture(GL_TEXTURE_2D, m_depth_stencil_text_id);

	// specify its parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// bind it to the buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil_text_id, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// error handling...
	log_gl_errors();
	m_valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	unbind();
	return *this;
}

FrameBuffer& FrameBuffer::attach_stencil()
{
	assert(false && "not tested");
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// generates the opengl texture object
	glGenTextures(1, &m_stencil_text_id);
	glBindTexture(GL_TEXTURE_2D, m_stencil_text_id);
	
	// specify its parameters
	log_gl_errors();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX8, m_width, m_height, 0, GL_STENCIL_INDEX8, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// bind it to the buffer
	log_gl_errors();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_stencil_text_id, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// error handling...
	log_gl_errors();
	m_valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	unbind();
	return *this;
}

FrameBuffer& FrameBuffer::attach_depth()
{
	assert(false && "not tested");
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// generates the opengl texture object
	glGenTextures(1, &m_depth_text_id);
	glBindTexture(GL_TEXTURE_2D, m_depth_text_id);

	// buffer specification
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// binding to the frambuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_text_id, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	log_gl_errors();
	m_valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	unbind();
	return *this;
}

FrameBuffer& FrameBuffer::attach_color()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// generates the opengl texture object
	glGenTextures(1, &m_color_text_id);
	glBindTexture(GL_TEXTURE_2D, m_color_text_id);

	// buffer specification
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	// binding to the frambuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_text_id, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// error handling...
	log_gl_errors();
	m_valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	unbind();
	return *this;
}