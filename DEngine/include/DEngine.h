#pragma once

#include "DEngine/Graphics/GraphicsContext.h"
#include "DEngine/Graphics/GraphicsFactory.h"

namespace DEngine
{
	enum class GraphicsAPI
	{
		Direct3D11 = 0
	};

	void SetupGraphicsContext(const GraphicsContext* gc, const GraphicsFactory* gf, GraphicsAPI api);

	extern GraphicsAPI GAPI;
}