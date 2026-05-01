#include "SceneGame.h"

#include "../Manager/FileManager.h"
#include "../Util/Rect.h"

#include <algorithm>

SceneGame::SceneGame(FileManager& fileMng, SceneManager* sceneMng)
	: player_(fileMng), fileMng_(fileMng), sceneMng_(sceneMng)
{
	player_.SystemInit();
	player_.GameInit();

	// Git Project の FileManager を使ってプレイヤー画像を取得
	// 画像が未配置でも player_.Draw 側で矩形描画にフォールバックする
	playerImage_ = fileMng_.LoadImageFM(kPlayerImagePath);
}

SceneGame::~SceneGame() = default;

void SceneGame::Update()
{
	// 入力状態更新
	input_.Update();

	// プレイヤー更新
	player_.Update(input_, kStageWidth);

	// プレイヤー中心にカメラを追従（ステージ外に出ないよう制限）
	const float targetCameraX = player_.GetX() - (kScreenWidth * 0.5f);
	const float cameraMax = kStageWidth - static_cast<float>(kScreenWidth);
	cameraX_ = (std::max)(0.0f, (std::min)(targetCameraX, cameraMax));

	// Git Project の Rect を使ったゴール当たり判定
	const Rect playerRect{ player_.GetX() - 24.0f, player_.GetY() - 48.0f, 48.0f, 48.0f };
	const Rect goalRect{ kGoalX - 16.0f, player_.GetGroundY() - 180.0f, 32.0f, 180.0f };
	if (playerRect.IsHit(goalRect))
	{
		EndScene(SceneID::CLEAR);
		return;
	}

	// 終了
	if (CheckHitKey(KEY_INPUT_C) != 0)
	{
		EndScene(SceneID::CLEAR);
		return;
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
	{
		EndScene(SceneID::EXIT);
	}
}

void SceneGame::Draw()
{
	// 背景
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(80, 170, 255), TRUE);

	// 地面
	const int groundY = static_cast<int>(player_.GetGroundY());
	DrawBox(0, groundY, kScreenWidth, kScreenHeight, GetColor(60, 170, 60), TRUE);

	// 段差（プレイヤーの判定と同じ位置）
	const int stepLeft = static_cast<int>(player_.GetStepStartX() - cameraX_);
	const int stepRight = static_cast<int>(player_.GetStepEndX() - cameraX_);
	const int stepTop = static_cast<int>(player_.GetStepTopY());
	DrawBox(stepLeft, stepTop, stepRight, groundY, GetColor(110, 110, 110), TRUE);

	// ゴール表示
	const int goalDrawX = static_cast<int>(kGoalX - cameraX_);
	DrawBox(goalDrawX - 8, groundY - 180, goalDrawX + 8, groundY, GetColor(255, 255, 255), TRUE);
	DrawTriangle(goalDrawX + 8, groundY - 180, goalDrawX + 72, groundY - 150, goalDrawX + 8, groundY - 120, GetColor(255, 80, 80), TRUE);

	// プレイヤー描画（画像が無ければ Player 側で矩形描画）
	const int playerGraphHandle = (playerImage_ ? playerImage_->GetHandle() : -1);
	player_.Draw(cameraX_, playerGraphHandle);

	// UI
	DrawFormatString(20, 20, GetColor(255, 255, 255), "STATE: %s", player_.GetStateName());
	DrawString(20, 48, "LEFT/RIGHT: MOVE  SPACE: JUMP  C: CLEAR  ESC: EXIT", GetColor(0, 0, 0));
}
