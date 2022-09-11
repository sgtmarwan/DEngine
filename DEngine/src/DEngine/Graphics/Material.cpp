#include "Material.h"

namespace DEngine
{

	const GraphicsFactory* Material::graphicsFactory = nullptr;

	void Material::SetGraphicsFactory(const GraphicsFactory* gf)
	{
		graphicsFactory = gf;
	}
}
