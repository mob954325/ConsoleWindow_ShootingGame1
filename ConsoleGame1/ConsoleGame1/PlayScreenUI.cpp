#include "PlayScreenUI.h"

namespace PlayScreenUI
{
	void PlayerProfileRender(); // 임시
	void BossHpProcess(); 

	ScreenElement* playerInfo;	
	ScreenElement* bossInfo;
	PlayerWeaponInfo* playerWeaponInfo;
	GameState gameState;

	float feedBackTimer = 0;
	float maxFeedBackTime = 1.5f;
	int isPlayerHit = 0; // 1 : true, 0 : false

	// boss용 변수들
	float bossHpAppearTimer = 0;
	float maxBossHpAppearTime = 0.04f;

	float bossWarningUITimer = 0;
	float maxBossWarningUITime = 0.08f;
	int warningType = 0; // 0 . 1

	int hpGaugeCount = 0; // 최대 10
	int isBossAppeared = 0; // 보스 등장 확인 -> 등장 애니메이션용 변수

	void Initialize()
	{
		gameState = GameState::BeforeStart;
		playerInfo = GameManager::GetPlayerInfo();
		playerWeaponInfo = GameManager::GetPlayerWeaponInfo();
		bossInfo = GameManager::GetBossInfo();
	}

	void RenderUI()
	{
		bossHpAppearTimer += Time::GetDeltaTime();
		bossWarningUITimer += Time::GetDeltaTime();
		feedBackTimer += Time::GetDeltaTime();
		if (feedBackTimer > maxFeedBackTime) isPlayerHit = 0;

		RanderGameFrame(); //-> 프레임 드랍 심함
		RenderPlayerHp();
		RenderPlayTime();
		RenderBoomCount();
		RenderScore();
		RenderProfile();

		RenderBossWarning();

		if (Time::GetTotalTime() > BOSS_APPEAR_TIME)
		{
			RenderBossHp();
		}
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
			ConsoleRenderer::ScreenDrawChar(i + gap , MAXHEIGHT + gap, L'█', FG_BLUE_DARK);
		}
	}

	void RenderBoomCount()
	{
		int gap = 2;
		int boomTextPosX = GetScreenPositionByRatio(0, 0.3f);
		int boomTextPosY = GetScreenPositionByRatio(1, 1.1f);

		// 체력 숫자
		int boomCount = playerWeaponInfo->boomCount;
		ConsoleRenderer::ScreenDrawString(boomTextPosX, boomTextPosY, "Boom : ", FG_GREEN);
		for (int i = 1; i <= boomCount; i++)
		{
			ConsoleRenderer::ScreenDrawChar((int)((boomTextPosX * 1.2f)+ gap * i), boomTextPosY, L'B', FG_GREEN);

		}
	}

	void RenderPlayTime()
	{
		int positionX = 0;

		float elapsedTime = Time::GetTotalTime();
		int min = (int)(elapsedTime / 60);
		int sec = (int)(elapsedTime) % 60;

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
			//ConsoleRenderer::ScreenDrawString(78, MAXHEIGHT + 5, L"█", FG_RED); // 임시
			PlayerProfileRender();
		}
	}

	void RenderBossHp()
	{
		int gap = 1;

		// 체력 숫자
		int currHealth = bossInfo->health;
		char hpBuffer[10];
		_itoa_s(currHealth, hpBuffer, 10);

		int gapFromHealthTitle = 10;
		int posY = GetScreenPositionByRatio(1, 0.1f);
		ConsoleRenderer::ScreenDrawString(3, posY, L"BOSS", FG_GREEN);

		BossHpProcess();

		// 체력 그림
		if (isBossAppeared == 0) // 순차적 생성
		{
			for (int i = 0; i < hpGaugeCount; i++)
			{
				ConsoleRenderer::ScreenDrawChar(gapFromHealthTitle + i + gap, posY, L'█', FG_BLUE_DARK);
			}
		}

		if (isBossAppeared == 1)
		{
			for (int i = 0; i < currHealth; i++)
			{
				ConsoleRenderer::ScreenDrawChar(gapFromHealthTitle + i + gap, posY, L'█', FG_BLUE_DARK);
			}
		}
	}

	void RenderBossWarning()
	{
		float totalTime = Time::GetTotalTime();
		if (totalTime >= BOSS_APPEAR_TIME - 2 && totalTime <= BOSS_APPEAR_TIME)
		{
			if (bossWarningUITimer > maxBossWarningUITime)
			{
				bossHpAppearTimer = 0;
				warningType = warningType == 1 ? 0 : 1;
			}

			int posX = GetScreenPositionByRatio(0, 0.3f);
			int posY = GetScreenPositionByRatio(1, 0.4f);

			if(warningType == 1)ConsoleRenderer::ScreenDrawString(posX, posY, L"██████████████████ Boss incoming ██████████████████", FG_YELLOW_DARK);
			if(warningType == 0)ConsoleRenderer::ScreenDrawString(posX, posY, L"██████████████████ Boss incoming ██████████████████", FG_RED_DARK);
		}
	}

	void ActivePlayerHitEffect()
	{
		isPlayerHit = 1;
		feedBackTimer = 0;
	}


	void PlayerProfileRender()
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

	void BossHpProcess()
	{
		// hpUI 생성 절차
		if (hpGaugeCount < bossInfo->health && bossHpAppearTimer > maxBossHpAppearTime) // 타이머
		{
			hpGaugeCount++;
			bossHpAppearTimer = 0;
		}

		if (hpGaugeCount >= bossInfo->health) isBossAppeared = 1;
	}
}