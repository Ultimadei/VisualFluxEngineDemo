#include <fstream>
#include <conio.h>

#include <VisualFlux/fileIO.h>
#include <VisualFlux/picoPNG.h>

namespace VisualFlux
{
	std::vector<unsigned char> readFile(const char* filePath) {
		std::ifstream input(filePath, std::ios::binary);
		perror("Error");
		if (input.fail()) {
			printf("File failed to open. Skipping");
			_getch();
			return std::vector<unsigned char>();
		}

		input.seekg(0, std::ios::end);
		int size = input.tellg();
		input.seekg(0, std::ios::beg);
		size -= input.tellg();

		std::vector<unsigned char> contents(size);
		input.read((char*)&contents[0], size);

		return contents;
	}

	Texture readImage(const char* filePath) {
		Texture texture = {};

		std::vector<unsigned char> buffer = readFile(filePath);
		if (buffer.size() == 0) {
			texture.id = 0;
			return texture;
		}

		std::vector<unsigned char> in(buffer.begin(), buffer.end());
		std::vector<unsigned char> out;
		unsigned long width, height;


		int error = decodePNG(out, width, height, &in[0], in.size());
		if (error != 0) {
			printf("Pico png error code %d\n", error);
		}

		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, false, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}