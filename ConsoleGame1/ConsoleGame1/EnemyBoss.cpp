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
		SetElementTimer(10, BossInfo);
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
				if (currX == (int)BossInfo->position.x && currY == (int)BossInfo->position.y)
				{
					ConsoleRenderer::ScreenDrawChar(currX, currY, L'(｀・ω・´)', FG_BLUE_DARK);
				}
				ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_RED);
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
		BulletManager::CreateBullet({ BossInfo->position.x - 5, BossInfo->position.y }, {5, 5}, { -BULLET_SPEED, 0 }, Tag::EnemyObject);
	}
}