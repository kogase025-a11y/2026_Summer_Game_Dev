#pragma once
#include "SceneSuper.h"
#include <DxLib.h>
#include <memory>

class FileManager;
class ImageFile;

class SceneTitle : public SceneSuper
{
public:
	// タイトルシーン生成
	explicit SceneTitle(FileManager& fileMng);
	void Update() override;
	// 画面描画
	void Draw() override;
private:
	std::shared_ptr<ImageFile> imageFile_;
};
