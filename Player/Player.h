#pragma once
#include "../Input/InputManager.h"

class Player
{
public:
	// 生成・破棄
	Player(void);
	~Player(void);
	// 初期化・解放
	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	// 入力付き更新・カメラ付き描画
	void Update(const InputManager& input, float stageWidth);
	void Draw(float cameraX, int playerGraphHandle) const;

	// 状態/位置取得
	const char* GetStateName() const;
	float GetX() const;
	float GetY() const;
	float GetGroundY() const;
	float GetStepStartX() const;
	float GetStepEndX() const;
	float GetStepTopY() const;

private:

	

	// 現在の状態
	float positionX_ = 300.0f;
	float positionY_ = 760.0f;
	float velocityY_ = 0.0f;
	bool onGround_ = true;

	// 移動パラメータ
	const float moveSpeed_ = 7.0f;
	const float gravity_ = 0.65f;
	const float jumpSpeed_ = 14.0f;
	// 地形パラメータ
	const float groundY_ = 760.0f;
	const float stepStartX_ = 1800.0f;
	const float stepEndX_ = 2500.0f;
	const float stepTopY_ = 640.0f;

	// アニメーション用状態名
	const char* stateName_ = "Idle";
};

