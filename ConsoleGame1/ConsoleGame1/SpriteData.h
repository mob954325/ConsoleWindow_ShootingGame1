#pragma once
#include "SpriteFileUtility.h"

#include "stdio.h"
#include "stdlib.h"

// 프레임 개수
#define HITEFFECT_COUNT 3
#define DEADEFFECT_COUNT 5
#define PLAYERBOOMEFFECT_COUNT 5

namespace SpriteData
{
	void Initialize();
	wchar_t** GetHitEffect(int frameValue, int* out_columnNum);
	wchar_t** GetBoomEffect(int frameValue, int* out_columnNum);
	wchar_t** GetPlayerBoomEffect(int frameValue, int* out_columnNum);
	void FreeAllSprites();
}