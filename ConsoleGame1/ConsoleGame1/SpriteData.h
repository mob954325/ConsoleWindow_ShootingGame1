#pragma once
#include "FileUtility.h"

#include "stdio.h"
#include "stdlib.h"

// 프레임 개수
#define HITEFFECT_COUNT 3

namespace SpriteData
{
	void Initialize();
	wchar_t** GetHitEffect(int frameValue, int* out_columnNum);
	void FreeAllSprites();
}