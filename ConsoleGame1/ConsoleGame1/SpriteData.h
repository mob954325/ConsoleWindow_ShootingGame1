#pragma once
#include "FileUtility.h"

#include "stdio.h"
#include "stdlib.h"

#define HITEFFECT_COUNT 3

namespace SpriteData
{
	void Initialize();
	wchar_t** GetHitEffect(int frameValue);
	void FreeAllSprites();
}