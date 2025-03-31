#pragma once
#include "DataTypes.h"
#include "Time.h"

#include "GameManager.h"
#include "BulletManager.h"
#include "ParticleManager.h"

#define BOSS_ATTACK_COUNT 3

namespace Boss
{
	void Initialize();
	void BossUpdate();
	void BossRender();
}