#include "PlayScreenUI.h"

namespace PlayScreenUI
{
	void Anim(); // 임시

	ScreenElement* playerInfo;	
	PlayerWeaponInfo* playerWeaponInfo;
	GameState gameState;

	float feedBackTimer = 0;
	float maxFeedBackTime = 1.5f;
	int isPlayerHit = 0; // 1 : true, 0 : false

	void PlayScreenUIInitialize()
	{
		gameState = GameState::BeforeStart();
		playerInfo = GameManager::GetPlayerInfo();
		playerWeaponInfo = GameManager::GetPlayerWeaponInfo();
	}

	void RenderUI()
	{
		feedBackTimer += Time::GetDeltaTime();
		if (feedBackTimer > maxFeedBackTime) isPlayerHit = 0;

		RanderGameFrame(); //-> 프레임 드랍 심함
		RenderPlayerHp();
		RenderPlayTime();
		RenderBoomCount();
		RenderScore();
		RenderProfile();
	}

	void RanderGameFrame()
	{
		ConsoleRenderer::ScreenDrawString(0, MAXHEIGHT, L"-----------------------------------------------------------------------------------------------------------------------", FG_BLUE_DARK);
	}

	void RenderPlayerHp()
	{
		int gap = 5;

		// 체력 숫자
		int currHealth = playerInfo->health;
		char hpBuffer[10];
		_itoa_s(currHealth, hpBuffer, 10);
		ConsoleRenderer::ScreenDrawString(0 , MAXHEIGHT + gap, hpBuffer, FG_GREEN); 

		// 체력 그림
		for (int i = 0; i < currHealth; i++)
		{
			ConsoleRenderer::ScreenDrawChar(i + gap , MAXHEIGHT + gap, 'I', FG_BLUE_DARK);
		}
	}

	void RenderBoomCount()
	{
		int gap = 2;
		int boomTextPosX = GetScreenPositionByRatio(0, 0.3);
		int boomTextPosY = GetScreenPositionByRatio(1, 1.1);

		// 체력 숫자
		int boomCount = playerWeaponInfo->boomCount;
		ConsoleRenderer::ScreenDrawString(boomTextPosX, boomTextPosY, "Boom : ", FG_GREEN);
		for (int i = 1; i <= boomCount; i++)
		{
			ConsoleRenderer::ScreenDrawChar((boomTextPosX * 1.2f)+ gap * i, boomTextPosY, L'⽶', FG_GREEN);

		}
	}

	void RenderPlayTime()
	{
		int positionX = 0;

		int elapsedTime = Time::GetTotalTime();
		int min = elapsedTime / 60;
		int sec = elapsedTime % 60;

		char minBuffer[5];
		char secBuffer[3];
		_itoa_s(min, minBuffer, 10);
		_itoa_s(sec, secBuffer, 10);

		ConsoleRenderer::ScreenDrawString(positionX, MAXHEIGHT + 3, "Time : ", FG_BLUE);
		ConsoleRenderer::ScreenDrawString(positionX + 8, MAXHEIGHT + 3, minBuffer, FG_BLUE);
		ConsoleRenderer::ScreenDrawString(positionX + 10, MAXHEIGHT + 3, " : ", FG_BLUE);
		ConsoleRenderer::ScreenDrawString(positionX + 14, MAXHEIGHT + 3, secBuffer, FG_BLUE);
	}

	void RenderScore()
	{
		int positionX = 10;

		int currScore = GameManager::GetCurrentPlayScore();
		char scoreBuffer[100];
		_itoa_s(currScore, scoreBuffer, 10);

		ConsoleRenderer::ScreenDrawString(0, MAXHEIGHT + 1, "Score : ", FG_GRAY);
		ConsoleRenderer::ScreenDrawString(positionX, MAXHEIGHT + 1, scoreBuffer, FG_GRAY);
	}

	wchar_t face1[12] = L"| l _ l  |";
	wchar_t face2[12] = L"| - _ -  |";
	wchar_t face3[12] = L"| > ~ <  |";

	void RenderProfile()
	{
		if (isPlayerHit == 1)
		{
			// hit
			ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 2, "+--------+", FG_RED);
			ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 3, face3, FG_RED);
			ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 4, "|        |", FG_RED);
			ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 5, "+--------+", FG_RED);
		}
		else
		{
			ConsoleRenderer::ScreenDrawString(78, MAXHEIGHT + 5, L"█", FG_RED); // 임시
			Anim();
		}
	}

	void ActivePlayerHitEffect()
	{
		isPlayerHit = 1;
		feedBackTimer = 0;
	}


	void Anim()
	{
		if ((int)Time::GetTotalTime() % 2 == 0)
		{
			ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 3, face1, FG_GRAY);
		}
		else
		{
			ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 3, face2, FG_GRAY);
		}
		ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 2, "+--------+", FG_GRAY);
		ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 4, "|        |", FG_GRAY);
		ConsoleRenderer::ScreenDrawString(50, MAXHEIGHT + 5, "+--------+", FG_GRAY);
	}
}