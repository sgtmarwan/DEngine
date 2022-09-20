#pragma once
#include <d3d11_4.h>
#include "Direct3D11Context.h"
#include "DEngine/Graphics/Buffer.h"
#include "D3D11_DATA_USAGE.h"

namespace DEngine
{
	UINT GetBufferType(BUFFER_TYPE type);
	class D3D11Buffer : public Buffer
	{
	private:
		ID3D11Buffer* m_Buffer = nullptr;
	public:
		D3D11Buffer(ID3D11Buffer* buffer);
		virtual ~D3D11Buffer();
		void Update(void* data, unsigned int size, unsigned int offset) override;
		void* Map(bool wait) const override;
		void UnMap() const override;

		void BindIndexBuffer() override;
		void BindVertexBuffer(unsigned int slot, unsigned int stride) override;

		void VSSet(unsigned int slot) override;
		void PSSet(unsigned int slot) override;
	};
}