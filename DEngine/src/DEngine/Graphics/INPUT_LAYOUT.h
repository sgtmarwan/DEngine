#pragma once

namespace DEngine
{
	enum class INPUT_FORMAT
	{
		int32_1 = 0, uint32_1, float32_1, float32_3, float32_4
	};

	struct INPUT_LAYOUT
	{
		char* Name;
		INPUT_FORMAT Format;
		unsigned int Index;
		unsigned int Offset;
	};
}