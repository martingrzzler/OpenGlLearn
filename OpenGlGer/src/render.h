#pragma once

#include <array>
#include <functional>

struct Vertex
{	
	// coordinates
	float x;
	float y;
	float z;
	// color values RGBA
	float r;
	float g;
	float b;
	float a;
};


void renderOldGLTrianagle();
std::function<void()> renderTriangle();
std::function<void()> renderColoredTriangle();