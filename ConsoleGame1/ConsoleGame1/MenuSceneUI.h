#pragma once
#include "ConsoleRenderer.h"
#include "RankingFileUtility.h"
#include "DataTypes.h"

namespace MenuSceneUI
{
	void Initialize();
	void RenderUI();

	void TitleUI();
	void ShowPressStartUI();
	void ShowHighestScore();
}