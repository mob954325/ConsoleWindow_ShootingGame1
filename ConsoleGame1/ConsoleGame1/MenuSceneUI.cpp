#include "MenuSceneUI.h";

namespace MenuSceneUI
{
	void RenderUI()
	{
		TitleUI();
		ShowPressStartUI();
	}

	void TitleUI()
	{
		int posX = GetScreenPositionByRatio(0, 0.49);	
		int posY = GetScreenPositionByRatio(1, 0.3);	
		ConsoleRenderer::ScreenDrawString(posX + 1, posY, "Space Shooting", FG_GREEN);
	}

	void ShowPressStartUI()
	{
		int posX = GetScreenPositionByRatio(0, 0.47);
		int posY = GetScreenPositionByRatio(1, 0.8);
		ConsoleRenderer::ScreenDrawString(posX, posY, "Press Space to Start", FG_GREEN);
	}
}