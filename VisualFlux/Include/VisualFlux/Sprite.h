#pragma once

#include <VisualFlux/OpenGL.h>
#include <VisualFlux/Vertex.h>

class Sprite {
public:
	enum class CollisionType {
		TRIANGLE,
		RECTANGLE,
		CIRCLE
	} const collisionType;

	enum class RenderType {
		TRIANGLE,
		RECTANGLE
	} const renderType;

	Sprite(
		Position position,
		Color color,
		float width, float height, 
		GLuint texture, 
		CollisionType collisionType, RenderType renderType
	);
	virtual ~Sprite();

	GLuint texture;
	Vertex** generateVertices();
private:
	Position _position;
	Color _color;
	float _width, _height;
	
};