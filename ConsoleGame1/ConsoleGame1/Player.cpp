﻿#include "Player.h"

#include "ParticleManager.h"
#include "DebugUtility.h"

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
	Vector2 normalSpeed = { 0,0 };

	float shotTimer = 0;
	float maxShotTimer = PLAYER_SHOTDELAY;

	int PlayerInit()
	{
		playerInfo = GameManager::GetPlayerInfo();
		playerWeaponInfo = GameManager::GetPlayerWeaponInfo();
		state = PlayerState::NonImmune;
		nextVec = { 2,2 };
		normalSpeed = playerInfo->speed;

		return 1;
	}

	void PlayerUpdate()
	{
		shotTimer += Time::GetDeltaTime();

		if (playerInfo->health <= 0)
		{
			DebugLog("Player Dead\n");
			SoundController::PlayEffectSound("GameOver.wav");
			ParticleManager::ShowParticleAtPosition(playerInfo->position, ParticleType::Dead, 0.14f);
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
		if (Input::IsKeyPressed(VK_SHIFT)) // 이동 속도 증가
		{
			playerInfo->speed = { playerInfo->speed.x * 1.5f, playerInfo->speed.y * 1.5f };
		}
		if (Input::IsKeyReleased(VK_SHIFT)) // 원래 이동속도로 돌리기
		{
			playerInfo->speed = normalSpeed;
		}

		if (GameManager::CheckVaildPosition(nextVec, playerInfo->scale) == 1)
		{
			playerInfo->position = nextVec;
		}
	}

	void Shoot()
	{
		if (shotTimer < maxShotTimer) return;

		if (Input::IsKeyDown('J'))
		{
			CreateBulletByLevel();
			SoundController::PlayEffectSound("Shot.wav");
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
			BulletManager::CreateBullet(playerInfo->position, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);
		}
		else if (bulletLevel == 1)
		{
			BulletManager::CreateBullet({ PlayerPosX , playerPosY + 1}, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY }, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY - 1}, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);
		}
		else if (bulletLevel >= 2)
		{
			BulletManager::CreateBullet({ PlayerPosX , playerPosY + 1 }, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY }, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY - 1 }, { BULLET_SPEED * 2, 0 }, Tag::PlayerObject);


			BulletManager::CreateBullet({ PlayerPosX , playerPosY + 2 }, { BULLET_SPEED * 2, BULLET_SPEED * 2 }, Tag::PlayerObject);
			BulletManager::CreateBullet({ PlayerPosX , playerPosY - 2 }, { BULLET_SPEED * 2, -BULLET_SPEED * 2 }, Tag::PlayerObject);
		}
	}

	void Boom()
	{
		if (playerWeaponInfo->boomCount <= 0) return;

		if (Input::IsKeyPressed('K'))
		{
			int totalScore = GameManager::KillALLOBJECTS(); // 점수 획득 후 모든 생성된 오브젝트 제거 
			BoomEffect(0.8f); // 폭탄 이펙트

			playerWeaponInfo->boomCount--;
			GameManager::AddPlayScore(totalScore);
			SoundController::PlayEffectSound("Boom.wav");

		}
	}

	// 임시 값
	float testTimer = 0;
	float maxTimer = 0.4f;
	int index = 0;

	void RenderPlayer()
	{
		for (int i = 0; i <= playerInfo->scale.y; i++)
		{
			for (int j = 0; j <= playerInfo->scale.x; j++)
			{
				// 좌측 상단부터 랜더링하기
				int currX = (int)(playerInfo->position.x - playerInfo->scale.x / 2 + j);
				int currY = (int)(playerInfo->position.y - playerInfo->scale.y / 2 + i);
				ConsoleRenderer::ScreenDrawChar(currX, currY, L'█', FG_WHITE);
			}
		}

		//RenderPlayerPosition();
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
		if (playerWeaponInfo->boomCount <= 0) return;
		
		if (Input::IsKeyDown('K'))
		{
			ParticleManager::ShowParticleAtPosition({MAXWIDTH / 2 - MAXWIDTH / 5, MAXHEIGHT / 2 - MAXHEIGHT / 5 }, ParticleType::PlayerBoom, 0.2f);
		}
	}
}