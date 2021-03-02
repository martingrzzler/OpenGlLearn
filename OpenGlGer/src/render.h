#pragma once

#include <array>
#include <functional>

struct Vertex
{
	float x;
	float y;
	float z;
};


void renderOldGLTrianagle();
std::function<void()> renderTriangle();