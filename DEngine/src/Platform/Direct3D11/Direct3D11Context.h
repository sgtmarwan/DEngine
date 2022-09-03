#pragma once
#include "Platform/Windows/DEW.h"
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include "DEngine/Graphics/GraphicsContext.h"
namespace DEngine
{
	class Direct3D11Context : public GraphicsContext
	{
	private:
		ID3D11Device5* device = nullptr;
		ID3D11DeviceContext4* deviceContext = nullptr;
		IDXGISwapChain4* swapChain = nullptr;
		ID3D11RenderTargetView1* renderTargetView = nullptr;
		ID3D11Texture2D* depthStencilTexture = nullptr;
		ID3D11DepthStencilView* depthStencilView = nullptr;
		ID3D11DepthStencilState* depthStencilState = nullptr;
		ID3D11RasterizerState2* rasterizerState = nullptr;
		D3D11_VIEWPORT viewport = { 0 };
		DXGI_PRESENT_PARAMETERS presentParameters = { 0 };
	public:
		Direct3D11Context(const HWND& hWnd, unsigned short backBufferCount, unsigned short vsync);
		~Direct3D11Context();
		void ChangeRes(unsigned int width, unsigned int height) override;
		void Resize(unsigned int width, unsigned int height) override;
		void ClearBackBuffer(Vector4 color, float depth, char stencil) override;
		void PresentFrame() override;
		void Draw(unsigned int indicesCount) const override;

	public:
		ID3D11Device5* GetDevice();
		ID3D11DeviceContext4* GetDeviceContext();
	private:
		void CreateDeviceAndContext(D3D_DRIVER_TYPE driverType);
		void CreateSwapChain(const HWND& hwnd);
		void SetOMStates();
		void SetViewport(float width, float height);
	};
}