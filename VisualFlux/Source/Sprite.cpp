#include <VisualFlux/Sprite.h>

#include <cstdio>

namespace VisualFlux {

	Sprite::Sprite(Position position, Color color, float width, float height, GLuint texture, CollisionType collisionType, RenderType renderType) :
		position(position),
		color(color),
		width(width),
		height(height),
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
			vertices[0] = new Vertex(Position(position.x, position.y), Color(color.r, color.g, color.b, color.a), UV(0.0f, 0.0f));
			vertices[1] = new Vertex(Position(position.x + width, position.y), Color(color.r, color.g, color.b, color.a), UV(1.0f, 0.0f));
			vertices[2] = new Vertex(Position(position.x, position.y + height), Color(color.r, color.g, color.b, color.a), UV(0.0f, 1.0f));
			break;
		case RenderType::RECTANGLE:
			vertices = new Vertex*[6];
			vertices[0] = new Vertex(Position(position.x, position.y), Color(color.r, color.g, color.b, color.a), UV(0.0f, 0.0f));
			vertices[1] = new Vertex(Position(position.x + width, position.y), Color(color.r, color.g, color.b, color.a), UV(1.0f, 0.0f));
			vertices[2] = new Vertex(Position(position.x, position.y + height), Color(color.r, color.g, color.b, color.a), UV(0.0f, 1.0f));
			vertices[3] = new Vertex(Position(position.x, position.y + height), Color(color.r, color.g, color.b, color.a), UV(0.0f, 1.0f));
			vertices[4] = new Vertex(Position(position.x + width, position.y + height), Color(color.r, color.g, color.b, color.a), UV(1.0f, 1.0f));
			vertices[5] = new Vertex(Position(position.x + width, position.y), Color(color.r, color.g, color.b, color.a), UV(1.0f, 0.0f));
			break;
		}

		return vertices;
	}

}