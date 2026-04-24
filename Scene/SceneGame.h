#pragma once
#include "SceneSuper.h"
#include "../Input/InputManager.h"
#include "../Player/Player.h"
#include <DxLib.h>

class FileManager;
class SceneManager;

class SceneGame : public SceneSuper
{
public:
	// ゲームシーン生成
	SceneGame(FileManager&, SceneManager*);
	// 毎フレーム更新
	void Update() override;
	// 毎フレーム描画
	void Draw() override;
private:
	// 画面サイズ
	static constexpr int kScreenWidth = 1920;
	static constexpr int kScreenHeight = 1080;
	// ステージ幅とゴール位置
	static constexpr float kStageWidth = 5000.0f;
	static constexpr float kGoalX = 4700.0f;

	// 入力・プレイヤー・カメラ
	InputManager input_;
	Player player_;
	float cameraX_ = 0.0f;
};
