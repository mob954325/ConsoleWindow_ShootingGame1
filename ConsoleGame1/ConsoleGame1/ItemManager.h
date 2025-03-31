#pragma once
#include "ConsoleRenderer.h"
#include "List.h"
#include "Time.h"
#include "DataTypes.h"
#include "Vector.h"
#include "GameManager.h"

#define MAX_BOUNCE_NUMBER 5

namespace ItemManager 
{
	void Initialize();
	void CreateItem(Vector2 spawnPos, Vector2 speed, ItemType type);
	void ItemUpdate();
	void ItemRender();
}