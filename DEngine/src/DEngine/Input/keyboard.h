#pragma once

#include <bitset>
#include <queue>

#include "KeyCodes.h"
namespace DEngine
{
	class keyboard
	{
		friend class WinWindow;
	public:
		class Event
		{
		public:
			enum class type
			{
				Up = 0, Down, Invalid = -1
			};
		public:
			const type Type;
			const unsigned char KeyCode;
			bool IsDown()
			{
				return (bool)Type;
			}
			Event() :
				Type(type::Invalid), KeyCode(0)
			{

			}
			Event(type t, unsigned char k) :
				KeyCode(k), Type(t)
			{

			}
		};
	public:
		keyboard();
		bool IsKeyDown(unsigned char KeyCode);
		bool IsKeyUp(unsigned char KeyCode);
		bool IsCharEmpty();
		bool IsKeyEmpty();
		Event ReadKey();
		char ReadChar();
		void Clear();
		void ClearKey();
		void ClearChar();
		void ClearState();

		void SetAutoRepeat(bool ar);
	private:
		static constexpr unsigned int nKeys = 256;
		static constexpr unsigned int queueSize = 16;

		bool AutoRepeat = true;
		void OnKeyDown(unsigned char KeyCode);
		void OnKeyUp(unsigned char KeyCode);
		void OnChar(char c);
		std::bitset<nKeys> KeysState;
		std::queue<Event> KeysBuffer;
		std::queue<char> CharsBuffer;
		template <typename T>
		void TrimBuffer(std::queue<T>& q);
	};
}