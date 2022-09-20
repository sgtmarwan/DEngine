#pragma once
#include <d3d11_4.h>

#include "DEngine/Graphics/DATA_USAGE.h"


namespace DEngine
{
	D3D11_USAGE GetUsage(DEngine::DATA_USAGE usage);
	int GetCPUAccessFlags(DEngine::DATA_USAGE usage);
}

