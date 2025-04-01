#include "MenuSceneUI.h"

namespace MenuSceneUI
{
	void InputGuide();

	char* rankerName[3];
	int rankerScore[3];

	void Initialize()
	{
		for(int i = 1; i <= RANKER_COUNT; i++)
		{
			int score = RankingFileUtility::GetHighScore(i, &rankerName[i - 1]);
			rankerScore[i - 1] = score;
		}
	}

	void RenderUI()
	{
		TitleUI();
		ShowPressStartUI();
		InputGuide();
		ShowHighestScore();
	}

	void TitleUI()
	{
		int posX = GetScreenPositionByRatio(0, 0.49f);	
		int posY = GetScreenPositionByRatio(1, 0.3f);	
		ConsoleRenderer::ScreenDrawString(posX + 1, posY, "Space Shooting", FG_GREEN);
	}

	void ShowPressStartUI()
	{
		int posX = GetScreenPositionByRatio(0, 0.47f);
		int posY = GetScreenPositionByRatio(1, 0.8f);
		ConsoleRenderer::ScreenDrawString(posX, posY, "Press Space to Start", FG_GREEN);
	}

	void ShowHighestScore()
	{
		int posX = GetScreenPositionByRatio(0, 0.7f);
		int posY = GetScreenPositionByRatio(1, 0.1f);
		ConsoleRenderer::ScreenDrawString(posX, posY - 2 , L"- Rank -", FG_WHITE);
		for (int i = 0; i < RANKER_COUNT; i++)
		{
			ConsoleRenderer::ScreenDrawString(posX, posY + i * 2, rankerName[i], FG_WHITE);
			char buffer[100];
			_itoa_s(rankerScore[i], buffer, 10);
			ConsoleRenderer::ScreenDrawString(posX + 16, posY + i * 2, buffer, FG_WHITE);
		}
	}

	void InputGuide()
	{
		int posX = GetScreenPositionByRatio(0, 0.1f);
		int posY = GetScreenPositionByRatio(1, 0.1f);
		ConsoleRenderer::ScreenDrawString(posX, posY , L"- Input Guide -", FG_WHITE);
		ConsoleRenderer::ScreenDrawString(posX, posY + 1, L"이동 : WASD", FG_WHITE);
		ConsoleRenderer::ScreenDrawString(posX, posY + 2, L"발사 : J", FG_WHITE);
		ConsoleRenderer::ScreenDrawString(posX, posY + 3, L"폭탄 : K [ 일반 적과 총알만 제거 ]", FG_WHITE);
	}
}