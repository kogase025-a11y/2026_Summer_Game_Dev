#pragma once
#include "SceneSuper.h"
#include <DxLib.h>

class FileManager;

class SceneTitle : public SceneSuper
{
public:
	explicit SceneTitle(FileManager&);
	void Update() override;
	void Draw() override;
};
