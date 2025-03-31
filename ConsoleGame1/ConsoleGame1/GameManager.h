#pragma once
#include "ConsoleRenderer.h"
#include "DataTypes.h"
#include "List.h"
#include "Time.h"
#include "Input.h"
#include "GameLoop.h"

#define SCORE_SCALE 100
#define BOSS_APPEAR_TIME 3

enum GameState
{
	BeforeStart = 0,
	Playing,
	PlayEnd,
};

enum GameResultState
{
	Lose = 0,
	Win = 1
};

namespace GameManager
{
	void Initialize();
	void FreeAllLists();

	Node*& GetBulletList();
	Node*& GetEnemyList();
	Node*& GetItemList();
	ScreenElement* GetPlayerInfo();
	PlayerWeaponInfo* GetPlayerWeaponInfo();
	ScreenElement* GetBossInfo();

	/// <summary>
	/// 오브젝트 크기만큼 점수를 반환하는 함수
	/// </summary>
	/// <returns>크기 * SCORE_SCALE</returns>
	int GetScoreBySize(ScreenElement obj);

	/// <summary>
	/// 현재 스코어 받기
	/// </summary>
	/// <returns>현재 누적된 스코어</returns>
	int GetCurrentPlayScore();

	// 게임 매니저 게임 상태 값을 가져오는 함수
	GameState GetGameState();

	// 게임 결과 상태 반환 함수
	GameResultState GetGameReslutState();

	// 게임 상태 설정 함수
	void SetGameState(GameState state);

	// 게임 결과 상태 설정 함수
	void SetGameResultState(GameResultState state);

	/// <summary>
	/// 해당 위치가 유효한 위치인지 확인
	/// </summary>
	/// <param name="pos">버퍼 위치</param>
	/// <returns>유효하지 않으면 0, 유효하면 1</returns>
	int CheckVaildPosition(Vector2 pos);

	/// <summary>
	/// 해당 위치가 유효한지 크기와 함께 확인하는 함수
	/// </summary>
	/// <param name="pos">버퍼 위치</param>
	/// <param name="scale">버퍼 크기</param>
	/// <returns>유효하지 않으면 0, 유효하면 1</returns>
	int CheckVaildPosition(Vector2 pos, Vector2 scale);

	/// <summary>
	/// 플레이어 사망 확인 함수
	/// </summary>
	/// <returns>사망 했으면 0, 생존해있으면 1</returns>
	int CheckIsPlayerDead();

	/// <summary>
	/// 스코어 추가하기
	/// </summary>
	/// <param name="value">추가할 스코어 값</param>
	void AddPlayScore(int value);

	/// <summary>
	/// 게임 결과 보여주는 함수 ( 승리 1, 패배 0)
	/// </summary>
	void ShowGameResult();

	/// <summary>
	/// 모든 오브젝트를 없애고 점수를 반환하는 함수
	/// </summary>
	int KillALLOBJECTS();
}