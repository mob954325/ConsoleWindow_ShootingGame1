#include "EnemyManager.h"

#include "BulletManager.h"
#include "GameManager.h"
#include "ItemManager.h"

#include "DebugUtility.h"

namespace EnemyManager
{
	void EnemyShoot();
	Node*& EnemyList = GameManager::GetEnemyList();

	float spawnTimer = 0.0f;

	float enemyShootTimer = 0.0f;
	float maxEnemyShootTime = 1.2f;

	void EnemyManagerInitialize()
	{
		EnemyList = GameManager::GetEnemyList();
	}

	void EnemyUpdate()
	{
		int enemyCount = NodeCount(EnemyList);
		for (int i = 0; i < enemyCount; i++)
		{
			Node* currEnemy = FindNode(EnemyList, i);
			if (!currEnemy) return;

			// 체력이 없거나 출력하는 위치에 벗어나면 적 제거
			if ((currEnemy->data.position.x <= 0)
			|| (currEnemy->data.health <= 0))
			{
				if (currEnemy->data.health <= 0)
				{
					int enemyScore = GameManager::GetScoreBySize(currEnemy->data);
					GameManager::AddPlayScore(enemyScore);

					float randx = rand() % 2;
					ItemManager::CreateItem(currEnemy->data.position, {-10, -10 * randx}, ItemType::WeaponUpgrade);
				}

				DeleteNode(&currEnemy, &EnemyList);
				continue;
			}

			currEnemy->data.position.x += currEnemy->data.speed.x * Time::GetDeltaTime();
			currEnemy->data.position.x += currEnemy->data.speed.y * Time::GetDeltaTime();
		}

		EnemyShoot();
	}

	void EnemyShoot()
	{
		enemyShootTimer += Time::GetDeltaTime();

		if (enemyShootTimer < maxEnemyShootTime) return;

		int enemyCount = NodeCount(EnemyList);
		for (int i = 0; i < enemyCount; i++)
		{
			Node* currEnemy = FindNode(EnemyList, i);			

			BulletManager::CreateBullet({ (currEnemy->data.position.x - 3), currEnemy->data.position.y }, {-25, 0}, Tag::EnemyObject);
			//__PrintDebugLog("Enemy Shoot\n");
		}

		enemyShootTimer = 0;
	}

	void EnemyRender()
	{
		int enemyCount = NodeCount(EnemyList);
		for (int i = 0; i < enemyCount; i++)
		{
			Node* currEnemy = FindNode(EnemyList, i);

			for (int i = 0; i <= currEnemy->data.scale.y; i++)
			{
				for (int j = 0; j <= currEnemy->data.scale.x; j++)
				{
					int currX = (int)currEnemy->data.position.x - currEnemy->data.scale.x / 2 + j;
					int currY = (int)currEnemy->data.position.y - currEnemy->data.scale.y / 2 + i;
					if (currX == (int)currEnemy->data.position.x && currY == (int)currEnemy->data.position.y)
					{
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_SKY_DARK);
					}
					else
					{
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_RED);
					}
				}
			}
		}
	}

	// 적 스폰 ==================================================================================
	
	void SpawnEnemyAtRandomPosition()
	{
		float spawnPositionX = rand() % ENEMY_SPAWN_AREA_WIDTH;
		float spawnPositionY = rand() % ENEMY_SPAWN_AREA_HEIGHT;

		// TODO : 랜덤시드 변경 코드 넣기
		float randomSizeX = rand() % MAX_ENEMY_SIZE;
		float randomSizeY = rand() % MAX_ENEMY_SIZE;
		float randomSpeed = rand() % MAX_ENEMY_SPEED;

		if (randomSpeed < MIN_ENEMY_SPEED) randomSpeed = MIN_ENEMY_SPEED;

		ScreenElement enemyData = SetScreenElementValue( { randomSizeX, randomSizeY }, randomSizeX + 1, { (spawnPositionX + MAXWIDTH), spawnPositionY }, {-randomSpeed, 0}, Tag::EnemyObject);
		AddNode(&EnemyList, enemyData);
	}

	void SpawnEnemyAtPosition(Vector2 spawnPosition)
	{
		ScreenElement enemyData = SetScreenElementValue({3, 3}, spawnPosition, { -1, 0 }, Tag::EnemyObject);
		AddNode(&EnemyList, enemyData);
	}


	void SetEnemySpanwer(float spawnDelay)
	{
		spawnTimer += Time::GetDeltaTime();
		if (spawnTimer < spawnDelay) return;

		SpawnEnemyAtRandomPosition();
		DebugLog("Enemy Spawned!!!\n");

		spawnTimer = 0.0f;
	}
}