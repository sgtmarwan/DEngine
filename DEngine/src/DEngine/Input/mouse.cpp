#include "mouse.h"

namespace DEngine
{
	mouse::mouse()
	{
		ButtonsState.reset();
	}

	void mouse::ClearState()
	{
		ButtonsState.reset();
	}

	bool mouse::IsButtonDown(unsigned int btn)
	{
		return ButtonsState[btn];
	}
	bool mouse::IsButtonUp(unsigned int btn)
	{
		return !ButtonsState[btn];
	}
	float mouse::GetPosX()
	{
		return x;
	}
	float mouse::GetPosY()
	{
		return y;
	}
	void mouse::OnMove(float _x, float _y)
	{
		x = (_x * 2) - 1;
		y = 1 - (_y * 2);
	}
	void mouse::OnLeave()
	{
		isInWindow = false;
	}
	void mouse::OnEnter()
	{
		isInWindow = true;
	}
	void mouse::OnButtonDown(float _x, float _y, unsigned int btn)
	{
		ButtonsState.set(btn, true);
		x = (_x * 2) - 1;
		y = 1 - (_y * 2);
	}
	void mouse::OnButtonUp(float _x, float _y, unsigned int btn)
	{
		ButtonsState.set(btn, false);
		x = (_x * 2) - 1;
		y = 1 - (_y * 2);
	}
	bool mouse::IsInWindow()
	{
		return isInWindow;
	}
}