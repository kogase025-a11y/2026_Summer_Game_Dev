#pragma once
#include <memory>

class FileManager;
#include "../Scene/SceneSuper.h"

struct ClearResult
{
	// クリアタイム
	float time;
	// ステージ番号
	int stageIndex;
};
class SceneManager
{
public:
	// シーン遷移の進行状態
	enum class TransitionState
	{
		None,
		FadeInNext,
		FadeOutCurrent,
		SwitchScene,
	};

	struct Transition
	{
		// 現在の遷移状態
		TransitionState state = TransitionState::None;
		// 経過フレーム
		float timer = 0.0f;
		float duration = 45.0f; // フェードの総時間（フレーム数）
		// 遷移先シーン
		SceneSuper::SceneID nextSceneID = SceneSuper::SceneID::NONE;
	};
	// シーン管理生成
	SceneManager(FileManager& fileMng);
	~SceneManager();
	// 更新・描画
	void Update();
	void Draw();

	// 終了要求の有無
	bool GetExit();
	// クリア結果を保存
	void SetClearResult(const ClearResult& result);
private:
	// シーン生成切り替え
	void ChangeScene(SceneSuper::SceneID nextSceneID);
	// フェード遷移更新
	void UpdateTransition();
	std::unique_ptr<SceneSuper> currentScene; // 大元のSceneはかならず一つ
	FileManager& fileMng_;

	// アプリ終了要求
	bool isExit;

	// 遷移管理データ
	Transition transition_;

	// クリア結果キャッシュ
	ClearResult clearResult_;
};


