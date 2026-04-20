#pragma once
#include "SceneSuper.h"
#include <DxLib.h>
#include <cstring>

class FileManager;

class SceneTitle : public SceneSuper
{
public:
	explicit SceneTitle(FileManager&) {}

	void Update() override
	{
		if (CheckHitKey(KEY_INPUT_SPACE) != 0)
		{
			EndScene(SceneID::STAGE_SELECT);
			return;
		}

		if (CheckHitKey(KEY_INPUT_RETURN) != 0)
		{
			EndScene(SceneID::GAME);
		}
	}

	void Draw() override
	{
		const int width = 1920;
		const int height = 1080;
		const int centerX = width / 2;
		const int centerY = height / 2;
		auto drawCenterText = [centerX](int y, const char* text, int color)
		{
			const int textW = GetDrawStringWidth(text, static_cast<int>(std::strlen(text)));
			DrawString(centerX - textW / 2, y, text, color);
		};

		DrawBox(0, 0, width, height, GetColor(10, 10, 30), TRUE);
		DrawBox(40, 40, width - 40, height - 40, GetColor(180, 20, 20), FALSE);

		drawCenterText(30, "TITLE: PRESS SPACE FOR PACHINKO ROUTE", GetColor(255, 255, 255));
		drawCenterText(55, "PRESS ENTER FOR NORMAL GAME", GetColor(200, 200, 200));

		DrawBox(centerX - 320, centerY - 110, centerX + 320, centerY + 110, GetColor(255, 215, 0), TRUE);
		DrawBox(centerX - 300, centerY - 90, centerX + 300, centerY + 90, GetColor(180, 0, 0), TRUE);
		DrawBox(centerX - 300, centerY - 90, centerX + 300, centerY + 90, GetColor(255, 255, 255), FALSE);

		drawCenterText(centerY - 15, "PUSH BUTTON", GetColor(255, 255, 255));
	}
};
