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
	MenuSceneUI::RenderUI();
}

void changeScene()
{
	if (Input::IsKeyPressed(VK_SPACE))
	{
		GameLoop::SceneChangeToNext();
	}
}
 