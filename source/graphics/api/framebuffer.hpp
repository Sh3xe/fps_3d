#pragma once

#include "defines.hpp"

class FrameBuffer
{
public:
	FrameBuffer(uint32_t width, uint32_t height);
	~FrameBuffer();

	FrameBuffer &operator=(const FrameBuffer&) = delete;
	FrameBuffer(const FrameBuffer &) = delete;

private:
	void attach_color(uint32_t width, uint32_t height);

	uint32_t m_id;
};