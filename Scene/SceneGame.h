#pragma once
#include "SceneSuper.h"
#include <DxLib.h>

class FileManager;
class SceneManager;

class SceneGame : public SceneSuper
{
public:
	SceneGame(FileManager&, SceneManager*) {}

	void Update() override
	{
		if (CheckHitKey(KEY_INPUT_C) != 0)
		{
			EndScene(SceneID::CLEAR);
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			EndScene(SceneID::EXIT);
		}
	}

	void Draw() override
	{
		DrawString(20, 80, "GAME: C=CLEAR, ESC=EXIT", GetColor(0, 255, 255));
	}
private:
	
};
