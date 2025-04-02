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
	// 피격 스프라이트 데이터 가져오기
	wchar_t** GetHitEffect(int frameValue, int* out_columnNum);
	// 폭탄 스프라이트 데이터 가져오기 ( 사망 모션으로 대체됨 )
	wchar_t** GetBoomEffect(int frameValue, int* out_columnNum);
	// 플레이어 폭탄 스프라이트 가져오기
	wchar_t** GetPlayerBoomEffect(int frameValue, int* out_columnNum);
	// 모든 스프라이트 할당 해제
	void FreeAllSprites();
}