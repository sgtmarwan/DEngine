#pragma once

#include "DEngine/Graphics/GraphicsContext.h"

namespace DEngine
{
	enum class GraphicsAPI
	{
		Direct3D11 = 0
	};

	void SetupGraphicsContext(const GraphicsContext* gc, GraphicsAPI api);
}