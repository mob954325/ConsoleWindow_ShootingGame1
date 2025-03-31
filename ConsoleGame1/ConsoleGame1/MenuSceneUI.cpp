#include "MenuSceneUI.h";

namespace MenuSceneUI
{
	void InputGuide();

	void RenderUI()
	{
		TitleUI();
		ShowPressStartUI();
		InputGuide();
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

	void InputGuide()
	{
		int posX = GetScreenPositionByRatio(0, 0.1);
		int posY = GetScreenPositionByRatio(1, 0.1);
		ConsoleRenderer::ScreenDrawString(posX, posY , L"- Input Guide -", FG_WHITE);
		ConsoleRenderer::ScreenDrawString(posX, posY + 1, L"이동 : WASD", FG_WHITE);
		ConsoleRenderer::ScreenDrawString(posX, posY + 2, L"발사 : J", FG_WHITE);
		ConsoleRenderer::ScreenDrawString(posX, posY + 3, L"폭탄 : K [ 일반 적과 총알만 제거 ]", FG_WHITE);
	}
}