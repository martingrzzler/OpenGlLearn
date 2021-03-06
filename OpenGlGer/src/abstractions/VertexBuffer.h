#include<GL/glew.h>

#pragma once

class VertexBuffer
{
public:
	VertexBuffer(void* data, unsigned int verticesSize);
	virtual ~VertexBuffer();
	void Bind();
	void UnBind();

private:
	GLuint vao;
	GLuint bufferId;
};
