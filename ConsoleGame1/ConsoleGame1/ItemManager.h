#pragma once
#include "ConsoleRenderer.h"
#include "List.h"
#include "Time.h"
#include "DataTypes.h"
#include "Vector.h"

namespace ItemManager 
{
	void ItemManagerInitialize();
	void CreateItem(Vector2 spawnPos, Vector2 speed, ItemType type);
	void ItemUpdate();
	void ItemRender();
}