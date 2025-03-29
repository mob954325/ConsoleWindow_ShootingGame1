#pragma once
#include "ConsoleRenderer.h"
#include "Input.h"
#include "GameLoop.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "ItemManager.h"
#include "GameManager.h"
#include "Collider.h"

#include "PlayScreenUI.h"

#include "DebugUtility.h"

namespace PlayScene
{
	void Initialize();
	void Update();
	void Render();
}