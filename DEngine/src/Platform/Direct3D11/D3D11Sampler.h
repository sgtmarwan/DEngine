#pragma once
#include <d3d11_4.h>

#include "DEngine/Graphics/Sampler.h"
namespace DEngine
{
	class D3D11Sampler : public Sampler
	{
	private:
		ID3D11SamplerState* m_SamplerState = nullptr;
	public:
		D3D11Sampler(ID3D11SamplerState* ss);
		~D3D11Sampler();
		void PSSet(unsigned int slot) override;
	};
}

