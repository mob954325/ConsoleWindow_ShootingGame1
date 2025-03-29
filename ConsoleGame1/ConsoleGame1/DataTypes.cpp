#include "DataTypes.h"

ScreenElement SetScreenElementValue(Vector2 scale, Vector2 vec, Vector2 speed, Tag tag)
{
	ScreenElement obj;
	obj.scale = scale;
	obj.position = { vec.x, vec.y };
	obj.tag = tag;
	obj.speed = speed;
	
	return obj;
}

ScreenElement SetScreenElementValue(Vector2 scale, int maxHealth, Vector2 vec, Vector2 speed, Tag tag)
{
	ScreenElement obj;
	obj.scale = scale;
	obj.health = maxHealth;
	obj.position = { vec.x, vec.y };
	obj.tag = tag;
	obj.speed = speed;

	return obj;
}

ScreenElement SetItemElementValue(Vector2 scale, int maxHealth, Vector2 vec, Vector2 speed, ItemType itemtype)
{
	ScreenElement obj;
	obj.scale = scale;
	obj.health = maxHealth;
	obj.position = { vec.x, vec.y };
	obj.speed = speed;
	obj.additionalElement.itemtype = itemtype;

	return obj;
}

PlayerWeaponInfo SetPlayerWeaponValue(int boomCount, int weaponLevel)
{
	PlayerWeaponInfo info;
	info.boomCount = boomCount;
	info.upGradeLevel = weaponLevel;

	return info;
}

int GetScreenPositionByRatio(int type, float value)
{
	if (type == 0) // 가로
	{
		return (int)(MAXWIDTH * value);
	}
	else if (type == 1) // 세로
	{
		return (int)(MAXHEIGHT * value);
	}

	return 0; // 잘못된 파라미터 값
}
