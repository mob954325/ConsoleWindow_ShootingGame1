#include "GameManager.h"

#include "DebugUtility.h"

namespace GameManager
{
	// 여기에 리스트 관리
	ObjectNode* BulletList = NULL;			// 총알 리스트
	ObjectNode* EnemyList = NULL;			// 적 리스트
	ObjectNode* ItemList = NULL;			// 아이템 리스트
	ScreenElement playerElement = {};		// 플레이어 기본 정보
	PlayerWeaponInfo playerWeaponInfo = {}; // 플레이어 무기 정보

	GameState gameState = GameState::BeforeStart;		// 현재 게임 상태
	GameResultState gameResult = GameResultState::Lose;	// 게임 결과 상태
	int playScore = 0;

	float changeSceneTimer = 0;
	float maxChangeSceneTime = 5;

	void GameManagerInitialize()
	{
		// 초기화
		gameState = GameState::BeforeStart;
		gameResult = GameResultState::Lose;

		playerElement = SetScreenElementValue({ 2,0 }, 20, { MAXWIDTH / 2, MAXHEIGHT / 2 }, {12, 12}, Tag::PlayerObject);
		playerWeaponInfo = SetPlayerWeaponValue(3, 0);
		playScore = 0;
	}

	void FreeAllLists()
	{
		FreeAllNode(&BulletList);
		FreeAllNode(&EnemyList);
	}

	int KillALLOBJECTS()
	{		
		int totalScore = 0;

		// 적
		int enemyCount = NodeCount(EnemyList);
		for (int i = 0; i < enemyCount; i++)
		{
			Node* currEnemy = FindNode(EnemyList, i);
			if (!currEnemy) continue;

			int enemyScore = GameManager::GetScoreBySize(currEnemy->data);
			totalScore += enemyScore;
		}

		// 총알
		int bulletCount = NodeCount(BulletList);
		for (int i = 0; i < bulletCount; i++)
		{
			Node* currBullet = FindNode(BulletList, i);
			if (!currBullet) continue;

			int bulletScore = GameManager::GetScoreBySize(currBullet->data);
			totalScore += bulletScore;
		}

		// 모든 리스트 없애기
		FreeAllNode(&BulletList);
		FreeAllNode(&EnemyList);

		return totalScore;
	}

	Node*& GetBulletList()
	{
		return BulletList;
	}

	Node*& GetEnemyList()
	{
		return EnemyList;
	}

	Node*& GetItemList()
	{
		return ItemList;
	}

	ScreenElement* GetPlayerInfo()
	{
		return &playerElement;
	}

	PlayerWeaponInfo* GetPlayerWeaponInfo()
	{
		return &playerWeaponInfo;
	}

	int GetScoreBySize(ScreenElement obj)
	{
		return obj.scale.x * SCORE_SCALE + obj.scale.y * SCORE_SCALE;
	}

	int GetCurrentPlayScore()
	{
		return playScore;
	}

	GameState GetGameState()
	{
		return gameState;
	}

	GameResultState GetGameReslutState()
	{
		return gameResult;
	}

	void SetGameState(GameState state)
	{
		gameState = state;

		if(state == GameState::PlayEnd) GameManager::FreeAllLists(); // 게임 종료를 받으면 할당한 데이터 제거
	}

	void SetGameResultState(GameResultState state)
	{
		gameResult = state;
	}

	int CheckVaildPosition(Vector2 pos)
	{
		if (pos.x < 0 || pos.x > MAXWIDTH || pos.y < 0 || pos.y > MAXHEIGHT) return 0;

		return 1;
	}

	int CheckVaildPosition(Vector2 pos, Vector2 scale)
	{
		if (pos.x - scale.x / 2 < 0 //
		|| pos.x + scale.x / 2 > MAXWIDTH
		|| pos.y - scale.y / 2 < 0 //
		|| pos.y + scale.y / 2 > MAXHEIGHT) return 0;

		return 1;
	}

	int CheckIsPlayerDead()
	{
		if (playerElement.health <= 0)
		{
			playerElement.health = 0;
			return 0;
		}

		return 1;
	}

	void AddPlayScore(int value)
	{
		playScore += value;
	}

	void ShowGameResult()
	{
		changeSceneTimer += Time::GetDeltaTime();

		int titlePosX = GetScreenPositionByRatio(0, 0.5);
		int titlePosY = GetScreenPositionByRatio(1, 0.2);

		if (gameResult == GameResultState::Lose)
		{
			ConsoleRenderer::ScreenDrawString(titlePosX, titlePosY, "Defeat ...", FG_RED_DARK);
		}
		else if (gameResult == GameResultState::Win)
		{
			gameResult = GameResultState::Win;
			ConsoleRenderer::ScreenDrawString(titlePosX, titlePosY, "Victory !!!", FG_GREEN);
		}

		if (changeSceneTimer > maxChangeSceneTime)
		{
			changeSceneTimer = 0;
			GameLoop::SceneChangeToNext();
		}
	}
}