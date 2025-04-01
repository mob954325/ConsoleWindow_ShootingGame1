#include "EndSceneUI.h"
#include "DebugUtility.h"

namespace EndSceneUI
{
	float inputBlockTimer = 0;
	float maxInputBlockTime = 3;

	char buffer[100];
	int bufferCount = 0;

	int isActiveSetName = 1;
	int isActiveSceneChange = 0;

	char VirtualKeyToChar(UINT vk) {
		BYTE keyboardState[256] = { 0 };
		WORD ascii;
		if (ToAscii(vk, MapVirtualKey(vk, MAPVK_VK_TO_VSC), keyboardState, &ascii, 0) == 1) {
			return (char)ascii;
		}
		return '\0';
	}

	void Initialize()
	{
		inputBlockTimer = 0;
		maxInputBlockTime = 3;

		buffer[100];
		bufferCount = 0;

		isActiveSetName = 1;
		isActiveSceneChange = 0;
	}

	void RenderUI()
	{
		inputBlockTimer += Time::GetDeltaTime();

		ShowTotalScore();
		CheckSpaceToMenu();
		ShowGameResult();
	}

	void ShowGameResult()
	{
		int scoreTextPosX = GetScreenPositionByRatio(0, 0.5f);
		int scoreTextPosY = GetScreenPositionByRatio(1, 0.3f);

		if (GameManager::GetGameReslutState() == GameResultState::Lose)
		{
			ConsoleRenderer::ScreenDrawString(scoreTextPosX, scoreTextPosY, "패배", FG_RED);
		}
		else if (GameManager::GetGameReslutState() == GameResultState::Win)
		{
			ConsoleRenderer::ScreenDrawString(scoreTextPosX, scoreTextPosY, "승리", FG_GREEN);
		}
	}

	void ShowTotalScore()
	{
		int totalScore = GameManager::GetCurrentPlayScore();
		int scoreTextPosX= GetScreenPositionByRatio(0, 0.5f);
		int scoreTextPosY = GetScreenPositionByRatio(1, 0.4f);
		char scoreBuffer[100];
		
		_itoa_s(totalScore, scoreBuffer, 10);

		ConsoleRenderer::ScreenDrawString(scoreTextPosX - 15, scoreTextPosY + 1, "Score : ", FG_GRAY);
		ConsoleRenderer::ScreenDrawString(scoreTextPosX, scoreTextPosY + 1, scoreBuffer, FG_GRAY);
	}

	void CheckSpaceToMenu()
	{
		if (inputBlockTimer < maxInputBlockTime) return;

		int helpTextPosX = GetScreenPositionByRatio(0, 0.4f);
		int helpTextPosY = GetScreenPositionByRatio(1, 0.8f);

		if (isActiveSetName == 1 && RankingFileUtility::CheckScore(GameManager::GetCurrentPlayScore()) == 1)
		{
			ConsoleRenderer::ScreenDrawString(helpTextPosX, helpTextPosY - 2, "New Record !!!", FG_YELLOW);
			ConsoleRenderer::ScreenDrawString(helpTextPosX - 10, helpTextPosY, "name : ", FG_WHITE);
			ConsoleRenderer::ScreenDrawString(helpTextPosX - 10, helpTextPosY + 1, L"엔터로 입력 완료하기", FG_WHITE);
			for (int i = 0; i < 255; i++)
			{
				if (bufferCount >= 0 && Input::IsKeyPressed(VK_BACK))
				{
					buffer[bufferCount] = '\0';
					if(bufferCount > 0) bufferCount--;
					break;	
				}

				if (Input::IsKeyPressed(i) && (i >= 0x30 && i <= 0x5A))
				{
					buffer[bufferCount++] = VirtualKeyToChar(i);
				}
			}
			ConsoleRenderer::ScreenDrawString(helpTextPosX, helpTextPosY, buffer, FG_WHITE);

			if (Input::IsKeyPressed(VK_RETURN))
			{
				isActiveSetName = 0;
				RankingFileUtility::UpdateScore(GameManager::GetCurrentPlayScore(), buffer);
				RankingFileUtility::WriteScore();
			}
		}
		else
		{
			isActiveSceneChange = 1;
		}
		
		ConsoleRenderer::ScreenDrawString(helpTextPosX, helpTextPosY + 5, L"스페이스 눌러서 메뉴로 돌아가기", FG_WHITE);

		if (isActiveSceneChange == 1 && Input::IsKeyPressed(VK_SPACE))
		{
			GameLoop::SceneChangeToNext();
		}
	}
}