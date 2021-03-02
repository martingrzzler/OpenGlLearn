#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	this->shaderId = this->createShader(vertexShaderFilename, fragmentShaderFilename);
}

Shader::~Shader()
{
	glDeleteProgram(this->shaderId);
}

void Shader::bind()
{
	glUseProgram(shaderId);
}

void Shader::unbind()
{
	glUseProgram(0);
}

GLuint Shader::compile(std::string shaderSource, GLenum type)
{
	GLuint id = glCreateShader(type);
	const char* src = shaderSource.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	// compile error checking
	int hasCompiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &hasCompiled);
	if (hasCompiled != GL_TRUE) 
	{
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = new char[length];
		glGetShaderInfoLog(id, length, &length, msg);
		std::cout << "Error: during Shader compilation " << msg << std::endl;
		delete[] msg;

		//indicate uninitialized Shader with 0
		return 0;
	}
	return id;
}

std::string Shader::parse(const char* filename)
{
	std::ifstream fs;
	fs.open(filename);
	if (!fs.is_open())
	{
		std::cout << "File " << filename << " not found" << std::endl;
		return std::string();
		fs.close();
	}
	std::stringstream buffer;
	buffer << fs.rdbuf();
	fs.close();

	return buffer.str();
}

GLuint Shader::createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	std::string vertexShaderSource = this->parse(vertexShaderFilename);
	std::string fragmentShaderSource = this->parse(fragmentShaderFilename);

	GLuint program = glCreateProgram();
	GLuint vs = this->compile(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fs = this->compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	// optionally I could delete the shaders now 

	return program;
}
