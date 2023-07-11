#pragma once

#include <glad/glad.h>
#include"stb_image.h"
namespace gl_helper
{
	class texture
	{
	public:
		void bind_texture(GLenum target);
		void set_parameter(GLenum target, GLenum param, GLint value);
		void set_parameter(GLenum target, GLenum param, const GLint* values);
		void load_in_GPU(const char* filename, bool create_bitmap = true);
		void use();
	private:
		unsigned int texture_id;
		int width;
		int height;
		int nr_channels;

		unsigned char* load_from_file(const char* filename, int& width, int& height, int& nr_channels);

	};
}


