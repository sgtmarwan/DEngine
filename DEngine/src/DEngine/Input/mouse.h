#pragma once
#include <bitset>

namespace DEngine
{
	class mouse //TODO: Complete This
	{
		friend class WinWindow;
	public :
		mouse();
		bool IsButtonDown(unsigned int btn);
		bool IsButtonUp(unsigned int btn);
		bool IsInWindow();
		float GetPosX();
		float GetPosY();
		void ClearState();

	private:
		static constexpr unsigned int nButtons = 3u;

		float x, y;
		bool isInWindow = false;
		void OnLeave();
		void OnEnter();
		void OnMove(float _x, float _y);
		void OnButtonDown(float _x, float _y, unsigned int btn);
		void OnButtonUp(float _x, float _y, unsigned int btn);


		std::bitset<nButtons> ButtonsState;
	};
}