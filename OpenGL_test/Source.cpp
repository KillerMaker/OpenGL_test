#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "texture.h"
#include "opengl_window.h"
#include "shader.h"
#include "transformation.h"
#include "quadratic_bezier.h"
#include "cubic_bezier.h"


float* get_vertices(int&);

void set_vertex_buffer(gl_helper::shader& program);
void set_textures(gl_helper::texture& tex1, gl_helper::texture& tex2);

int main()
{
    gl_helper::opengl_window window(800, 800, "OpenGL");

    //Getting shaders path
    std::filesystem::path vertex_shader_path = std::filesystem::current_path() / "vertex_shader.glsl";
    std::filesystem::path fragment_shader_path = std::filesystem::current_path() / "fragment_shader.glsl";

    gl_helper::shader program(
        vertex_shader_path.string().c_str(),
        fragment_shader_path.string().c_str()
    );

    gl_helper::texture bricks_texture;
    gl_helper::texture blue_texture;

    set_vertex_buffer(program);
    set_textures(bricks_texture, blue_texture);

    gl_helper::transform transform;

    program.use();
    program.set_int("texture1", 0);
    program.set_int("texture2", 1);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(.01f, .01f, .01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        bricks_texture.use();

        glActiveTexture(GL_TEXTURE1);
        blue_texture.use();

        program.use();

        glBindVertexArray(program.get_vertex_array_buffer()); 

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        gl_helper::matrix view_matrix;
        transform.translation_matrix(0.0f, 0.0f, -10.0f, view_matrix);

        gl_helper::matrix transform_matrix;
        transform.rotation_matrix_y(30.0f * (float)glfwGetTime(), transform_matrix);

        gl_helper::matrix projection_matrix;
        transform.projection_matrix(projection_matrix, 45.0f, width, height, 0.5f, 100.f);

        int sign = 1;
        for (int i = 0; i <3; i++)
        {
            sign = -sign;
            gl_helper::matrix rotation, translation;

            transform.rotation_matrix_x(-55.0f * (float)glfwGetTime()* sign, rotation);
            transform.translation_matrix(i*sin((float)glfwGetTime()) * sign*2, i*cos((float)glfwGetTime()) * sign*2, i * sign*2, translation);

            gl_helper::matrix model_matrix = rotation * translation;
            
            program.set_matrix("transform_matrix", transform_matrix);
            program.set_matrix("projection_matrix", projection_matrix);
            program.set_matrix("view_matrix", view_matrix);
            program.set_matrix("model_matrix", model_matrix);

            glDrawArrays(GL_TRIANGLES, 0, program.get_vertex_count());
        }

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

float* get_vertices(int& size)
{
    size = 36*5;

    auto* ptr = new float[size] {

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};


    return ptr;
}

void set_vertex_buffer(gl_helper::shader& program) 
{
    //Getting data vertices
    int size;
    float* data = get_vertices(size);

    //Wrapping the vertex data inside a matrix for ease of use
    gl_helper::matrix m_data(36, 5, data, true);

    //Creating a vertex buffer and pushing data to it
    program.generate_vertex_buffer();
    program.bind_vertex_array_buffer(m_data);

    //Setting vertex attributues using the vertux buffer data 
    program.set_vertex_attribute(0, 3, false, sizeof(float) * 5);
    //program.set_vertex_attribute(1, 3, false, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    program.set_vertex_attribute(2, 2, false, sizeof(float) * 5, (void*)(3 * sizeof(float)));

}

void set_textures(gl_helper::texture& tex1, gl_helper::texture& tex2)
{ 
    stbi_set_flip_vertically_on_load(true);

    //Getting the texture file path in disk
    std::filesystem::path bricks_texture_path = std::filesystem::current_path() / "assets" / "shinji.png";
    std::filesystem::path blue_texture_path = std::filesystem::current_path() / "assets" / "blue.png";

    //Binding the texture
    tex1.bind_texture(GL_TEXTURE_2D);

    //Setting last binded texture parameters
    tex1.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex1.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    tex1.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex1.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Loading the texture inside the GPU
    tex1.load_in_GPU(bricks_texture_path.string().c_str());


    tex2.bind_texture(GL_TEXTURE_2D);

    //Setting last binded texture parameters
    tex2.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex2.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    tex2.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex2.set_parameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Loading the texture inside the GPU
    tex2.load_in_GPU(blue_texture_path.string().c_str());
}




