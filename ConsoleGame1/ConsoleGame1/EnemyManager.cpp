#include "EnemyManager.h"

#include "BulletManager.h"
#include "GameManager.h"
#include "ItemManager.h"
#include "ParticleManager.h"

#include "DebugUtility.h"

namespace EnemyManager
{
	void EnemyShoot();
	void CreateBulletByType(ScreenElement curr);

	Node*& EnemyList = GameManager::GetEnemyList();

	float spawnTimer = 0.0f;

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

			currEnemy->data.remainTime -= Time::GetDeltaTime(); // 타이머 감소

			// 체력이 없거나 출력하는 위치에 벗어나면 적 제거
			if ((currEnemy->data.position.x <= 0)
			|| (currEnemy->data.health <= 0))
			{
				if (currEnemy->data.health <= 0)
				{
					int enemyScore = GameManager::GetScoreBySize(currEnemy->data);
					GameManager::AddPlayScore(enemyScore);

					ParticleManager::ShowParticleAtPosition(currEnemy->data.position, ParticleType::Dead, 0.08);

					int currDropRate = rand() % 101;
					if (currDropRate <= ITEM_DROPRATE)
					{
						float randx = rand() % 2;
						int randItemIndex = rand() % ItemType::ItemTypeCount;

						ItemManager::CreateItem(currEnemy->data.position, { -10, -10 * randx }, (ItemType)randItemIndex);
					}
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
		int enemyCount = NodeCount(EnemyList);
		for (int i = 0; i < enemyCount; i++)
		{
			Node* currEnemy = FindNode(EnemyList, i);			

			//if (currEnemy->data.additionalElement.enemyType == EnemyType::Smol) return; // ?
			if (currEnemy->data.remainTime <= 0)
			{
				currEnemy->data.remainTime = currEnemy->data.maxTime;
				CreateBulletByType(currEnemy->data);
			}
			//__PrintDebugLog("Enemy Shoot\n");
		}
	}

	void CreateBulletByType(ScreenElement curr)
	{
		EnemyType type = curr.additionalElement.enemyType;
		if (type == EnemyType::Smol)
		{
			ScreenElement* player = GameManager::GetPlayerInfo();			
			float speedX = player->position.x - curr.position.x;
			float speedY = player->position.y - curr.position.y;

			BulletManager::CreateBullet({ (curr.position.x - 3), curr.position.y }, { speedX, speedY }, Tag::EnemyObject);
		}
		else if (type == EnemyType::Medium) // 2 x 2
		{
			BulletManager::CreateBullet({ (curr.position.x - 3), curr.position.y }, { -BULLET_SPEED, 0 }, Tag::EnemyObject);
		}
		else if (type == EnemyType::Large) // 3 x 3
		{
			BulletManager::CreateBullet({ (curr.position.x - 3), curr.position.y + 1}, { -BULLET_SPEED, 0 }, Tag::EnemyObject);
			BulletManager::CreateBullet({ (curr.position.x - 3), curr.position.y - 1}, { -BULLET_SPEED, 0 }, Tag::EnemyObject);
		}
	}

	void EnemyRender()
	{
		int enemyCount = NodeCount(EnemyList);
		for (int i = 0; i < enemyCount; i++)
		{
			Node* currEnemy = FindNode(EnemyList, i);

			for (int i = 1; i <= currEnemy->data.scale.y; i++)
			{
				for (int j = 1; j <= currEnemy->data.scale.x; j++)
				{
					int currX = (int)currEnemy->data.position.x - currEnemy->data.scale.x / 2 + j;
					int currY = (int)currEnemy->data.position.y - currEnemy->data.scale.y / 2 + i;
					ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_RED);
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
		float randomSpeed = rand() % MAX_ENEMY_SPEED;
		int randomType = rand() % EnemyType::EnemyTypeCount;

		if (randomSpeed < MIN_ENEMY_SPEED) randomSpeed = MIN_ENEMY_SPEED;

		ScreenElement enemyData;
		// 타입 별 데이터 저장
		if (randomType == EnemyType::Smol) // 1 x 1
		{
			enemyData = SetEnemyElementValue( { 1, 1 }, 1, { (MAXWIDTH - spawnPositionX), spawnPositionY }, { -randomSpeed, 0 }, (EnemyType)randomType);
			SetElementTimer(SMOL_SHOT_DELAY, &enemyData); // 공격 딜레이
		}
		else if (randomType == EnemyType::Medium) // 2 x 2
		{
			enemyData = SetEnemyElementValue({ 2, 2 }, 3, { (MAXWIDTH - spawnPositionX), spawnPositionY }, { -randomSpeed, 0 }, (EnemyType)randomType);
			SetElementTimer(MEDIUM_SHOT_DELAY, &enemyData); // 공격 딜레이
		}
		else if (randomType == EnemyType::Large) // 3 x 4
		{
			enemyData = SetEnemyElementValue({ 3, 3 }, 9, { (MAXWIDTH - spawnPositionX), spawnPositionY }, { -randomSpeed, 0 }, (EnemyType)randomType);
			SetElementTimer(LARGE_SHOT_DELAY, &enemyData); // 공격 딜레이
		}

		AddNode(&EnemyList, enemyData);
	}

	void SpawnEnemyAtPosition(Vector2 spawnPosition, int hp)
	{
		ScreenElement enemyData = SetEnemyElementValue({1, 1}, hp, spawnPosition, { 0, 0 }, EnemyType::Smol);
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