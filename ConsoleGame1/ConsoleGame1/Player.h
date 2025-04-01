#pragma once
#include "ConsoleRenderer.h"
#include "Input.h"
#include "Time.h"
#include "BulletManager.h"
#include "GameManager.h"

#include <Windows.h>

#define PLAYER_SHOTDELAY 0.2f

enum PlayerState
{
	NonImmune = 0,	// 피격 받음
	Immune,			// 피격 받지 못함
};

namespace Player
{
	int PlayerInit();
	void PlayerUpdate();
	void RenderPlayer();

	/// <summary>
	/// 플레이어아 무적인지 확인하는 함수
	/// </summary>
	/// <returns>무적이면 1 아니면 0 반환</returns>
	int CheckPlayerImmune();
	
	/// <summary>
	/// 플레이어 무적상태 변경 함수
	/// </summary>
	/// <param name="value">0 : 무적아님, 1 : 무적</param>
	void ChangePlayerImmnueState(int value);
}