#include "SpriteData.h"

namespace SpriteData
{
	void LoadTextFile();
	void ContainersAllocate();

	wchar_t** HitEffects[HITEFFECT_COUNT];

	void Initialize()
	{
		ContainersAllocate();
		LoadTextFile();
	}
	
	wchar_t** GetHitEffect(int frameValue)
	{
		return HitEffects[frameValue];
	}

	void FreeAllSprites()
	{
		// HitEffects
		for (int i = 0; i < HITEFFECT_COUNT; i++)
		{
			for (int j = 0; j < HITEFFECT_COUNT; j++)
			{
				free(HitEffects[i][j]);
			}
			free(HitEffects[i]);
		}
	}


	void LoadTextFile()
	{
		// HitEffect - 3ÇÁ·¹ÀÓ
		FileUtility::GetTextFromWFile("HitEffect\\Hit1.txt", &(HitEffects[0]));
		FileUtility::GetTextFromWFile("HitEffect\\Hit2.txt", &(HitEffects[1]));
		FileUtility::GetTextFromWFile("HitEffect\\Hit3.txt", &(HitEffects[2]));
	}

	void ContainersAllocate()
	{
		// HitEffects
		for (int i = 0; i < HITEFFECT_COUNT; i++)
		{
			HitEffects[i] = (wchar_t**)malloc(HITEFFECT_COUNT * sizeof(char*));
		}

		int a = 0;
	}
}