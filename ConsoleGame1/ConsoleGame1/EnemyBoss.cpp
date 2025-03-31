#include "EnemyBoss.h"

#include "DebugUtility.h"

namespace Boss
{
	void BossShoot();

	ScreenElement* BossInfo = {};

	float bossShootTimer = 0;
	float maxBossShootTime = 1;

	void Initialize()
	{
		BossInfo = GameManager::GetBossInfo();
		SetElementTimer(3, BossInfo);
	}

	void BossUpdate()
	{
		if (BossInfo->health <= 0)
		{
			int enemyScore = GameManager::GetScoreBySize(*BossInfo);
			GameManager::AddPlayScore(enemyScore); // 아마 게임 끝날때까지 계속 점수 증가할꺼임
		}

		// 행동
		BossInfo->remainTime -= Time::GetDeltaTime();
		if (BossInfo->position.x > MAXWIDTH - 10)
		{
			BossInfo->position.x += BossInfo->speed.x * Time::GetDeltaTime();
		}
		else
		{
			BossInfo->speed.x = 0;
			if (BossInfo->remainTime <= 0)
			{
				BossInfo->remainTime = BossInfo->maxTime;
				BossShoot();
			}
			// 보스 체력 UI 활성화
			// 적 공격 활성화
		}
	}

	void BossRender()
	{
		for (int i = 1; i <= BossInfo->scale.y; i++)
		{
			for (int j = 1; j <= BossInfo->scale.x; j++)
			{
				int currX = (int)BossInfo->position.x - BossInfo->scale.x / 2 + j;
				int currY = (int)BossInfo->position.y - BossInfo->scale.y / 2 + i;

				ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_RED);
				if (currX == (int)BossInfo->position.x && currY == (int)BossInfo->position.y)
				{
					ConsoleRenderer::ScreenDrawChar(currX, currY, L'(｀・ω・´)', FG_BLUE_DARK);
				}
			}
		}

		// 사망
		if (BossInfo->health <= 0)
		{
			for (int i = 0; i < 10; i++)
			{
				int posX = rand() % (int)BossInfo->scale.x;
				int posY = rand() % (int)BossInfo->scale.y;
				ParticleManager::ShowParticleAtPosition({ BossInfo->position.x - posX, BossInfo->position.y + posY / 2 }, ParticleType::Dead, 0.1);
			}
		}
	}

	void BossShoot()
	{
		// TODO 보스 패턴 늘리기 
		float attackProbability = 100 / BOSS_ATTACK_COUNT;
		float randomAttack = rand() % (int)attackProbability; // 아마 마지막 공격이 더 많이 나갈것임		

		ScreenElement* player = GameManager::GetPlayerInfo();

		for (int i = 0; i < 3; i++)
		{
			// 위
			float speedX_Top = player->position.x - (BossInfo->position.x - 5);
			float speedY_Top = player->position.y - (BossInfo->position.y - 5);
			BulletManager::CreateBullet({ BossInfo->position.x - 5, BossInfo->position.y - 5 + i}, { speedX_Top, speedY_Top }, Tag::EnemyObject);
			// 아래
			float speedX_Bottom = player->position.x - (BossInfo->position.x - 5);
			float speedY_Bottom = player->position.y - (BossInfo->position.y + 5);
			BulletManager::CreateBullet({ (BossInfo->position.x - 5), BossInfo->position.y + 5 + i}, { speedX_Bottom, speedY_Bottom }, Tag::EnemyObject);
		}

		if (randomAttack <= attackProbability) // 1
		{
			DebugLog("boss1\n");
		}
		else if (randomAttack <= attackProbability * 2)
		{
			DebugLog("boss2\n");
			for (int i = 0; i < 5; i++)
			{
				// 위
				float speedX_Top = player->position.x - (BossInfo->position.x - 5);
				float speedY_Top = player->position.y - (BossInfo->position.y - 5);
				BulletManager::CreateBullet({ BossInfo->position.x - 5, BossInfo->position.y - 5 + i }, { speedX_Top, speedY_Top }, Tag::EnemyObject);
				// 아래
				float speedX_Bottom = player->position.x - (BossInfo->position.x - 5);
				float speedY_Bottom = player->position.y - (BossInfo->position.y + 5);
				BulletManager::CreateBullet({ (BossInfo->position.x - 5), BossInfo->position.y + 5 + i }, { speedX_Bottom, speedY_Bottom }, Tag::EnemyObject);
			}
		}
		else if (randomAttack <= attackProbability * 3)
		{
			DebugLog("boss3\n");
			BulletManager::CreateBullet({ BossInfo->position.x - 5, BossInfo->position.y }, {5, 5}, { -BULLET_SPEED, 0 }, Tag::EnemyObject);
		}
	}
}