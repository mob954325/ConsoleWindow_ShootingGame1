#pragma once
#include "ConsoleRenderer.h"
#include "DataTypes.h"
#include "List.h"
#include "Time.h"
#include "Vector.h"

#include <random>

#define MAX_ENEMY_SIZE 5
#define MAX_ENEMY_SPEED 17
#define MIN_ENEMY_SPEED 8

namespace EnemyManager
{
	void EnemyManagerInitialize();
	void EnemyUpdate();
	void EnemyRender();

	void SpawnEnemyAtRandomPosition();
	void SpawnEnemyAtPosition(Vector2 spawnPosition, int hp);
	void SetEnemySpanwer(float spawnDelay);
}