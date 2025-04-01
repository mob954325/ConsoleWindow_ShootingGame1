#include "DebugUtility.h"

#include "Windows.h"
#include "Time.h"
#include "ConsoleRenderer.h"
#include "Input.h"
#include "GameLoop.h"
#include "SpriteFileUtility.h"
#include "SpriteData.h"
#include "SoundController.h"
#include "RankingFileUtility.h"

#include <locale.h>

int wmain() 
{
	setlocale(LC_ALL, ""); // 유니코드 설정

	//ENABLE_LEAK_CHECK();

	RankingFileUtility::Initialize();
	ConsoleRenderer::ScreenInit();
	Time::InitTime();
	GameLoop::Initialize();
	SpriteFileUtility::Initialize();
	SpriteData::Initialize();
	SoundController::Initialize();
	
	SoundController::PlayMainMusic("Bolero8Bit.mp3"); // 메인 음악
	
	while (!Input::IsKeyPressed(VK_HOME))
	{
		Time::UpdateTime();
		Input::Update();
		GameLoop::Update();
		GameLoop::Render();
		SoundController::Update();
		//__CheckFPS();
	};
	
	SoundController::Release();
	SpriteData::FreeAllSprites();
	SpriteFileUtility::FreeAll();
	ConsoleRenderer::ScreenRelease();
	RankingFileUtility::Release();

	//DUMP_LEAKS();
}