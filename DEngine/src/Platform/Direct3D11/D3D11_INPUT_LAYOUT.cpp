#include "D3D11_INPUT_LAYOUT.h"

namespace DEngine
{
	DXGI_FORMAT GetInputFormat(DEngine::INPUT_FORMAT format)
	{
		switch (format)
		{
		case DEngine::INPUT_FORMAT::int32_1:
			return DXGI_FORMAT_R32_SINT;
			break;
		case DEngine::INPUT_FORMAT::uint32_1:
			return DXGI_FORMAT_R32_UINT;
			break;
		case DEngine::INPUT_FORMAT::uint8_4:
			return DXGI_FORMAT_R8G8B8A8_UINT;
			break;
		case DEngine::INPUT_FORMAT::float32_1:
			return DXGI_FORMAT_R32_FLOAT;
			break;
		case DEngine::INPUT_FORMAT::float32_2:
			return DXGI_FORMAT_R32G32_FLOAT;
			break;
		case DEngine::INPUT_FORMAT::float32_3:
			return DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case DEngine::INPUT_FORMAT::float32_4:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		default:
			return DXGI_FORMAT_UNKNOWN;
			break;
		}
	}
}