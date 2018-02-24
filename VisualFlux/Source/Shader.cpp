#include <VisualFlux/Shader.h>
#include <fstream>
#include <sstream>

namespace VisualFlux
{
	VisualFlux::Shader::Shader(const char* filePath, GLenum type) : _filePath(filePath), _shaderID(glCreateShader(type)) {
		_compileShader();
	}

	Shader::~Shader() {
	}

	void Shader::_compileShader() {
		// Used for getting the glsl code from the shader files
		std::ifstream shaderIO;
		std::stringstream file;

		shaderIO.open(_filePath);
		// Read the entire file into one string stream
		file << shaderIO.rdbuf();

		shaderIO.close();

		// Read the string streams contents into a normal string
		std::string shaderSource = file.str();
		// Read into a c string
		const char* shadercstr = shaderSource.c_str();

		// Compile the shader
		glShaderSource(_shaderID, 1, &shadercstr, nullptr);
		glCompileShader(_shaderID);

		// Now do error checking for the compilation process
		int success;
		glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			char error[512];
			glGetShaderInfoLog(_shaderID, 512, nullptr, error);
			printf("\n%s\n", error);
		}
	}

	void Shader::attachShader(GLuint program) {
		glAttachShader(program, _shaderID);
	}
}

