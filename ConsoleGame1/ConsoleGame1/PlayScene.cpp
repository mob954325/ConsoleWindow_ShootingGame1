#include "PlayScene.h"

void TestVictory();

void PlayScene::Initialize()
{
	GameManager::GameManagerInitialize(); // TODO : 이름 줄이기
	EnemyManager::EnemyManagerInitialize();
	BulletManager::BulletManagerInitialize();
	ItemManager::ItemManagerInitialize();
	ParticleManager::Initialize();
	PlayScreenUI::PlayScreenUIInitialize();
	Time::InitTime();

	Player::PlayerInit();

	GameManager::SetGameState(GameState::Playing);	
	//EnemyManager::SpawnEnemyAtPosition({40,20}, 1000); // 임시 적 스폰
}

void PlayScene::Update()
{
	// 승패 확인
	if (GameManager::CheckIsPlayerDead() == 0) 
	{
		GameManager::SetGameResultState(GameResultState::Lose);
		GameManager::SetGameState(GameState::PlayEnd);
	}
	if (GameManager::GetGameState() == GameState::PlayEnd) return;

	// 업데이트 루프
	EnemyManager::SetEnemySpanwer(2);
	BulletManager::BulletUpdate();
	ItemManager::ItemUpdate();

	EnemyManager::EnemyUpdate();

	Player::PlayerUpdate();
	TestVictory();
}

void PlayScene::Render()
{
	// 승패 확인
	if (GameManager::GetGameState() == GameState::PlayEnd)
	{
		GameManager::ShowGameResult();
		//return;
	}

	// 업데이트 루프
	BulletManager::BulletRender();
	EnemyManager::EnemyRender();
	ItemManager::ItemRender();
	ParticleManager::ParticleRender();
	Player::RenderPlayer();

	PlayScreenUI::RenderUI();
}

void TestVictory()
{
	if (Input::IsKeyPressed(VK_SPACE))
	{
		GameManager::SetGameState(GameState::PlayEnd);
	}
}