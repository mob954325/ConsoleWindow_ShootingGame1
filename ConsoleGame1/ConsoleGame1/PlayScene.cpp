#include "PlayScene.h"

void TestVictory();

void PlayScene::Initialize()
{
	GameManager::Initialize(); // TODO : 이름 줄이기
	EnemyManager::Initialize();
	BulletManager::Initialize();
	ItemManager::Initialize();
	ParticleManager::Initialize();
	PlayScreenUI::Initialize();
	Time::InitTime();

	Player::PlayerInit();
	Boss::Initialize();

	GameManager::SetGameState(GameState::Playing);	
	//EnemyManager::SpawnEnemyAtPosition({40,20}, 1000); // 임시 적 스폰
	//ItemManager::CreateItem({ 40,20 }, { 0,0 }, ItemType::HpRestore); // 임시 아이템 생성
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
		float enemyScore = GameManager::GetScoreBySize(*GameManager::GetBossInfo()); // AAAA
		enemyScore *= 0.25f;
		GameManager::AddPlayScore((int)enemyScore); // 아마 게임 끝날때까지 계속 점수 증가할꺼임
		GameManager::SetGameResultState(GameResultState::Win);
		GameManager::SetGameState(GameState::PlayEnd);
	}

	if (GameManager::GetGameState() == GameState::PlayEnd) return;


	// 업데이트 루프
	if (Time::GetTotalTime() > BOSS_APPEAR_TIME)
	{
		Boss::BossUpdate();
		EnemyManager::SetEnemySpanwer(3);
	}
	else
	{
		EnemyManager::SetEnemySpanwer(1);
	}

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

	// 업데이트 루프
	if (Time::GetTotalTime() > BOSS_APPEAR_TIME)
	{
		Boss::BossRender();
	}

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