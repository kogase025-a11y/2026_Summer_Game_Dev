#include "Player.h"

#include <DxLib.h>
#include <algorithm>

Player::Player(void)
{
}

Player::~Player(void)
{
}

bool Player::SystemInit(void)
{
	return true;
}

void Player::GameInit(void)
{
}

void Player::Update(void)
{
}

void Player::Draw(void)
{
}

bool Player::Release(void)
{
	return true;
}

void Player::Update(const InputManager& input, float stageWidth)
{
	const float playerHalfWidth = 24.0f;
	const auto getGroundYAtX = [this](float x)
	{
		if ((x >= stepStartX_) && (x <= stepEndX_))
		{
			return stepTopY_;
		}
		return groundY_;
	};

	const float moveInput =
		(input.IsPress(KEY_INPUT_RIGHT) ? 1.0f : 0.0f) -
		(input.IsPress(KEY_INPUT_LEFT) ? 1.0f : 0.0f);

	const float prevX = positionX_;
	positionX_ += moveInput * moveSpeed_;
	positionX_ = (std::max)(0.0f, (std::min)(positionX_, stageWidth));

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

	const bool jumpPressed = input.IsTrigger(KEY_INPUT_SPACE);
	if (jumpPressed && onGround_)
	{
		velocityY_ = -jumpSpeed_;
		onGround_ = false;
	}

	const float supportGroundY = getGroundYAtX(positionX_);
	if (onGround_ && (positionY_ < supportGroundY - 0.5f))
	{
		onGround_ = false;
	}

	if (!onGround_)
	{
		velocityY_ += gravity_;
	}

	positionY_ += velocityY_;
	if (positionY_ >= supportGroundY)
	{
		positionY_ = supportGroundY;
		velocityY_ = 0.0f;
		onGround_ = true;
	}

	if (input.IsTrigger(KEY_INPUT_X))
	{
		stateName_ = "Damage";
	}
	else if (input.IsTrigger(KEY_INPUT_Z))
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

	if (playerGraphHandle >= 0)
	{
		DrawRotaGraph(drawX, drawY - 24, 1.0, 0.0, playerGraphHandle, TRUE);
		return;
	}

	const int left = drawX - 24;
	const int right = drawX + 24;
	const int top = drawY - 48;
	const int bottom = drawY;
	DrawBox(left, top, right, bottom, GetColor(120, 220, 255), TRUE);
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