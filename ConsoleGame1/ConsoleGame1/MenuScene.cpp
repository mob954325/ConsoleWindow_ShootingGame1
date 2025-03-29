#include "MenuScene.h"
#include "ConsoleRenderer.h"
#include "Input.h"
#include "GameLoop.h"

void changeScene();

void MenuScene::Initialize()
{
	ConsoleRenderer::ScreenInit();
}

void MenuScene::Update()
{
	changeScene();
}

void MenuScene::Render()
{
	ConsoleRenderer::ScreenDrawString(0, 0, "MainMenu", FG_PINK_DARK);
	MenuSceneUI::RenderUI();
}

void changeScene()
{
	if (Input::IsKeyPressed(VK_SPACE))
	{
		GameLoop::SceneChangeToNext();
	}
}
 