#include "SceneManager.h"
#include <DxLib.h>
#include <algorithm>
#include <memory>

#include "FileManager.h"

#include "../Scene/SceneTitle.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneClear.h"

// プロジェクト設定上で Player.cpp が未登録のため暫定で取り込み
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
	// 通常状態なら現在シーンを更新
	if (transition_.state == TransitionState::None)
	{
		currentScene->Update();
		// シーン終了要求が来たらフェードアウトへ
		if (currentScene->IsEnd() && !currentScene->GetIsTransition())
		{
			transition_.timer = 0.0f;
			transition_.nextSceneID = currentScene->GetNextScene();
			transition_.state = TransitionState::FadeOutCurrent;
		}
	}
	// 遷移中はフェード処理を更新
	if (transition_.state != TransitionState::None)
	{
		UpdateTransition();
	}
}

void SceneManager::UpdateTransition()
{
	// フレームごとに遷移タイマーを進める
	transition_.timer += 1.0f;
	float t = Clamp01(transition_.timer / transition_.duration);

	switch (transition_.state)
	{
	case TransitionState::FadeOutCurrent:
		// 現在シーンをフェードアウト
		currentScene->SetIsTransition(true);
		currentScene->SetTransitionOut(t);
		if (t >= 1.0f)
		{
			transition_.state = TransitionState::SwitchScene;
		}
		break;
	case TransitionState::SwitchScene:
		// 次シーンに切り替えてフェードイン開始
		ChangeScene(transition_.nextSceneID);
		transition_.state = TransitionState::FadeInNext;
		transition_.timer = 0.0f;
		currentScene->SetTransitionIn(transition_.timer);
		currentScene->SetIsTransition(true);
		break;
	case TransitionState::FadeInNext:
		// 次シーンをフェードイン
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
	// 現在シーンの描画
	if (currentScene)
	{
		currentScene->Draw();
	}
}

void SceneManager::ChangeScene(SceneSuper::SceneID nextSceneID)
{
	// 指定されたIDのシーンへ切り替える
	switch (nextSceneID)
	{
	case SceneSuper::SceneID::TITLE:
		currentScene = std::unique_ptr<SceneSuper>(new SceneTitle(fileMng_));
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
