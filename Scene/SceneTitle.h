#pragma once
#include "SceneSuper.h"
#include "../Manager/FileManager.h"
#include "../Resource/ImageFile.h"
#include <memory>
#include <DxLib.h>
#include <memory>

class FileManager;
class ImageFile;

class SceneTitle : public SceneSuper
{
public:
	// タイトルシーン生成
	explicit SceneTitle(FileManager& fileMng);
<<<<<<< HEAD
	void Update() override;
	// 画面描画
	void Draw() override;
private:
	std::shared_ptr<ImageFile> imageFile_;
=======
	// 入力更新
	void Update() override;
	// 画面描画
	void Draw() override;

private:
	std::shared_ptr<ImageFile> titleBg_;
>>>>>>> origin/koga
};
