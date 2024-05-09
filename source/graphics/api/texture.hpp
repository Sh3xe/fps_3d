#pragma once

#include "defines.hpp"

class Texture {
public:
	Texture();
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	uint32_t get_id() const { return m_id; }

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	inline bool is_valid() const { return m_valid; }

protected:
	uint32_t m_id = 0;
	bool m_valid = false;
};