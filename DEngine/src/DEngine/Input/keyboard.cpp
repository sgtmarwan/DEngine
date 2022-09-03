#include "keyboard.h"


namespace DEngine
{
	keyboard::keyboard()
	{
		KeysState.reset();
	}
	template <typename T>
	void keyboard::TrimBuffer(std::queue<T>& q)
	{
		while (q.size() > queueSize)
		{
			q.pop();
		}
	}
	bool keyboard::IsKeyDown(unsigned char KeyCode)
	{
		return KeysState[KeyCode];
	}
	bool keyboard::IsKeyUp(unsigned char KeyCode)
	{
		return !KeysState[KeyCode];
	}

	bool keyboard::IsKeyEmpty()
	{
		return KeysBuffer.empty();
	}
	bool keyboard::IsCharEmpty()
	{
		return CharsBuffer.empty();
	}

	void keyboard::SetAutoRepeat(bool ar)
	{
		AutoRepeat = ar;
	}

	keyboard::Event keyboard::ReadKey()
	{
		if (KeysBuffer.empty())
		{
			return keyboard::Event();
		}
		else
		{
			keyboard::Event k = KeysBuffer.front();
			KeysBuffer.pop();
			return k;
		}
	}

	char keyboard::ReadChar()
	{
		if (CharsBuffer.empty())
		{
			return 0;
		}
		else
		{
			char c = CharsBuffer.front();
			CharsBuffer.pop();
			return c;
		}
	}

	void keyboard::ClearKey()
	{
		KeysBuffer = std::queue<keyboard::Event>();
	}

	void keyboard::ClearChar()
	{
		CharsBuffer = std::queue<char>();
	}

	void keyboard::Clear()
	{
		KeysBuffer = std::queue<keyboard::Event>();
		CharsBuffer = std::queue<char>();
	}

	void keyboard::ClearState()
	{
		KeysState.reset();
	}


	void keyboard::OnKeyDown(unsigned char KeyCode)
	{
		KeysState.set(KeyCode, true);
		KeysBuffer.push(keyboard::Event(keyboard::Event::type::Down, KeyCode));
		TrimBuffer<keyboard::Event>(KeysBuffer);
	}
	void keyboard::OnKeyUp(unsigned char KeyCode)
	{
		KeysState.set(KeyCode, false);
		KeysBuffer.push(keyboard::Event(keyboard::Event::type::Up, KeyCode));
		TrimBuffer<keyboard::Event>(KeysBuffer);
	}

	void keyboard::OnChar(char c)
	{
		CharsBuffer.push(c);
		TrimBuffer<char>(CharsBuffer);
	}


}