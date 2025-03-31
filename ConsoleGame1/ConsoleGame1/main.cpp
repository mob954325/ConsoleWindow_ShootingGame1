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

	ENABLE_LEAK_CHECK();

	RankingFileUtility::Initialize();
	DebugLog("%d", RankingFileUtility::GetHighScore(1, nullptr));
	RankingFileUtility::ChceckScore(999999, "Test1");
	RankingFileUtility::WriteScore();
	RankingFileUtility::Release();

	//ConsoleRenderer::ScreenInit();
	//Time::InitTime();
	//GameLoop::Initialize();
	//SpriteFileUtility::Initialize();
	//SpriteData::Initialize();
	//SoundController::Initialize();

	////SoundController::SoundPlay("test.wav"); // 소리 테스트용

	//while (!Input::IsKeyPressed(VK_HOME))
	//{
	//	Time::UpdateTime();
	//	Input::Update();
	//	GameLoop::Update();
	//	GameLoop::Render();
	//
	//	__CheckFPS();
	//};
	//
	//SoundController::Release();
	//SpriteData::FreeAllSprites();
	//SpriteFileUtility::FreeAll();
	//ConsoleRenderer::ScreenRelease();

	DUMP_LEAKS();
}