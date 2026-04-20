#pragma once
#include "SceneSuper.h"
#include <DxLib.h>

class FileManager;

class SceneClear : public SceneSuper
{
public:
	explicit SceneClear(FileManager&) {}

	void Update() override
	{
		if (CheckHitKey(KEY_INPUT_RETURN) != 0)
		{
			EndScene(SceneID::TITLE);
		}
	}

	void Draw() override
	{
		DrawString(20, 110, "CLEAR: PRESS ENTER", GetColor(0, 255, 0));
	}
};
