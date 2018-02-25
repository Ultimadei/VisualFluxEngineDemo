#include <VisualFlux/Window.h>
#include <VisualFlux/fileIO.h>
#include <VisualFlux/ResourceCache.h>
#include <VisualFlux/Vertex.h>

#include <conio.h>

extern "C" { _declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001; }

using namespace VisualFlux;

VisualFlux::Window* window;

void init() 
{
	window = new VisualFlux::Window("Title", 500, 200, 1024, 768, "Data/Shaders/color.vert", "Data/Shaders/color.frag", true, true);
}

int main(int argc, char** argv) 
{
	float time = 0;
	init();

	auto textureCache = VisualFlux::ResourceCache<VisualFlux::Texture, std::string>();

	const auto texture = textureCache.getCachedResource("Data/Textures/1_orb.png", VisualFlux::readImage("Data/Textures/1_orb.png"));

	while (true) 
	{
		// window->draw();
		window->addSprite(Sprite(Position(0.0f, 0.0f), Color(0.0f, 0.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0, Sprite::CollisionType::TRIANGLE, Sprite::RenderType::TRIANGLE));
		window->addSprite(Sprite(Position(-1.0f, 0.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f, texture.id, Sprite::CollisionType::TRIANGLE, Sprite::RenderType::RECTANGLE));
		Shader::Uniform uniforms[2] = 
		{
			Shader::Uniform("time", Shader::Uniform::Type::FLOAT1F, (float)time),
			Shader::Uniform("sampler", Shader::Uniform::Type::INT1I, (int)0)
		};
		window->draw(uniforms, 1);
		time += 0.01f;
	}
	_getch();

	return 0;
}