#include "shader.h"

namespace gl_helper 
{
    shader::shader(const char* vertex_path, const char* fragment_path)
    {
        std::string vertex_code;
        std::string fragment_code;

        load_shaders_from_disk(vertex_path, fragment_path, vertex_code, fragment_code);
        compile_shaders(vertex_code.c_str(), fragment_code.c_str());
    }

    shader::~shader()
    {
        glDeleteBuffers(1, &vertex_array_buffer);
        glDeleteBuffers(1, &vertex_buffer_object);
        glDeleteProgram(program_id);
    }

    void shader::set_matrix(const std::string& name, gl_helper::matrix& matrix)
    {
        switch (matrix.size())
        {
        case 4:
            glUniformMatrix2fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, matrix.handle());
            break;
        case 9:
            glUniformMatrix3fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, matrix.handle());
            break;
        case 16:
            glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_TRUE, matrix.handle());
            break;
        }
    }

    void shader::generate_vertex_buffer()
    {
        glGenBuffers(1, &vertex_buffer_object);
        glGenVertexArrays(1, &vertex_array_buffer);
        glBindVertexArray(vertex_array_buffer);
    }

    void shader::bind_vertex_array_buffer(const gl_helper::matrix& matrix)
    {
        vertex_count = matrix.get_rows();

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * matrix.size(), matrix.get_read_only_handle(), GL_STATIC_DRAW);
    }

    void shader::set_vertex_attribute(unsigned int attribute_index,unsigned int vertex_dimension, bool normalized, unsigned int stride, const void* ptr)
    {
        glVertexAttribPointer(
            attribute_index,
            vertex_dimension,
            GL_FLOAT,
            (normalized) ? GL_TRUE : GL_FALSE,
            stride,
            ptr
        );

        glEnableVertexAttribArray(attribute_index);
    }

    void shader::use()
    {
        glUseProgram(program_id);
    }

    void shader::load_shaders_from_disk(const char* vertex_path, const char* fragment_path, std::string& vertex_code, std::string& fragment_code)
    {
        std::ifstream v_shader_file;
        std::ifstream f_shader_file;

        try
        {
            v_shader_file.open(vertex_path);
            f_shader_file.open(fragment_path);

            std::stringstream v_shader_stream;
            std::stringstream f_shader_stream;

            v_shader_stream << v_shader_file.rdbuf();
            f_shader_stream << f_shader_file.rdbuf();

            v_shader_file.close();
            f_shader_file.close();

            vertex_code = v_shader_stream.str();
            fragment_code = f_shader_stream.str();            
        }
        catch (const std::exception&)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
    }

    void shader::compile_shaders(const char* vertex_shader, const char* fragment_shader)
    {
        int compilation_succeed;
        char log[512];

        unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader_id, 1, &vertex_shader, nullptr);
        glCompileShader(vertex_shader_id);

        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compilation_succeed);

        if (!compilation_succeed)
        {
            glGetShaderInfoLog(vertex_shader_id, 512, nullptr, log);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
        }

        unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader_id, 1, &fragment_shader, nullptr);
        glCompileShader(fragment_shader_id);

        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compilation_succeed);

        if (!compilation_succeed)
        {
            glGetShaderInfoLog(fragment_shader_id, 512, nullptr, log);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
        }

        program_id = glCreateProgram();
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        glLinkProgram(program_id);

        glDeleteShader(fragment_shader_id);
        glDeleteShader(vertex_shader_id);
    }
}

 