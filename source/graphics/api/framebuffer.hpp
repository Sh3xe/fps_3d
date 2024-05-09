#pragma once

#include "defines.hpp"

class FrameBuffer
{
public:
	FrameBuffer(uint32_t width, uint32_t height);
	~FrameBuffer();

	FrameBuffer& operator=(const FrameBuffer&) = delete;
	FrameBuffer(const FrameBuffer &) = delete;

	inline bool is_valid() const { return m_valid; }

	void bind() const;
	static void unbind();

	FrameBuffer& attach_stencil();
	FrameBuffer& attach_depth();
	FrameBuffer& attach_depth_stencil();
	FrameBuffer& attach_color();

private:
	bool m_valid{ false };
	uint32_t m_id{ 0 };
	uint32_t m_width{ 0 }, m_height{ 0 };
	uint32_t m_color_text_id{ 0 };
	uint32_t m_depth_text_id{ 0 };
	uint32_t m_stencil_text_id{ 0 };
	uint32_t m_depth_stencil_text_id{ 0 };
};