#include "EndScene.h"
#include "ConsoleRenderer.h"
#include "Input.h"
#include "GameLoop.h"

void EndScene::Initialize()
{
	ConsoleRenderer::ScreenInit();
}

void EndScene::Update()
{

}

void EndScene::Render()
{
	EndSceneUI::RenderUI();
}