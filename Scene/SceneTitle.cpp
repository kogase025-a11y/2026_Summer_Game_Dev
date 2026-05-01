#include "SceneTitle.h"

#include "../Manager/FileManager.h"

#include <cstring>

SceneTitle::SceneTitle(FileManager& fileMng)

{
}

void SceneTitle::Update()
{
	// ENTERでゲーム開始
	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
	{
		EndScene(SceneID::GAME);
	}
}

void SceneTitle::Draw()
{
	// タイトル背景とボタン風UIを描画
	const int width = 1920;
	const int height = 1080;
	const int centerX = width / 2;
	auto drawCenterText = [centerX](int y, const char* text, int color)
	{
		const int textW = GetDrawStringWidth(text, static_cast<int>(std::strlen(text)));
		DrawString(centerX - textW / 2, y, text, color);
	};

	DrawBox(0, 0, width, height, GetColor(10, 10, 30), TRUE);
	DrawBox(40, 40, width - 40, height - 40, GetColor(180, 20, 20), FALSE);

	drawCenterText(35, "TITLE", GetColor(255, 255, 255));
	drawCenterText(65, "PRESS ENTER TO START", GetColor(220, 220, 220));

	DrawBox(centerX - 320, 430, centerX + 320, 650, GetColor(255, 215, 0), TRUE);
	DrawBox(centerX - 300, 450, centerX + 300, 630, GetColor(180, 0, 0), TRUE);
	DrawBox(centerX - 300, 450, centerX + 300, 630, GetColor(255, 255, 255), FALSE);
	drawCenterText(530, "PUSH START", GetColor(255, 255, 255));
}
