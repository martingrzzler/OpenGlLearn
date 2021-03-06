#include "VertexBuffer.h"
#include "../render.h"
#include<iostream>

VertexBuffer::VertexBuffer(void* data, unsigned int verticesSize)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &this->bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(Vertex), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, x));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, r));

	glBindVertexArray(0);

}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->bufferId);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(this->vao);
}

void VertexBuffer::UnBind()
{
	glBindVertexArray(0);
}
