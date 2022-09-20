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
		{{-0.5f, 0.5f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, //0
		{{ 0.5f, 0.5f,   0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, //1
		{{ 0.5f,-0.5f,   0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //2
		{{-0.5f,-0.5f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, //3

		{{-0.5f, 0.5f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, //4
		{{ 0.5f, 0.5f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, //5
		{{ 0.5f,-0.5f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //6
		{{-0.5f,-0.5f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, //7
	};
	unsigned int inds[] = {
		2,1,0,
		0,3,2,

		4,5,6,
		6,7,4,

		5,1,2,
		2,6,5,

		3,0,4,
		4,7,3,

		1,5,4,
		4,0,1,

		7,6,2,
		2,3,7
	};

	DEngine::INPUT_LAYOUT il[] = {
		{"POSITION", DEngine::INPUT_FORMAT::float32_3, 0, 0},
		{"norm", DEngine::INPUT_FORMAT::float32_3, 0, 12},
		{"TexCoords", DEngine::INPUT_FORMAT::float32_2, 0, 24}
	};
	DEngine::TestGame game(1280, 720);
	game.Run(verts, 8, inds, 36, &vs, 1, &ps, 1, il, 3, image, width, height, cii);
	return 0;
}