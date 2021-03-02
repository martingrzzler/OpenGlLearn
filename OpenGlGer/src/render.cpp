#include <GL/glew.h>
#include "render.h"

void renderOldGLTrianagle()
{
	glBegin(GL_TRIANGLES);

	glVertex2f(-0.5, -0.5);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();

}


std::function<void()> renderTriangle()
{
	std::array<Vertex, 4> positions =
	{
		Vertex{-0.5f, -0.5f},
		Vertex{0.0f, 0.5f },
		Vertex{0.5f, -0.5f}
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(Vertex), positions.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, x));
	glEnableVertexAttribArray(0);

	int size = positions.size();

	return [size]()
	{
		glDrawArrays(GL_TRIANGLES, 0, size);
	};

}