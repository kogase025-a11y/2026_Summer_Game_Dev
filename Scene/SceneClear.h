#pragma once
#include "SceneSuper.h"
#include <DxLib.h>

class FileManager;

class SceneClear : public SceneSuper
{
public:
	explicit SceneClear(FileManager&);
	void Update() override;
	void Draw() override;
};
