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
	SceneGame(FileManager&, SceneManager*);
	void Update() override;
	void Draw() override;
private:
	static constexpr int kScreenWidth = 1920;
	static constexpr int kScreenHeight = 1080;
	static constexpr float kStageWidth = 5000.0f;
	static constexpr float kGoalX = 4700.0f;

	InputManager input_;
	Player player_;
	float cameraX_ = 0.0f;
};
