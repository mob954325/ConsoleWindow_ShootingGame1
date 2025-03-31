#include "PlayScene.h"

void TestVictory();

void PlayScene::Initialize()
{
	GameManager::GameManagerInitialize(); // TODO : 이름 줄이기
	EnemyManager::EnemyManagerInitialize();
	BulletManager::BulletManagerInitialize();
	ItemManager::ItemManagerInitialize();
	ParticleManager::ParticleManagerInitialize();
	PlayScreenUI::PlayScreenUIInitialize();
	Time::InitTime();

	Player::PlayerInit();
	Boss::Initialize();

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
	else if (GameManager::GetBossInfo()->health <= 0)
	{
		GameManager::SetGameResultState(GameResultState::Win);
		GameManager::SetGameState(GameState::PlayEnd);
	}

	if (GameManager::GetGameState() == GameState::PlayEnd) return;


	// 업데이트 루프
		Boss::BossUpdate();
	//if (Time::GetTotalTime() > 60)
	//{
	//}
	//else
	//{
	//	EnemyManager::SetEnemySpanwer(2);
	//}

	BulletManager::BulletUpdate();
	ItemManager::ItemUpdate();

	EnemyManager::EnemyUpdate();

	Player::PlayerUpdate();
	//TestVictory();
}

void PlayScene::Render()
{
	// 승패 확인
	if (GameManager::GetGameState() == GameState::PlayEnd)
	{
		GameManager::ShowGameResult();
		//return;
	}

	Boss::BossRender();
	// 업데이트 루프
	//if (Time::GetTotalTime() > 60)
	//{
	//}

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