#pragma once
#include "SceneSuper.h"
#include <DxLib.h>

class FileManager;

class SceneTitle : public SceneSuper
{
public:
	// タイトルシーン生成
	explicit SceneTitle(FileManager&);
	// 入力更新
	void Update() override;
	// 画面描画
	void Draw() override;
};
