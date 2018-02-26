#include <VisualFlux/Window.h>
#include <VisualFlux/fileIO.h>
#include <VisualFlux/ResourceCache.h>
#include <VisualFlux/Vertex.h>

#include <conio.h>

extern "C" { _declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001; }

using namespace VisualFlux;

Window* window;

void init() 
{
	window = new Window("Title", 500, 200, 1024, 768, "Data/Shaders/color.vert", "Data/Shaders/color.frag", true, true);
}

int main(int argc, char** argv) 
{
	float time = 0;
	init();

	auto textureCache = ResourceCache<Texture, std::string>();

	const auto texture = textureCache.getCachedResource("Data/Textures/1_orb.png", readImage("Data/Textures/1_orb.png"));
	auto triangle = Sprite(Position(0.0f, 0.0f), Color(0.0f, 0.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0, Sprite::CollisionType::TRIANGLE, Sprite::RenderType::TRIANGLE);
	auto orb = Sprite(Position(-1.0f, 0.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f, texture.id, Sprite::CollisionType::TRIANGLE, Sprite::RenderType::RECTANGLE);

	while (true) 
	{
		// window->draw();
		window->addSprite(triangle);
		window->addSprite(orb);
		Shader::Uniform uniforms[2] = 
		{
			Shader::Uniform("time", Shader::Uniform::Type::FLOAT1F, (float)time),
			Shader::Uniform("sampler", Shader::Uniform::Type::INT1I, (int)0)
		};
		window->draw(uniforms, 2);
		time += 0.01f;

		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				return 0;
			case SDL_KEYDOWN:
				window->addKey(sdlEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				window->removeKey(sdlEvent.key.keysym.sym);
				break;
			}
		}

		if (window->getKey(SDLK_w)) {
			orb.position.y += 0.01;
		}

		if (window->getKey(SDLK_a)) {
			orb.position.x -= 0.01;
		}

		if (window->getKey(SDLK_s)) {
			orb.position.y -= 0.01;
		}

		if (window->getKey(SDLK_d)) {
			orb.position.x += 0.01;
		}
	}
	_getch();

	return 0;
}