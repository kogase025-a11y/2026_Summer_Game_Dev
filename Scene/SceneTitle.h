#pragma once
#include "SceneSuper.h"
#include "../Manager/FileManager.h"
#include "../Resource/ImageFile.h"
#include <memory>
#include <DxLib.h>

class FileManager;

class SceneTitle : public SceneSuper
{
public:
	// タイトルシーン生成
	explicit SceneTitle(FileManager& fileMng);
	// 入力更新
	void Update() override;
	// 画面描画
	void Draw() override;

private:
	std::shared_ptr<ImageFile> titleBg_;
};
