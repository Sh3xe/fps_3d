#pragma once

#include "texture.hpp"
#include <string>

// TODO: change api to use Ref<Texture2D> load_from_file()

class Texture2D: public Texture
{
public:
	Texture2D():
		Texture()
	{
	}

	Texture2D( const std::string &path ):
		Texture()
	{
		load_from_file( path );
	}

	bool load_from_file( const std::string &path );

	bool create_from_memory(uint32_t width, uint32_t height, uint32_t format, void* data);

	void bind() const;
	void unbind() const;
};