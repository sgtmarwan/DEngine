#include "D3D11Sampler.h"

#include "Direct3D11Context.h"
namespace DEngine {

	D3D11Sampler::D3D11Sampler(ID3D11SamplerState* ss) :
		m_SamplerState(ss)
	{
	}

	D3D11Sampler::~D3D11Sampler()
	{
		if (m_SamplerState != nullptr) m_SamplerState->Release();
	}
	void D3D11Sampler::PSSet(unsigned int slot)
	{
		Direct3D11Context::Get()->GetDeviceContext()->PSSetSamplers(slot, 1, &m_SamplerState);
	}
}
