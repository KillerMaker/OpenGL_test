#include "texture.h"
#include <iostream>

namespace gl_helper 
{
    void texture::bind_texture(GLenum target)
    {
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }

    void texture::set_parameter(GLenum target, GLenum param, GLint value)
    {
        glTexParameteri(target, param, value);
    }

    void texture::set_parameter(GLenum target, GLenum param, const GLint* values)
    {
        glTexParameteriv(target, param, values);
    }

    void texture::load_in_GPU(const char* filename, bool create_bitmap)
    {
        unsigned char* image = load_from_file(filename, width, height, nr_channels);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        if (create_bitmap)
            glGenerateMipmap(GL_TEXTURE_2D);

        delete[] image;
    }

    void texture::use()
    {
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }

    unsigned char* texture::load_from_file(const char* filename, int& width, int& height, int& nr_channels)
    {
        unsigned char* image = stbi_load(filename, &width, &height, &nr_channels, 0);

        if (stbi_failure_reason())
        {
            std::cout << stbi_failure_reason();
            return nullptr;
        }

        return image;

    }
}

