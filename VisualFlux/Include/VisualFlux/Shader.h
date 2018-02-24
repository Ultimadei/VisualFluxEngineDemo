#pragma once

#include <VisualFlux/OpenGL.h>
#include <string>

namespace VisualFlux
{
	class Shader {
	public:
		Shader(const char* filePath, GLenum type);
		~Shader();

		struct Uniform {
			std::string name;
			enum class Type {
				FLOAT1F,
				INT1I
			} type;
			float float1fValue;
			int int1iValue;
			Uniform(std::string name, Type type, float float1fValue = 0.0f) : name(name), type(type), float1fValue(float1fValue) {}
			Uniform(std::string name, Type type, int int1iValue = 0) : name(name), type(type), int1iValue(int1iValue) {}
		};

		void attachShader(GLuint program);
	private:
		void _compileShader();
		const char* _filePath;
		GLuint _shaderID;
	};
}