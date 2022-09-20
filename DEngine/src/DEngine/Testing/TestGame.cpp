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
		Direct3D11Context::Set((Direct3D11Context*)gc);
		gf = new D3D11GraphicsFactory();
		GraphicsFactory::Set(gf);
		kbd = new keyboard();
		Mouse = new mouse();
		WinWnd->SetGraphicsContext(gc);
		WinWnd->SetKeyboard(kbd);
		WinWnd->SetMouse(Mouse);
		wnd = WinWnd;
	}

	void TestGame::Run(Vertex* verts, unsigned int vertsCount, unsigned int* ind, unsigned int count, char** vs, unsigned int vsc, char** ps, unsigned int psc, INPUT_LAYOUT* il, unsigned int ilc, void* image, unsigned int width, unsigned int height, unsigned int cc)
	{
		Matrix4x4* color = new Matrix4x4[5];
		Quaternion quat = Quaternion(Vector3::Normalize(Vector3(0.0f, 1.0f, 1.0f)), 45.0f * deg2rad);
		Matrix4x4 rot = Matrix4x4::Rotate(quat);
		Camera cam(DEngine::ProjectionMode::Prespective, 1280, 720, 90, 0.5, 10);
		color[0] = cam.GetProjectionMatrix() * (Matrix4x4::Translate(Vector3(0.0f, 0, 0)) * rot * Matrix4x4::Scale(Vector3(1)));
		Mesh* mesh = new Mesh(verts, vertsCount, ind, count);
		size_t* vs_s, * ps_s;
		void** vs_sources = ReadSource(vs, vsc, &vs_s);
		void** ps_sources = ReadSource(ps, psc, &ps_s);
		Shader* shader = gf->CreateShader(vs_sources, vs_s, 1, ps_sources, ps_s, 1, il, ilc);
		Texture2D* tex = gf->CreateTexture2D(image, width, height, TEXTURE2D_FORMAT::RGBA8_UNORM,DATA_USAGE::GRW, 0);
		Sampler* sampl = gf->CreateSampler();
		mesh->Bind(0);
		shader->Bind();
		tex->PSSet(0);
		sampl->PSSet(0);
		Buffer* psData = gf->CreateBuffer((void*) color, 5 * sizeof(Matrix4x4), DATA_USAGE::GR_CW, BUFFER_TYPE::ShaderBuffer);
		psData->VSSet(0);
		wnd->Show();
		float movev = 0;
		float moveh = 0;
		float movez = 0;
		float c = 0.1;
		float v = 0.1;
		float t = 45;
		while (wnd->Update())
		{
			{
				if (kbd->IsKeyDown(DEKC_UP))
				{
					movev += 0.01f;
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown(DEKC_DOWN))
				{
					movev -= 0.01f;
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown(DEKC_RIGHT))
				{
					moveh += 0.01f;
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown(DEKC_LEFT))
				{
					moveh -= 0.01f;
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown('E'))
				{
					movez += 0.01f;
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown('R'))
				{
					movez -= 0.01f;
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown('Z'))
				{
					t += 0.5;
					quat = Quaternion(Vector3::Normalize(Vector3(0.0f, 1.0f, 0.0f)), t * deg2rad);
					rot = Matrix4x4::Rotate(quat);
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
				if (kbd->IsKeyDown('S'))
				{
					t -= 0.5;
					quat = Quaternion(Vector3::Normalize(Vector3(0.0f, 1.0f, 0.0f)), t * deg2rad);
					rot = Matrix4x4::Rotate(quat);
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					memcpy(psData->Map(true), color, sizeof(Matrix4x4));
					psData->UnMap();
				}
			}
			/* {
				if (kbd->IsKeyDown('C'))
				{
					cam.Rotate(Quaternion(Vector3::Up, -c * 2 * deg2rad));
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					psData->UpdateData(color, 1 * sizeof(Matrix4x4), 0);
				}
				if (kbd->IsKeyDown('V'))
				{
					cam.Rotate(Quaternion(Vector3::Up, c * 2 * deg2rad));
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					psData->UpdateData(color, 1 * sizeof(Matrix4x4), 0);
				}
				if (kbd->IsKeyDown('W'))
				{
					cam.Rotate(Quaternion(Vector3::Right, v * 2 * deg2rad));
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					psData->UpdateData(color, 1 * sizeof(Matrix4x4), 0);
				}
				if (kbd->IsKeyDown('X'))
				{
					cam.Rotate(Quaternion(Vector3::Right, -v * 2 * deg2rad));
					*color = cam.GetProjectionMatrix()  * (Matrix4x4::Translate(Vector3(0.0f + moveh, 0 + movev, 0 + movez)) * rot * Matrix4x4::Scale(Vector3(1)));
					psData->UpdateData(color, 1 * sizeof(Matrix4x4), 0);
				}
			}*/
			gc->ClearBackBuffer({ 1.0f, 0.8f, 0.4f, 1.0f }, 1.0f, 0);
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


