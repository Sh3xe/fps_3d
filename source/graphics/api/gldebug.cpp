#include "gldebug.hpp"
#include "core/logger.hpp"
#include <glad/glad.h>

void _log_gl_errors(int line, const char* file)
{
	GLenum error_flag = GL_NO_ERROR;
	while((error_flag = glGetError()) != GL_NO_ERROR)
	{
		VV_ERROR("OpenGL Error in file: ", file, " at line", line, ": ");
		switch(error_flag)
		{
			case GL_INVALID_ENUM:
				VV_ERROR("GL_INVALID_ENUM");
				break;
			case GL_INVALID_VALUE:
				VV_ERROR("GL_INVALID_VALUE");
				break;
			case GL_INVALID_OPERATION:
				VV_ERROR("GL_INVALID_OPERATION");
				break;
			case GL_OUT_OF_MEMORY:
				VV_ERROR("GL_OUT_OF_MEMORY");
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				VV_ERROR("GL_INVALID_FRAMEBUFFER_OPERATION");
				break;
			default: break;
		}
	}
}
