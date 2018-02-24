#pragma once

#include <SDL/SDL.h>
#include <VisualFlux/OpenGL.h>
#include <VisualFlux/Shader.h>
#include <VisualFlux/Sprite.h>

#include <vector>

namespace VisualFlux
{
	class Window {
	public:
		Window(
			const char* title,
			int x, int y,
			int width, int height,
			const char* vertexShaderLocation,
			const char* fragmentShaderLocation,
			bool initGlew = true,
			bool doubleBuffered = true
		);
		~Window();

		void draw();
		void draw(Shader::Uniform uniformVariables[], int uniformCount);
		void addSprite(Sprite sprite);
	private:
		const char* _title;
		int _x, _y;
		int _width, _height;
		GLuint _program, _vao, _vbo;
		Shader *_vertexShader, *_fragmentShader;
		bool _doubleBuffered;
		SDL_Window* _window;
		std::vector<Sprite> _sprites;
		std::vector<Vertex> _vertices;

		void _bindBuffers();
	};


}

