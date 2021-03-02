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

	//enables vsync
	glfwSwapInterval(1);

	// set up
	auto drawTrinangle = renderColoredTriangle();

	// initialize shader
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.bind();

	//helper varibales for fps
	double lastTime = glfwGetTime();
	int nbFrames = 0;


	// Wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window))
	{
		//fps
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last print was more than 1 sec ago
		 // printf and reset timer
			std::cout << 1000.0 / double(nbFrames) << " ms/frame" << std::endl;
			std::cout << nbFrames << " FPS" << std::endl;
			nbFrames = 0;
			lastTime += 1.0;
		}

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