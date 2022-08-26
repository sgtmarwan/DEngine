#include "TestGame.h"
#include <fstream>
#include <iostream>
#include <filesystem>

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
		std::filesystem::file_size(std::filesystem::path(source[i]));
		//file.seekg(0, std::ios::end);
		//size_t fileSize = file.tellg();
		size_t fileSize = std::filesystem::file_size(std::filesystem::path(source[i]));
		(* sizes)[i] = fileSize;
		//file.seekg(0, std::ios::beg);
		src[i] = new char[fileSize];
			// read the file
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
		D3D11Mesh::SetGraphicsContext((Direct3D11Context*)gc);
		D3D11Shader::SetGraphicsContext((Direct3D11Context*)gc);
		WinWnd->SetGraphicsContext(gc);
		wnd = WinWnd;
	}

	void TestGame::Run(Vertex* verts, unsigned int vertsCount,unsigned int* ind, unsigned int count, char** vs, unsigned int vsc, char** ps, unsigned int psc,INPUT_LAYOUT* il, unsigned int ilc)
	{
		Vector4* color = new Vector4();
		*color = { 0.5f, 0.3f, 0.7f, 1.0f };
		unsigned int colorSizes[] = { {sizeof(float) * 4} };
		Mesh* mesh = gf->CreateMesh(verts, vertsCount, ind, count);
		size_t* vs_s, * ps_s;
		void** vs_sources = ReadSource(vs, vsc, &vs_s);
		void** ps_sources = ReadSource(ps, psc, &ps_s);
		Shader* shader = gf->CreateShader(vs_sources, vs_s, 1, ps_sources, ps_s, 1, il, ilc);
		mesh->Bind();
		shader->Bind();
		ShaderData* psData = gf->CreateShaderData((void**) & color, colorSizes, 1, DATA_USAGE::GR_CW);
		shader->SetPSShaderData(psData, 0);
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


