#include <TestGame.h>
#include <DEngine.h>
#include "stb_image.h"
#include <iostream>


int main()
{
	int width, height, cii;
	char* image = (char*)stbi_load("res/images/wood.png", &width, &height, &cii, 4);
	char* vs = (char*)"res/shaders/VertexShader.cso";
	char* ps = (char*)"res/shaders/PixelShader.cso";
	DEngine::Vertex verts[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}
	};
	unsigned int inds[] = {
		0,1,2,
		2,3,0
	};

	DEngine::INPUT_LAYOUT il[] = {
		{"POSITION", DEngine::INPUT_FORMAT::float32_3, 0, 0},
		{"norm", DEngine::INPUT_FORMAT::float32_3, 0, 12},
		{"TexCoords", DEngine::INPUT_FORMAT::float32_2, 0, 24}
	};
	DEngine::TestGame game(1280, 720);
	game.Run(verts, 4, inds, 6, &vs, 1, &ps, 1, il, 3, image, width, height, cii);
	return 0;
}