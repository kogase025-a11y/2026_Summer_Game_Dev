#include "Player.h"

#include <DxLib.h>
#include <algorithm>

Player::Player(FileManager& fileMng) : fileMng_(fileMng)
{
	
	 particleTex = fileMng_.LoadImageFM("Image/ToiletPaper.PNG");

}

Player::~Player(void)
{

}

bool Player::SystemInit(void)
{
	// システム初期化時にプレイヤー状態を初期化
	positionX_ = 200.0f;
	positionY_ = groundY_;
	velocityY_ = 0.0f;
	onGround_ = true;
	stateName_ = "Idle";
	return true;
}

void Player::GameInit(void)
{
	// ゲーム開始時のリセット
	positionX_ = 300.0f;
	positionY_ = groundY_;
	velocityY_ = 0.0f;
	onGround_ = true;
	stateName_ = "Idle";
}

void Player::Update(void)
{
	// 旧インターフェース用（入力がない時は更新しない）
}

void Player::Draw(void)
{
	// 旧インターフェース用（カメラ0・画像なしで描画）
	Draw(0.0f, -1);
}

bool Player::Release(void)
{
	return true;
}

void Player::Update(const InputManager& input, float stageWidth)
{
	// プレイヤー当たり判定の半幅
	const float playerHalfWidth = 30.0f;

	// 現在のX座標が通常床か段差上かを返す
	const auto getGroundYAtX = [this](float x)
	{
		if ((x >= stepStartX_) && (x <= stepEndX_))
		{
			return stepTopY_;
		}
		return groundY_;
	};

	// 左右入力（右=+1, 左=-1）
	const float moveInput =
		(input.IsNew(KEY_INPUT_RIGHT) ? 1.0f : 0.0f) -
		(input.IsNew(KEY_INPUT_LEFT) ? 1.0f : 0.0f);

	// 水平方向の移動
	const float prevX = positionX_;
	positionX_ += moveInput * moveSpeed_;

	// 画面（ステージ）外に出ないようにクランプ
	const float clampedStageWidth = (std::max)(0.0f, stageWidth);
	const float minX = playerHalfWidth;
	const float maxX = (std::max)(minX, clampedStageWidth - playerHalfWidth);
	positionX_ = (std::max)(minX, (std::min)(positionX_, maxX));

	// 段差より下にいる時だけ側面衝突を有効にする
	const bool isBelowStepTop = (positionY_ > stepTopY_ + 0.5f);
	if (isBelowStepTop)
	{
		if ((prevX + playerHalfWidth <= stepStartX_) && (positionX_ + playerHalfWidth > stepStartX_))
		{
			positionX_ = stepStartX_ - playerHalfWidth;
		}
		else if ((prevX - playerHalfWidth >= stepEndX_) && (positionX_ - playerHalfWidth < stepEndX_))
		{
			positionX_ = stepEndX_ + playerHalfWidth;
		}
	}

	// ジャンプ開始
	const bool jumpPressed = input.IsTrgDown(KEY_INPUT_SPACE);
	if (jumpPressed && onGround_)
	{
		velocityY_ = -jumpSpeed_;
		onGround_ = false;
	}

	// 足元の床高さを取得
	const float supportGroundY = getGroundYAtX(positionX_);

	// 地形の切り替わりで足場が消えたら落下開始
	if (onGround_ && (positionY_ < supportGroundY - 0.5f))
	{
		onGround_ = false;
	}

	// 空中時は重力適用
	if (!onGround_)
	{
		velocityY_ += gravity_;
	}

	// 垂直方向の移動と着地判定
	positionY_ += velocityY_;
	if (positionY_ >= supportGroundY)
	{
		positionY_ = supportGroundY;
		velocityY_ = 0.0f;
		onGround_ = true;
	}

	// 状態名更新（アニメーション等で利用）
	if (input.IsTrgDown(KEY_INPUT_X))
	{
		stateName_ = "Damage";
	}
	else if (input.IsTrgDown(KEY_INPUT_Z))
	{
		stateName_ = "Attack";
	}
	else if (!onGround_)
	{
		stateName_ = (velocityY_ < 0.0f) ? "Jump" : "Fall";
	}
	else if (moveInput != 0.0f)
	{
		stateName_ = "Run";
	}
	else
	{
		stateName_ = "Idle";
	}
}

void Player::Draw(float cameraX, int playerGraphHandle) const
{
	const int drawX = static_cast<int>(positionX_ - cameraX);
	const int drawY = static_cast<int>(positionY_);

	if (particleTex)
	{
		DrawRotaGraph(drawX, drawY - 24, 1.0, 0.0, particleTex->GetHandle(), TRUE);
		return;
	}
	
	if (playerGraphHandle >= 0)
	{
		DrawRotaGraph(drawX, drawY - 24, 1.0, 0.0, playerGraphHandle, TRUE);
		return;
	}

	const int left = drawX - 30;
	const int right = drawX + 30;
	const int top = drawY - 48;
	const int bottom = drawY;
	DrawBox(left, top, right, bottom, GetColor(120, 220, 255), TRUE);

	// 当たり判定デバッグ描画（当たり判定の幅で赤い枠線を描画）
#ifdef _DEBUG
	const float playerHalfWidth = 30.0f;
	const int debugLeft = static_cast<int>(positionX_ - playerHalfWidth - cameraX);
	const int debugRight = static_cast<int>(positionX_ + playerHalfWidth - cameraX);
	const int debugTop = static_cast<int>(positionY_ - 48.0f); // 描画の下端(bottom)は positionY_ と同じ
	const int debugBottom = static_cast<int>(positionY_);

	DrawBox(debugLeft, debugTop, debugRight, debugBottom, GetColor(255, 0, 0), FALSE); // FALSEで枠線のみ
#endif
}

const char* Player::GetStateName() const
{
	return stateName_;
}

float Player::GetX() const
{
	return positionX_;
}

float Player::GetY() const
{
	return positionY_;
}

float Player::GetGroundY() const
{
	return groundY_;
}

float Player::GetStepStartX() const
{
	return stepStartX_;
}

float Player::GetStepEndX() const
{
	return stepEndX_;
}

float Player::GetStepTopY() const
{
	return stepTopY_;
}