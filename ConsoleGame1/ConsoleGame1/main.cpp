#include "DebugUtility.h"

#include "Windows.h"
#include "Time.h"
#include "ConsoleRenderer.h"
#include "Input.h"
#include "GameLoop.h"
#include "SpriteData.h"

#include <locale.h>

int wmain() 
{
	setlocale(LC_ALL, ""); // 유니코드 설정

	ENABLE_LEAK_CHECK();

	ConsoleRenderer::ScreenInit();
	Time::InitTime();
	GameLoop::Initialize();
	SpriteData::Initialize();
	while (!Input::IsKeyPressed(VK_HOME))
	{
		Time::UpdateTime();
		Input::Update();
		GameLoop::Update();
		GameLoop::Render();
	
		__CheckFPS();
	};
	
	ConsoleRenderer::ScreenRelease();

	DUMP_LEAKS();
}