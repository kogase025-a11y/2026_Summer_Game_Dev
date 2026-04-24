#pragma once

#include <DxLib.h>
#include <array>

class InputManager
{
public:
	static constexpr int KEY_COUNT = 256;

	void Update()
	{
		prev_ = curr_;
		GetHitKeyStateAll(curr_.data());
	}

	bool IsPress(int keyCode) const
	{
		if (!IsValidKeyCode(keyCode))
		{
			return false;
		}
		return curr_[keyCode] != 0;
	}

	bool IsTrigger(int keyCode) const
	{
		if (!IsValidKeyCode(keyCode))
		{
			return false;
		}
		return (curr_[keyCode] != 0) && (prev_[keyCode] == 0);
	}

	bool IsRelease(int keyCode) const
	{
		if (!IsValidKeyCode(keyCode))
		{
			return false;
		}
		return (curr_[keyCode] == 0) && (prev_[keyCode] != 0);
	}

private:
	static bool IsValidKeyCode(int keyCode)
	{
		return (0 <= keyCode) && (keyCode < KEY_COUNT);
	}

	std::array<char, KEY_COUNT> curr_{};
	std::array<char, KEY_COUNT> prev_{};
};
