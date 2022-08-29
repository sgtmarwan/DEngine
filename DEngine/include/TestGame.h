#pragma once
#include "DEngineAPI.h"

#include "Platform/Windows/WinWindow.h"
#include "Platform/Direct3D11/Direct3D11Context.h"
#include "Platform/Direct3D11/D3D11GraphicsFactory.h"
#include "Platform/Direct3D11/D3D11Mesh.h"
#include "Platform/Direct3D11/D3D11Shader.h"
#include "Platform/Direct3D11/D3D11Texture2D.h"
namespace DEngine
{
	class DEAPI TestGame
	{
	private:
		Window* wnd;
		GraphicsContext* gc;
		GraphicsFactory* gf;
	public:
		TestGame(unsigned int width, unsigned int height);
		void Run(Vertex* verts, unsigned int vertsCount, unsigned int* ind, unsigned int count, char** vs, unsigned int vsc, char** ps, unsigned int psc, INPUT_LAYOUT* il, unsigned int ilc, void* image, unsigned int width, unsigned int height, unsigned int cc);
		~TestGame();
	};
}