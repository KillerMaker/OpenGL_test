#pragma once
#include <string>
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

namespace gl_helper
{
	class opengl_window
	{
	public:
		GLFWwindow* window = nullptr;

		opengl_window(unsigned int width, unsigned int height, const char* name);
		~opengl_window(){ glfwTerminate(); }

		operator GLFWwindow* () { return window; }
	};
}


