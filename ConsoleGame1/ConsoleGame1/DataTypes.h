#pragma once
#include "Vector.h"
#include <windows.h>

#define ENEMY_SPAWN_AREA_WIDTH 5
#define ENEMY_SPAWN_AREA_HEIGHT 21

#define MAXWIDTH 110
#define MAXHEIGHT 24

#define BULLET_SPEED 50

enum Tag
{
	None = 0,
	PlayerObject,
	EnemyObject,
	ItemObject,
};

enum ItemType
{
	WeaponUpgrade = 0,
	BoomItem,
	HpRestore,
	ItemTypeCount
};

enum ParticleType
{
	Hit = 0,
	Dead,
	PlayerBoom,
};

enum EnemyType
{
	Smol = 0,
	Medium,
	Large,
	EnemyTypeCount
};

struct ScreenElement
{
	// 오브젝트 태그
	Tag tag = Tag::None;
	// 오브젝트 크기
	Vector2 scale;
	// 오브젝트 크기만큼의 좌표값
	Vector2 position; 
	// 오브젝트 스피드
	Vector2 speed;
	// 체력
	int health = 1;
	// 다양하게 사용할 오브젝트의 독자적 타이머
	float maxTime = 0;
	float remainTime = 0;

	// 추가 오브젝트 정보 ( 특정 오브젝트용 )
	union AdditionalElement
	{
		ItemType itemtype;
		ParticleType particleType;
		EnemyType enemyType;
	} additionalElement;
};

struct PlayerWeaponInfo
{
	int boomCount = 0;
	int upGradeLevel = 0; // 무기 형태로 바꿀수도 있을듯?
};

ScreenElement SetScreenElementValue(Vector2 scale, Vector2 vec, Vector2 speed, Tag tag);
ScreenElement SetScreenElementValue(Vector2 scale, int maxHealth, Vector2 vec, Vector2 speed, Tag tag);
ScreenElement SetEnemyElementValue(Vector2 scale, int maxHealth, Vector2 vec, Vector2 speed, EnemyType enemyType);
ScreenElement SetItemElementValue(Vector2 scale, int maxHealth, Vector2 vec, Vector2 speed, ItemType itemtype);
PlayerWeaponInfo SetPlayerWeaponValue(int boomCount, int weaponLevel);
void SetElementTimer(float maxTime, ScreenElement* obj);

/// <summary>
/// 비율값으로 스크린 좌표값 구하는 함수 ( 0 - 1 사이 값 )
/// </summary>
/// <param name="type">0이면 가로 1이면 세로값</param>
/// <param name="value">비율값</param>
/// <returns>비율에 따른 스크린 좌표값</returns>
int GetScreenPositionByRatio(int type, float value);
