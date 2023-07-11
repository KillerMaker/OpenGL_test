#pragma once

#include <glad/glad.h> 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include"vector4.h"
#include "matrix.h"
namespace gl_helper 
{
	class shader
	{
	public:

		shader(const char* vertex_path, const char* fragment_path);
		~shader();

		void use();

		inline void set_int(const std::string& name, int value)
		{
			glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
		}

		inline void set_bool(const std::string& name, bool value)
		{
			glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
		}

		inline void set_float(const std::string& name, float value)
		{
			glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
		}

		inline void set_vector3(const std::string& name, const gl_helper::vector3& vector)
		{
			glUniform3f(glGetUniformLocation(program_id, name.c_str()), *vector.x, *vector.y, *vector.z);
		}

		inline void set_vector4(const std::string& name, const gl_helper::vector4& vector)
		{
			glUniform4f(glGetUniformLocation(program_id, name.c_str()), *vector.x, *vector.y, *vector.z, *vector.w);
		}

		void set_matrix(const std::string& name, gl_helper::matrix& matrix);

		inline unsigned int get_shader_program() { return program_id; }
		inline unsigned int get_vertex_array_buffer() { return vertex_array_buffer; }
		inline unsigned int get_vertex_buffer_object() { return vertex_buffer_object; }
		inline unsigned int get_vertex_count() { return vertex_count; }

		void generate_vertex_buffer();
		void bind_vertex_array_buffer(const gl_helper::matrix& matrix);
		void set_vertex_attribute(unsigned int attribute_index, unsigned int vertex_dimension=3, bool normalized = false, unsigned int stride = 3 * sizeof(float), const void* ptr = (void*)0);

	private:
		unsigned int vertex_count;
		unsigned int program_id;
		unsigned int vertex_buffer_object;
		unsigned int vertex_array_buffer;

		void load_shaders_from_disk(const char* vertex_path, const char* fragment_path, std::string& vertex_code, std::string& fragment_code);
		void compile_shaders(const char* vertex_shader, const char* fragment_shader);
	};
}


