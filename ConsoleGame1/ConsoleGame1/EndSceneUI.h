#pragma once
#include "GameManager.h"
#include "RankingFileUtility.h"
#include "Input.h"
#include <stdio.h>
#include <Windows.h>

namespace EndSceneUI
{
	void Initialize();
	void RenderUI();
	void ShowGameResult();
	void ShowTotalScore();
	void CheckSpaceToMenu();
}