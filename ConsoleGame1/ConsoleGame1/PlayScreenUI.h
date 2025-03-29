#pragma once
#include "ConsoleRenderer.h"
#include "GameManager.h"
#include "DataTypes.h"
#include "Time.h"

namespace PlayScreenUI
{
	void PlayScreenUIInitialize();
	void RenderUI();
	void RanderGameFrame();
	void RenderPlayerHp();
	void RenderBoomCount();
	void RenderPlayTime();
	void RenderScore();
	void RenderProfile();

	void ActivePlayerHitEffect();
}