#include "TestGame.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#include "DEngine.h"
#include "DEngine/Graphics/Camera.h"
#include "Math/Matrix4x4.h"
#include "Math/Quaternion.h"



constexpr float PI = 22.0f / 7.0f;
constexpr float deg2rad = PI / 180.0f;


void** ReadSource(char** source, unsigned int c, size_t** sizes)
{
	std::ifstream file;

	char** src = new char*[c];
	*sizes = new size_t[c];

	for (unsigned int i = 0; i < c; ++i)
	{
		file.open(source[i], std::ios_base::binary);
		if (!file.is_open())
			return nullptr;
		size_t fileSize = std::filesystem::file_size(std::filesystem::path(source[i]));
		(* sizes)[i] = fileSize;
		src[i] = new char[fileSize];
		file.read(src[i], fileSize);
		file.close();
	}
	return (void**)src;
	
}



namespace DEngine
{


	TestGame::TestGame(unsigned int width, unsigned int height)
	{
		WinWindow* WinWnd = new WinWindow(L"TestGame", L"CLS", width, height);
		gc = new Direct3D11Context(WinWnd->GetWindowHandle(), 3, 0);
		gf = new D3D11GraphicsFactory((Direct3D11Context*)gc);
		kbd = new keyboard();
		Mouse = new mouse();
		WinWnd->SetGraphicsContext(gc);
		WinWnd->SetKeyboard(kbd);
		WinWnd->SetMouse(Mouse);
		SetupGraphicsContext(gc, GraphicsAPI::Direct3D11);
		wnd = WinWnd;
	}

	void TestGame::Run(Vertex* verts, unsigned int vertsCount, unsigned int* ind, unsigned int count, char** vs, unsigned int vsc, char** ps, unsigned int psc, INPUT_LAYOUT* il, unsigned int ilc, void* image, unsigned int width, unsigned int height, unsigned int cc)
	{
		Matrix4x4* color = new Matrix4x4();
		Quaternion quat = Quaternion(Vector3::Forward, 90.0f * deg2rad);
		Matrix4x4 rot = Matrix4x4::Rotate(quat);
		*color = rot;//* Matrix4x4::PrespectiveProjection(720.f/1280.0f,  90.0f * deg2rad, 0.5f, 10.0f) ;



		Mesh* mesh = gf->CreateMesh(verts, vertsCount, ind, count);
		size_t* vs_s, * ps_s;
		void** vs_sources = ReadSource(vs, vsc, &vs_s);
		void** ps_sources = ReadSource(ps, psc, &ps_s);
		Shader* shader = gf->CreateShader(vs_sources, vs_s, 1, ps_sources, ps_s, 1, il, ilc);
		Texture2D* tex = gf->CreateTexture2D(image, width, height, TEXTURE2D_FOMAT::RGBA8_UNORM,DATA_USAGE::GRW, 0);
		Sampler* sampl = gf->CreateSampler();
		mesh->Bind(0);
		shader->Bind();
		tex->PSSet(0);
		sampl->PSSet(0);
		ShaderData* psData = gf->CreateShaderData((void*) color, sizeof(Matrix4x4), DATA_USAGE::GR_CW);
		psData->VSSet(0);
		wnd->Show();
		while (wnd->Update())
		{
			gc->ClearBackBuffer({ 1.0f, 0.8f, 0.4f, 1.0f }, 1, 0);
			gc->Draw(mesh->GetIndicesCount());
			gc->PresentFrame();
		}

		delete color;
		delete mesh;
		delete shader;
	}

	TestGame::~TestGame()
	{
		delete wnd;
		delete gf;
		delete gc;
	}
}


