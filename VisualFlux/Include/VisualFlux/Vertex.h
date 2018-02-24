#pragma once

#include <VisualFlux/OpenGL.h>

struct Position {
	inline Position(float x, float y) : x(x), y(y) {}
	float x;
	float y;
};

struct Color {
	inline Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	float r;
	float g;
	float b;
	float a;
};

struct Texture {
	GLuint id;
	int width;
	int height;
};

struct UV {
	UV(float u, float v) : u(u), v(v) {}
	float u;
	float v;
};

struct Vertex {
	inline Vertex(Position position, Color color, UV uv) : position(position), color(color), uv(uv) {}
	Position position;
	Color color;
	UV uv;
};