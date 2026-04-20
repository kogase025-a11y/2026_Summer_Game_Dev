#pragma once
#include "SceneSuper.h"
#include "../Effect/EffectSuper.h"
#include "../Effect/PachinkoBlackoutEffect.h"

#include <DxLib.h>
#include <memory>

class FileManager;

class SceneStageSelect : public SceneSuper
{
public:
	explicit SceneStageSelect(FileManager&)
		: stageEffect_(new PachinkoBlackoutEffect())
	{
	}

	void Update() override
	{
		if (stageEffect_)
		{
			stageEffect_->Update();
			if (stageEffect_->IsFinished())
			{
				EndScene(SceneID::CLEAR);
			}
		}
	}

	void Draw() override
	{
		const int width = 1920;
		const int height = 1080;
		const int centerX = width / 2;
		const int centerY = height / 2;
		DrawBox(0, 0, width, height, GetColor(8, 8, 20), TRUE);
		DrawBox(40, 40, width - 40, height - 40, GetColor(255, 210, 60), FALSE);
		DrawBox(58, 58, width - 58, height - 58, GetColor(200, 22, 50), FALSE);
		DrawString(centerX - 95, centerY - 270, "STAGE SELECT", GetColor(255, 255, 255));

		if (stageEffect_)
		{
			stageEffect_->Draw();
		}
	}

private:
	std::unique_ptr<EffectSuper> stageEffect_;
};
