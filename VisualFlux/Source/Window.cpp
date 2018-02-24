#include <VisualFlux/Window.h>
#include <VisualFlux/Vertex.h>

#include <sstream>
#include <iostream>

namespace VisualFlux
{
	Window::Window(
		const char * title,
		int x, int y,
		int width, int height,
		const char* vertexShaderLocation, const char* fragmentShaderLocation,
		bool initGlew,
		bool doubleBuffered
	) :
		_title(title),
		_x(x),
		_y(y),
		_width(width),
		_height(height),
		_doubleBuffered(doubleBuffered),
		_window(nullptr)
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doubleBuffered);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);
		if (_window == nullptr)
		{
			std::ostringstream ss;
			ss << "Unable to create a window. " << SDL_GetError() << "\n";
			throw new std::runtime_error(ss.str());
		}

		const auto context = SDL_GL_CreateContext(_window);
		if (context == nullptr)
		{
			std::ostringstream ss;
			ss << "Unable to create a window. " << SDL_GetError() << "\n";
			throw new std::runtime_error(ss.str());
		}

		gladLoadGLLoader(SDL_GL_GetProcAddress);
		if (!gladLoadGL())
		{
			std::ostringstream ss;
			ss << "Unable to initialize glad.\n";
			throw new std::runtime_error(ss.str());
		}

		std::cout << glGetString(GL_VENDOR) << "\n";
		std::cout << glGetString(GL_VERSION) << "\n";

		_program = glCreateProgram();
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);

		_vertexShader = new Shader(vertexShaderLocation, GL_VERTEX_SHADER);
		_fragmentShader = new Shader(fragmentShaderLocation, GL_FRAGMENT_SHADER);

		int success;
		glGetProgramiv(_program, GL_LINK_STATUS, &success);
		if (!success) 
		{
			char error[512];
			glGetProgramInfoLog(_program, 512, nullptr, error);
			printf("\n%s\n", error);
		}

		_vertexShader->attachShader(_program);
		_fragmentShader->attachShader(_program);
		glLinkProgram(_program);
	}

	Window::~Window() 
	{
	}

	void Window::draw() 
	{
		if (_sprites.size() == 0) { return; }
		_bindBuffers();

		glClearDepth(1.0f);
		glClearColor(255, 0, 0, 255);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glUseProgram(_program);
		glBindVertexArray(_vao);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		int offset = 0;
		for (int i = 0; i < _sprites.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _sprites[i].texture);
			switch (_sprites[i].renderType) {
			case Sprite::RenderType::TRIANGLE:
				glDrawArrays(GL_TRIANGLES, offset, 3);
				offset += 3;
				break;
			case Sprite::RenderType::RECTANGLE:
				glDrawArrays(GL_TRIANGLES, offset, 6);
				offset += 6;
			}
		}
		glBindVertexArray(0);
		glUseProgram(0);

		if (_doubleBuffered) { SDL_GL_SwapWindow(_window); }
		_sprites.clear();
		_vertices.clear();
	}

	void Window::draw(Shader::Uniform uniformVariables[], int uniformCount) {
		if (_sprites.size() == 0) { return; }
		_bindBuffers();

		glClearDepth(1.0f);
		glClearColor(255, 0, 0, 255);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glUseProgram(_program);
		glBindVertexArray(_vao);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		for (int i = 0; i < uniformCount; i++) {
			GLint uniform = glGetUniformLocation(_program, uniformVariables[i].name.c_str());

			if (uniform != GL_INVALID_INDEX) {
				switch (uniformVariables[i].type) {
				case Shader::Uniform::Type::FLOAT1F:
					glUniform1f(uniform, uniformVariables[i].float1fValue);
					break;
				case Shader::Uniform::Type::INT1I:
					glUniform1i(uniform, uniformVariables[i].int1iValue);
				}
			}
		}

		int offset = 0;
		for (int i = 0; i < _sprites.size(); i++) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _sprites[i].texture);
			switch (_sprites[i].renderType) {
			case Sprite::RenderType::TRIANGLE:
				glDrawArrays(GL_TRIANGLES, offset, 3);
				offset += 3;
				break;
			case Sprite::RenderType::RECTANGLE:
				glDrawArrays(GL_TRIANGLES, offset, 6);
				offset += 6;
			}
		}

		glBindVertexArray(0);
		glUseProgram(0);

		if (_doubleBuffered) { SDL_GL_SwapWindow(_window); }
		_sprites.clear();
		_vertices.clear();
	}

	void Window::addSprite(Sprite sprite) {
		_sprites.push_back(sprite);
	}

	void Window::_bindBuffers() {
		for (int i = 0; i < _sprites.size(); i++) {
			int vertexCount = 0;
			switch (_sprites[i].renderType) {
			case Sprite::RenderType::TRIANGLE:
				vertexCount = 3;
				break;
			case Sprite::RenderType::RECTANGLE:
				vertexCount = 6;
				break;
			}

			Vertex** spriteVertices = _sprites[i].generateVertices();
			for (int j = 0; j < vertexCount; j++) {
				_vertices.push_back(*spriteVertices[j]);
			}
			for (int j = 0; j < vertexCount; j++) {
				delete spriteVertices[j];
			}
			delete spriteVertices;
		}

		/*Vertex vertices[] = {
			Vertex(Position(-0.5f, -0.5f), Color(0, 0, 1, 255)),
			Vertex(Position(-0.5f, 0.5f), Color(1, 0, 0, 255)),
			Vertex(Position(0.5f, -0.5f), Color(0, 1, 0, 255))
		};*/

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), nullptr, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof(Vertex), _vertices.data());

		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}
