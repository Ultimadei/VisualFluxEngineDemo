#include <VisualFlux/Window.h>
#include <VisualFlux/fileIO.h>

#include <conio.h>

extern "C" { _declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001; }

VisualFlux::Window* window;

void init() 
{
	window = new VisualFlux::Window("Title", 500, 200, 1024, 768, "Data/Shaders/color.vert", "Data/Shaders/color.frag", true, true);
}

int main(int argc, char** argv) 
{
	float time = 0;
	init();

	const auto texture = VisualFlux::readImage("Data/Textures/1_orb.png");

	while (true) 
	{
		// window->draw();
		window->addSprite(Sprite(Position(0.0f, 0.0f), Color(0.0f, 0.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0, Sprite::CollisionType::TRIANGLE, Sprite::RenderType::TRIANGLE));
		window->addSprite(Sprite(Position(-1.0f, 0.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f, texture.id, Sprite::CollisionType::TRIANGLE, Sprite::RenderType::RECTANGLE));
		VisualFlux::Shader::Uniform uniforms[2] = 
		{
			VisualFlux::Shader::Uniform("time", VisualFlux::Shader::Uniform::Type::FLOAT1F, (float)time),
			VisualFlux::Shader::Uniform("sampler", VisualFlux::Shader::Uniform::Type::INT1I, (int)0)
		};
		window->draw(uniforms, 1);
		time += 0.01f;
	}
	_getch();

	return 0;
}