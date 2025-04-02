#include "GameLoop.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "Collider.h"
#include "ConsoleRenderer.h"

enum Scene SceneCurrent = Scene::MENU;
enum Scene SceneNext = Scene::MENU;

void CheckSceneChange();

void GameLoop::Initialize()
{
	MenuScene::Initialize(); // 메뉴초기화 실행
}

void GameLoop::Update()
{
	CheckSceneChange();

	// 업데이트
	switch (SceneCurrent)
	{
	case MENU:
		MenuScene::Update();
		break;
	case PLAY:
		PlayScene::Update();
		Collider::CheckBulletCollider();
		Collider::CheckItemCollider();
		break;
	case END:
		EndScene::Update();
		break;
	}
}

void GameLoop::Render()
{
	ConsoleRenderer::ScreenClear();
	// 씬 출력
	switch (SceneCurrent)
	{
	case MENU:
		MenuScene::Render();
		break;
	case PLAY:
		PlayScene::Render();
		break;
	case END:
		EndScene::Render();
		break;
	}

	ConsoleRenderer::ScreenFlipping();
}

// === Change Scene Functions

/// <summary>
/// 씬 전환 확인 함수
/// </summary>
void CheckSceneChange()
{
	// 씬 전환
	if (SceneCurrent != SceneNext)
	{
		// 전환 전 씬 정리
		switch (SceneCurrent)
		{
		case MENU:
			break;
		case PLAY:
			PlayScene::OnSceneEnd();
		case END:
			break;
		default:
			break;
		}

		SceneCurrent = SceneNext;
		// 전환 시 초기화
		switch (SceneCurrent)
		{
		case MENU:
			MenuScene::Initialize();
			break;
		case PLAY:
			PlayScene::Initialize();
			break;
		case END:
			EndScene::Initialize();
			break;
		default:
			break;
		}
	}
}

void GameLoop::SceneChangeByName(Scene sceneName)
{
	SceneNext = sceneName;
}

void GameLoop::SceneChangeToNext()
{
	SceneNext = (Scene)((SceneCurrent + 1) % Scene::SCENECOUNT);
}