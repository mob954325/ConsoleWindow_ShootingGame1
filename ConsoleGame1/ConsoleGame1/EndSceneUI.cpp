#include "EndSceneUI.h"

namespace EndSceneUI
{
	float inputBlockTimer = 0;
	float maxInputBlockTime = 3;

	void RenderUI()
	{
		inputBlockTimer += Time::GetDeltaTime();

		ShowTotalScore();
		CheckSpaceToMenu();
		ShowGameResult();
	}

	void ShowGameResult()
	{
		int scoreTextPosX = GetScreenPositionByRatio(0, 0.4);
		int scoreTextPosY = GetScreenPositionByRatio(1, 0.7);

		if (GameManager::GetGameReslutState() == GameResultState::Lose)
		{
			ConsoleRenderer::ScreenDrawString(scoreTextPosX, scoreTextPosY, "�й�", FG_GRAY);
		}
		else if (GameManager::GetGameReslutState() == GameResultState::Win)
		{
			ConsoleRenderer::ScreenDrawString(scoreTextPosX, scoreTextPosY, "�¸�", FG_GRAY);
		}
	}

	void ShowTotalScore()
	{
		int totalScore = GameManager::GetCurrentPlayScore();
		int scoreTextPosX= GetScreenPositionByRatio(0, 0.5);
		int scoreTextPosY = GetScreenPositionByRatio(1, 0.4);
		char scoreBuffer[100];
		
		_itoa_s(totalScore, scoreBuffer, 10);

		ConsoleRenderer::ScreenDrawString(scoreTextPosX - 15, scoreTextPosY + 1, "Score : ", FG_GRAY);
		ConsoleRenderer::ScreenDrawString(scoreTextPosX, scoreTextPosY + 1, scoreBuffer, FG_GRAY);
	}

	void CheckSpaceToMenu()
	{
		if (inputBlockTimer < maxInputBlockTime) return;

		int helpTextPosX = GetScreenPositionByRatio(0, 0.45);
		int helpTextPosY = GetScreenPositionByRatio(1, 0.8);
		ConsoleRenderer::ScreenDrawString(helpTextPosX, helpTextPosY, L"�����̽� ������ �޴��� ���ư���", FG_GREEN);

		if (Input::IsKeyPressed(VK_SPACE))
		{
			GameLoop::SceneChangeToNext();
		}
	}
}