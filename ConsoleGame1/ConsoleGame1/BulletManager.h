﻿#pragma once
#include "ConsoleRenderer.h"
#include "List.h"
#include "Time.h"
#include "DataTypes.h"
#include "Vector.h"

namespace BulletManager
{
	void Initialize();
	void CreateBullet(Vector2 spawnPos, Vector2 speed, Tag tag);
	void CreateBullet(Vector2 spawnPos, Vector2 scale, Vector2 speed, Tag tag);
	void BulletUpdate();
	void BulletRender();
}