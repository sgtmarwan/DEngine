#include <TestGame.h>
#include <DEngine.h>

int main()
{
	char* vs = (char*)"res/shaders/VertexShader.cso";
	char* ps = (char*)"res/shaders/PixelShader.cso";
	DEngine::Vertex verts[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
	};
	unsigned int inds[] = {
		0,1,2,
		2,3,0
	};

	DEngine::INPUT_LAYOUT il[] = {
		{"POSITION", DEngine::INPUT_FORMAT::float32_4, 0, 0}
	};
	DEngine::TestGame game(1280, 720);
	game.Run(verts, 4, inds, 6, &vs, 1, &ps, 1, il, 1);
	return 0;
}