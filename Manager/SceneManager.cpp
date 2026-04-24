#include "SceneManager.h"
#include <DxLib.h>
#include <algorithm>
#include <memory>

#include "FileManager.h"

#include "../Scene/SceneTitle.h"
#include "../Scene/SceneStageSelect.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneClear.h"
#include "../Player/Player.cpp"

namespace
{
	float Clamp01(float v)
	{
		if (v < 0.0f) return 0.0f;
		if (v > 1.0f) return 1.0f;
		return v;
	}
}

SceneManager::SceneManager(FileManager& fileMng) : fileMng_(fileMng)
{
	currentScene = std::unique_ptr<SceneSuper>(new SceneTitle(fileMng_));
	isExit = false;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	if (transition_.state == TransitionState::None)
	{
		currentScene->Update();
		if (currentScene->IsEnd() && !currentScene->GetIsTransition())
		{
			transition_.timer = 0.0f;
			transition_.nextSceneID = currentScene->GetNextScene();
			transition_.state = TransitionState::FadeOutCurrent;
		}
	}
	if (transition_.state != TransitionState::None)
	{
		UpdateTransition();
	}
}

void SceneManager::UpdateTransition()
{
	transition_.timer += 1.0f; // フレームごとにタイマーを進める
	float t = Clamp01(transition_.timer / transition_.duration);

	switch (transition_.state)
	{
	case TransitionState::FadeOutCurrent:
		// フェードアウトのロジック
		currentScene->SetIsTransition(true);
		currentScene->SetTransitionOut(t);
		if (t >= 1.0f)
		{
			transition_.state = TransitionState::SwitchScene;
		}
		break;
	case TransitionState::SwitchScene:
		ChangeScene(transition_.nextSceneID);
		transition_.state = TransitionState::FadeInNext;
		transition_.timer = 0.0f; // フェードインのタイマーをリセット
		currentScene->SetTransitionIn(transition_.timer); // 最初の一フレーム目の描画
		currentScene->SetIsTransition(true);
		break;
	case TransitionState::FadeInNext:
		// フェードインのロジック
		currentScene->SetTransitionIn(t);
		if (t >= 1.0f)
		{
			transition_.state = TransitionState::None;
			currentScene->SetIsTransition(false);
		}
	}
}

void SceneManager::Draw()
{
	if (currentScene)
	{
		currentScene->Draw();
	}
}

void SceneManager::ChangeScene(SceneSuper::SceneID nextSceneID)
{
	switch (nextSceneID)
	{
	case SceneSuper::SceneID::TITLE:
		currentScene = std::unique_ptr<SceneSuper>(new SceneTitle(fileMng_));
		break;
	case SceneSuper::SceneID::STAGE_SELECT:
		currentScene = std::unique_ptr<SceneSuper>(new SceneStageSelect(fileMng_));
		break;
	case SceneSuper::SceneID::GAME:
		currentScene = std::unique_ptr<SceneSuper>(new SceneGame(fileMng_, this));
		break;
	case SceneSuper::SceneID::CLEAR:
		currentScene = std::unique_ptr<SceneSuper>(new SceneClear(fileMng_));
		break;
	case SceneSuper::SceneID::EXIT:
		isExit = true;
		break;
	default:
#ifdef _DEBUG
		OutputDebugStringA("Unknown SceneID\n");
#endif
		break;
	}
}

bool SceneManager::GetExit()
{
	return isExit;
}

void SceneManager::SetClearResult(const ClearResult& result)
{
	clearResult_ = result;
}
