#include "Direct3D11Context.h"
namespace DEngine
{
	Direct3D11Context* Direct3D11Context::s_GraphicsContext = nullptr;
	Direct3D11Context::Direct3D11Context(const HWND& hWnd, unsigned short backBufferCount, unsigned short vsync) :
		GraphicsContext(backBufferCount, vsync)
	{
		CreateDeviceAndContext(D3D_DRIVER_TYPE_HARDWARE);
		CreateSwapChain(hWnd);
		RECT winRect;
		GetClientRect(hWnd, &winRect);
		Resize((winRect.right - winRect.left), (winRect.bottom - winRect.top));
		SetOMStates();
		presentParameters.DirtyRectsCount = 0;
		presentParameters.pDirtyRects = 0;
		presentParameters.pScrollOffset = 0;
		presentParameters.pScrollRect = 0;
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	Direct3D11Context::~Direct3D11Context()
	{
		if (depthStencilTexture != nullptr) depthStencilTexture->Release();
		if (depthStencilState != nullptr) depthStencilState->Release();
		if (rasterizerState != nullptr) rasterizerState->Release();
		if (depthStencilView != nullptr) depthStencilView->Release();
		if (renderTargetView != nullptr) renderTargetView->Release();
		if (swapChain != nullptr) swapChain->Release();
		if (deviceContext != nullptr) deviceContext->Release();
		if (device != nullptr) device->Release();
	}
	void Direct3D11Context::Draw(unsigned int indicesCount) const
	{
		deviceContext->DrawIndexed(indicesCount, 0, 0);
	}
	void Direct3D11Context::SetRes(unsigned int width, unsigned int height)
	{
		DXGI_MODE_DESC dmd = {};
		dmd.Width = width;
		dmd.Height = height;
		dmd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		dmd.RefreshRate.Numerator = 60;
		dmd.RefreshRate.Denominator = 1;
		dmd.Scaling = DXGI_MODE_SCALING_CENTERED;
		dmd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChain->ResizeTarget(&dmd);
	}
	void Direct3D11Context::Resize(unsigned int width, unsigned int height)
	{
		if (renderTargetView != nullptr)
			renderTargetView->Release();
		if (depthStencilView != nullptr)
			depthStencilView->Release();
		if (frameBuffer != nullptr)
			frameBuffer->Release();
		swapChain->ResizeBuffers(m_BackBufferCount, width, height, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&frameBuffer));
		device->CreateRenderTargetView1(frameBuffer, nullptr, &renderTargetView);
		D3D11_TEXTURE2D_DESC depthStencilBufferDesc = {};
		depthStencilBufferDesc.Width = width;
		depthStencilBufferDesc.Height = height;
		depthStencilBufferDesc.MipLevels = 1;
		depthStencilBufferDesc.ArraySize = 1;
		depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilBufferDesc.SampleDesc.Count = 1;
		depthStencilBufferDesc.SampleDesc.Quality = 0;
		depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilBufferDesc.CPUAccessFlags = 0;
		depthStencilBufferDesc.MiscFlags = 0;
		if (depthStencilTexture != nullptr)
			depthStencilTexture->Release();
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = depthStencilBufferDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		device->CreateTexture2D(&depthStencilBufferDesc, NULL, &depthStencilTexture);
		device->CreateDepthStencilView(depthStencilTexture, NULL, &depthStencilView);
		SetViewport((float)width, (float)height);
		deviceContext->OMSetRenderTargets(1, (ID3D11RenderTargetView**) & renderTargetView, depthStencilView);
	}
	void Direct3D11Context::PresentFrame()
	{
		swapChain->Present1(m_Vsync, 0u, &presentParameters);
		deviceContext->OMSetRenderTargets(1, (ID3D11RenderTargetView**)&renderTargetView, depthStencilView);
		m_CurrentBackBuffer = (m_CurrentBackBuffer + 1) % m_BackBufferCount;
	}
	ID3D11Device5* Direct3D11Context::GetDevice()
	{
		return device;
	}
	ID3D11DeviceContext4* Direct3D11Context::GetDeviceContext()
	{
		return deviceContext;
	}
	void Direct3D11Context::ClearBackBuffer(const Vector4& color)
	{
		deviceContext->ClearRenderTargetView(renderTargetView, (float*) & color);
	}
	void Direct3D11Context::ClearDepthBuffer(float depth)
	{
		deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, depth, 0);
	}
	void Direct3D11Context::CreateDeviceAndContext(D3D_DRIVER_TYPE driverType)
	{
		UINT creationFlags = 0;
#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		ID3D11Device* d;
		ID3D11DeviceContext* dc;             // Crashs for some reason
		D3D11CreateDevice(0, driverType, 0, 0/*creationFlags*/, nullptr, 0, D3D11_SDK_VERSION, &d, nullptr, &dc);
		d->QueryInterface<ID3D11Device5>(&device);
		dc->QueryInterface<ID3D11DeviceContext4>(&deviceContext);
		d->Release();
		dc->Release();
	}
	void Direct3D11Context::CreateSwapChain(const HWND& hwnd)
	{
		IDXGIFactory4* factory;
		CreateDXGIFactory2(0, __uuidof(IDXGIFactory4), (void**)&factory);
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = 0;
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = FALSE;
		swapChainDesc.SampleDesc = { 1, 0 };
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = m_BackBufferCount;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Flags = 0;
		factory->CreateSwapChainForHwnd(
			device,
			hwnd,
			&swapChainDesc,
			nullptr,
			nullptr,
			&swapChain);
		factory->Release();
	}
	void Direct3D11Context::SetOMStates()
	{
		D3D11_RASTERIZER_DESC2 rasterizerDesc = {};

		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;
		rasterizerDesc.ConservativeRaster = D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF;
		rasterizerDesc.ForcedSampleCount = 0;

		device->CreateRasterizerState2(&rasterizerDesc, &rasterizerState);

		deviceContext->RSSetState(rasterizerState);


		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};

		depthStencilStateDesc.DepthEnable = TRUE;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilStateDesc.StencilEnable = FALSE;

		device->CreateDepthStencilState(&depthStencilStateDesc, &depthStencilState);

		deviceContext->OMSetDepthStencilState(depthStencilState, 1);
	}
	void Direct3D11Context::SetViewport(float width, float height)
	{
		viewport.Width = width;
		viewport.Height = height;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		deviceContext->RSSetViewports(1, &viewport);
	}
	Direct3D11Context* Direct3D11Context::Get()
	{
		return s_GraphicsContext;
	}
	void Direct3D11Context::Set(Direct3D11Context* gc)
	{
		s_GraphicsContext = gc;
	}
}
