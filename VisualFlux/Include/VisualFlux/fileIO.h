#pragma once

#include <VisualFlux/Vertex.h>
#include <Vector>

namespace VisualFlux  {
	extern std::vector<unsigned char> readFile(const char* filePath);
	extern Texture readImage(const char* filePath);
}