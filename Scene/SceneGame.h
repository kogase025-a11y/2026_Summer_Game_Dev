#pragma once
#include "SceneSuper.h"
#include "../Input/InputManager.h"
#include "../Player/Player.h"
#include <DxLib.h>
#include <memory>

class FileManager;
class SceneManager;
class ImageFile;

class SceneGame : public SceneSuper
{
public:
	// ゲームシーン生成
	SceneGame(FileManager& fileMng, SceneManager* sceneMng);
	// ゲームシーン破棄
	~SceneGame() override;
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
	// プレイヤー画像パス（画像未配置でも動作する）
	static constexpr const char* kPlayerImagePath = "Data/Image/player.png";

	// 入力・プレイヤー・カメラ

	Player player_;
	float cameraX_ = 0.0f;
	FileManager& fileMng_;
	SceneManager* sceneMng_ = nullptr;
	std::shared_ptr<ImageFile> playerImage_;

	// ポーズ中かどうかのフラグ
	bool isPause_ = false;
};
