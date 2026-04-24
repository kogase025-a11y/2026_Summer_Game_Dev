#pragma once
#include "../Input/InputManager.h"

class Player
{
public:
	Player(void);
	~Player(void);
	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	void Update(const InputManager& input, float stageWidth);
	void Draw(float cameraX, int playerGraphHandle) const;

	const char* GetStateName() const;
	float GetX() const;
	float GetY() const;
	float GetGroundY() const;
	float GetStepStartX() const;
	float GetStepEndX() const;
	float GetStepTopY() const;

private:
	float positionX_ = 300.0f;
	float positionY_ = 760.0f;
	float velocityY_ = 0.0f;
	bool onGround_ = true;

	const float moveSpeed_ = 7.0f;
	const float gravity_ = 0.65f;
	const float jumpSpeed_ = 14.0f;
	const float groundY_ = 760.0f;
	const float stepStartX_ = 1800.0f;
	const float stepEndX_ = 2500.0f;
	const float stepTopY_ = 640.0f;

	const char* stateName_ = "Idle";
};

