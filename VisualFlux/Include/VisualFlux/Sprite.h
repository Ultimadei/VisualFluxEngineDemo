#pragma once

#include <VisualFlux/OpenGL.h>
#include <VisualFlux/Vertex.h>

namespace VisualFlux {

	struct Sprite {
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

		
		Vertex** generateVertices();
		

		Position position;
		Color color;
		float width, height;
		GLuint texture;
	};

}