#include "Application.h"

#include <DxLib.h>

#include "../Manager/FileManager.h"
#include "../Manager/SceneManager.h"

Application::Application()
{
}

Application::~Application()
{
}

bool Application::SystemInit(void)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG, 32);

	if (DxLib_Init() == -1)
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	fileMng_.reset(new FileManager());
	sceneMana.reset(new SceneManager(*fileMng_));

	return true;
}

void Application::Run(void)
{
	while (ProcessMessage() == 0)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			break;
		}
		if (sceneMana && sceneMana->GetExit())
		{
			break;
		}

		Update();
		Draw();
		ScreenFlip();
	}
}

void Application::Update(void)
{
	if (sceneMana)
	{
		sceneMana->Update();
	}
}

void Application::Draw(void)
{
	ClearDrawScreen();
	if (sceneMana)
	{
		sceneMana->Draw();
	}
}

bool Application::Release(void)
{
	sceneMana.reset();
	fileMng_.reset();
	DxLib_End();
	return true;
}