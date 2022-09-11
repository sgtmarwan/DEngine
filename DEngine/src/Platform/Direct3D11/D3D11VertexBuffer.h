#pragma once
#include <d3d11_4.h>
#include "Direct3D11Context.h"
#include "DEngine/Graphics/VertexBuffer.h"

namespace DEngine
{
	class D3D11VertexBuffer : public VertexBuffer
	{
	private:
		static Direct3D11Context* graphicsContext;
	public:
		static void SetGraphicsContext(Direct3D11Context* gc);
	private:
		ID3D11Buffer* vertexBuffer = nullptr;
	public:
		D3D11VertexBuffer(ID3D11Buffer* vb, unsigned int stride);
		virtual ~D3D11VertexBuffer();
		void Bind(const unsigned int slot);
		void UpdateData(void* data, unsigned int size, unsigned int offset);
		void* GetDataPointer(bool wait) const;
		void ReleaseDataPointer() const;
	};
}