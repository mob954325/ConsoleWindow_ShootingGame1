#include "Player.h"

#include "DebugUtility.h"

#include "SpriteData.h"

namespace Player
{
	// 멤버 함수
	void Move();
	void Shoot();
	void Boom();
	void BoomEffect(float effectTime);
	void RenderPlayerPosition();
	void CreateBulletByLevel();

	// Player
	ScreenElement* playerInfo;
	PlayerWeaponInfo* playerWeaponInfo;

	enum PlayerState state;
	Vector2 nextVec = { 0,0 };

	float shotTimer = 0;
	float maxShotTimer = PLAYER_SHOTDELAY;
	float boomEffectTimer = 0;

	int PlayerInit()
	{
		boomEffectTimer = 10000;
		playerInfo = GameManager::GetPlayerInfo();
		playerWeaponInfo = GameManager::GetPlayerWeaponInfo();
		state = PlayerState::NonImmune;
		nextVec = { 2,2 }; // 임시

		return 1;
	}

	void PlayerUpdate()
	{
		shotTimer += Time::GetDeltaTime();

		if (playerInfo->health <= 0)
		{
			DebugLog("Player Dead\n");
			ChangePlayerImmnueState(0);
		}

		Move();
		Shoot();
		Boom();
	}

	void Move()
	{
		nextVec = playerInfo->position;
		if (Input::IsKeyDown('W'))
		{
			nextVec.y -= playerInfo->speed.y * Time::GetDeltaTime();
			//__PrintDebugLog("Up\n");
		}
		if (Input::IsKeyDown('S'))
		{
			nextVec.y += playerInfo->speed.y * Time::GetDeltaTime();
			//__PrintDebugLog("Down\n");
		}
		if (Input::IsKeyDown('A'))
		{
			nextVec.x -= playerInfo->speed.x * Time::GetDeltaTime();
			//__PrintDebugLog("Back\n");
		}
		if (Input::IsKeyDown('D'))
		{
			nextVec.x += playerInfo->speed.x * Time::GetDeltaTime();
			//__PrintDebugLog("Front\n");
		}

		if (GameManager::CheckVaildPosition(nextVec, playerInfo->scale) == 1)
		{
			playerInfo->position = nextVec;
		}
	}

	void Shoot()
	{
		if (shotTimer < maxShotTimer) return;

		if (Input::IsKeyDown('F'))
		{
			CreateBulletByLevel();
			__PrintDebugLog("Shoot\n");
		}

		shotTimer = 0;
	}

	void CreateBulletByLevel()
	{
		int bulletLevel = playerWeaponInfo->upGradeLevel;
		float PlayerPosX = playerInfo->position.x;
		float playerPosY = playerInfo->position.y;

		if (bulletLevel == 0)
		{
			BulletManager::CreateBullet(playerInfo->position, { 20, 0 }, Tag::PlayerObject);
		}
		else if (bulletLevel == 1)
		{
			BulletManager::CreateBullet({ PlayerPosX , playerPosY + 1}, { 20, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY }, { 20, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY - 1}, { 20, 0 }, Tag::PlayerObject);
		}
		else if (bulletLevel >= 2)
		{
			BulletManager::CreateBullet({ PlayerPosX , playerPosY + 1 }, { 20, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY }, { 20, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY - 1 }, { 20, 0 }, Tag::PlayerObject);


			BulletManager::CreateBullet({ PlayerPosX , playerPosY + 2 }, { 20, 20 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY - 2 }, { 20, -20 }, Tag::PlayerObject);
		}
	}

	void Boom()
	{
		if (playerWeaponInfo->boomCount <= 0) return;

		if (Input::IsKeyPressed('G'))
		{
			boomEffectTimer = 0;
			int totalScore = GameManager::KillALLOBJECTS(); // 점수 획득 후 모든 생성된 오브젝트 제거 
			GameManager::AddPlayScore(totalScore);
			playerWeaponInfo->boomCount--;
		}
	}

	// 임시 값
	float testTimer = 0;
	float maxTimer = 0.4;
	int index = 0;

	void RenderPlayer()
	{
		for (int i = 0; i <= playerInfo->scale.y; i++)
		{
			for (int j = 0; j <= playerInfo->scale.x; j++)
			{
				// 좌측 상단부터 랜더링하기
				int currX = (int)playerInfo->position.x - playerInfo->scale.x / 2 + j;
				int currY = (int)playerInfo->position.y - playerInfo->scale.y / 2 + i;
				if (currX == (int)playerInfo->position.x && currY == (int)playerInfo->position.y)
				{
					ConsoleRenderer::ScreenDrawChar(currX, currY, L'◉', FG_RED);
				}
				else
				{
					ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_GREEN);
				}
			}
		}

		RenderPlayerPosition();
		BoomEffect(0.8f); // 폭탄 이펙트

		//// 텍스트 파일로 불러온 이펙트 테스트
		//testTimer += Time::GetDeltaTime();
		//if (testTimer > maxTimer) { testTimer = 0, index++, index %= 3; }

		//wchar_t** t = SpriteData::GetHitEffect(index);
		//for (int i = 0; i < HITEFFECT_COUNT; i++)
		//{
		//	ConsoleRenderer::ScreenDrawString(10, 10 + i, t[i], FG_BLUE_DARK);
		//}
	}

	void RenderPlayerPosition()
	{
		char xChar[10];
		char yChar[10];

		_itoa_s((int)playerInfo->position.x, xChar, 10);
		_itoa_s((int)playerInfo->position.y, yChar, 10);

		ConsoleRenderer::ScreenDrawString(30, 1, xChar, FG_GREEN);
		ConsoleRenderer::ScreenDrawString(30, 2, yChar, FG_GREEN);
	}

	int CheckPlayerImmune()
	{
		return state == PlayerState::Immune ? 1 : 0;
	}

	void ChangePlayerImmnueState(int value)
	{
		if (value < 0 || value > 1) return; //유효하지 않는 숫자
		state = (PlayerState)value;
	}

	void BoomEffect(float effectTime)
	{
		if (playerWeaponInfo->boomCount < 0) return;

		boomEffectTimer += Time::GetDeltaTime();

		if (boomEffectTimer < effectTime)
		{
			for (int y = 0; y < MAXHEIGHT; y++)
			{
				for (int x = 0; x < MAXWIDTH; x++)
				{
					ConsoleRenderer::ScreenDrawChar(x, y, L'▒', FG_WHITE);
				}
			}
		}
	}
}