#include <VisualFlux/Sprite.h>

#include <cstdio>

namespace VisualFlux {

	Sprite::Sprite(Position position, Color color, float width, float height, GLuint texture, CollisionType collisionType, RenderType renderType) :
		_position(position),
		_color(color),
		_width(width),
		_height(height),
		texture(texture),
		collisionType(collisionType),
		renderType(renderType) {
	}

	Sprite::~Sprite() {
	}

	Vertex** Sprite::generateVertices() {
		Vertex** vertices = nullptr;

		switch (renderType) {
		default:
			printf("Render type not recognized. Using triangle.\n");
		case RenderType::TRIANGLE:
			vertices = new Vertex*[3];
			vertices[0] = new Vertex(Position(_position.x, _position.y), Color(_color.r, _color.g, _color.b, _color.a), UV(0.0f, 0.0f));
			vertices[1] = new Vertex(Position(_position.x + _width, _position.y), Color(_color.r, _color.g, _color.b, _color.a), UV(1.0f, 0.0f));
			vertices[2] = new Vertex(Position(_position.x, _position.y + _height), Color(_color.r, _color.g, _color.b, _color.a), UV(0.0f, 1.0f));
			break;
		case RenderType::RECTANGLE:
			vertices = new Vertex*[6];
			vertices[0] = new Vertex(Position(_position.x, _position.y), Color(_color.r, _color.g, _color.b, _color.a), UV(0.0f, 0.0f));
			vertices[1] = new Vertex(Position(_position.x + _width, _position.y), Color(_color.r, _color.g, _color.b, _color.a), UV(1.0f, 0.0f));
			vertices[2] = new Vertex(Position(_position.x, _position.y + _height), Color(_color.r, _color.g, _color.b, _color.a), UV(0.0f, 1.0f));
			vertices[3] = new Vertex(Position(_position.x, _position.y + _height), Color(_color.r, _color.g, _color.b, _color.a), UV(0.0f, 1.0f));
			vertices[4] = new Vertex(Position(_position.x + _width, _position.y + _height), Color(_color.r, _color.g, _color.b, _color.a), UV(1.0f, 1.0f));
			vertices[5] = new Vertex(Position(_position.x + _width, _position.y), Color(_color.r, _color.g, _color.b, _color.a), UV(1.0f, 0.0f));
			break;
		}

		return vertices;
	}

}