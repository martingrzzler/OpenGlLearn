#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "shader.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")


int main(int argc, const char** argv)
{

	// init GLFW 
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	//create window and context
	window = glfwCreateWindow(640, 480, "OpenGl Playground", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error: glew could not be initialized" << std::endl;
		return -1;
	}

	std::cout << "OpenGl Version " << glGetString(GL_VERSION) << std::endl;

	// set up
	auto drawTrinangle = renderTriangle();

	// initialize shader
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.bind();


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//render here
		drawTrinangle();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	
	glfwTerminate();
	return 0;
}