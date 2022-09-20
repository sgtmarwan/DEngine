#include "D3D11_DATA_USAGE.h"

namespace DEngine
{
	D3D11_USAGE GetUsage(DEngine::DATA_USAGE usage)
	{
		switch (usage)
		{
		case DEngine::DATA_USAGE::GRW:
			return D3D11_USAGE_DEFAULT;
			break;
		case DEngine::DATA_USAGE::GR_CW:
			return D3D11_USAGE_DYNAMIC;
			break;
		case DEngine::DATA_USAGE::GR:
			return D3D11_USAGE_IMMUTABLE;
			break;
		case DEngine::DATA_USAGE::GW_CR:
			return D3D11_USAGE_STAGING;
			break;
		default:
			return D3D11_USAGE_DEFAULT;
			break;
		}
	}
	int GetCPUAccessFlags(DEngine::DATA_USAGE usage)
	{
		switch (usage)
		{
		case DEngine::DATA_USAGE::GRW:
			return 0;
			break;
		case DEngine::DATA_USAGE::GR_CW:
			return D3D11_CPU_ACCESS_WRITE;
			break;
		case DEngine::DATA_USAGE::GR:
			return 0;
			break;
		case DEngine::DATA_USAGE::GW_CR:
			return D3D11_CPU_ACCESS_READ;
			break;
		default:
			return 0;
			break;
		}
	}
}