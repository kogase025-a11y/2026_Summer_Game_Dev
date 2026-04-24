#pragma once

#include <DxLib.h>
#include <array>

class InputManager
{
public:
	// DxLibのキー配列サイズ
	static constexpr int KEY_COUNT = 256;

	// 入力状態を1フレーム分更新
	void Update()
	{
		prev_ = curr_;
		GetHitKeyStateAll(curr_.data());
	}

	// 押下中
	bool IsPress(int keyCode) const
	{
		if (!IsValidKeyCode(keyCode))
		{
			return false;
		}
		return curr_[keyCode] != 0;
	}

	// このフレームで押された
	bool IsTrigger(int keyCode) const
	{
		if (!IsValidKeyCode(keyCode))
		{
			return false;
		}
		return (curr_[keyCode] != 0) && (prev_[keyCode] == 0);
	}

	// このフレームで離された
	bool IsRelease(int keyCode) const
	{
		if (!IsValidKeyCode(keyCode))
		{
			return false;
		}
		return (curr_[keyCode] == 0) && (prev_[keyCode] != 0);
	}

private:
	// 有効なキーコードか判定
	static bool IsValidKeyCode(int keyCode)
	{
		return (0 <= keyCode) && (keyCode < KEY_COUNT);
	}

	std::array<char, KEY_COUNT> curr_{};
	std::array<char, KEY_COUNT> prev_{};
};
