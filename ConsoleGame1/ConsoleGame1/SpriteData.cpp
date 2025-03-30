#include "SpriteData.h"

namespace SpriteData
{
	void LoadTextFile();
	void ContainersAllocate();

	wchar_t** HitEffects[HITEFFECT_COUNT];
	int HitEffectsColumnNum[HITEFFECT_COUNT];

	wchar_t** DeadEffects[DEADEFFECT_COUNT];
	int DeadEffectsColumnNum[DEADEFFECT_COUNT];

	wchar_t** PlayerBoomEffects[PLAYERBOOMEFFECT_COUNT];
	int PlayerBoomEffectsColumnNum[PLAYERBOOMEFFECT_COUNT];

	void Initialize()
	{
		ContainersAllocate();
		LoadTextFile();
	}
	
	wchar_t** GetHitEffect(int frameValue, int *out_columnNum)
	{
		*out_columnNum = HitEffectsColumnNum[frameValue];
		return HitEffects[frameValue];
	}

	wchar_t** GetBoomEffect(int frameValue, int* out_columnNum)
	{
		*out_columnNum = DeadEffectsColumnNum[frameValue];
		return DeadEffects[frameValue];
	}

	wchar_t** GetPlayerBoomEffect(int frameValue, int* out_columnNum)
	{
		*out_columnNum = PlayerBoomEffectsColumnNum[frameValue];
		return PlayerBoomEffects[frameValue];
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

		// DeadEffect 
		for (int i = 0; i < DEADEFFECT_COUNT; i++)
		{
			for (int j = 0; j < DEADEFFECT_COUNT; j++)
			{
				free(DeadEffects[i][j]);
			}
			free(DeadEffects[i]);
		}

		// PlayerBoomEffect 
		for (int i = 0; i < PLAYERBOOMEFFECT_COUNT; i++)
		{
			for (int j = 0; j < PLAYERBOOMEFFECT_COUNT; j++)
			{
				free(PlayerBoomEffects[i][j]);
			}
			free(PlayerBoomEffects[i]);
		}
	}


	void LoadTextFile()
	{
		// HitEffect - 3프레임
		HitEffectsColumnNum[0] = FileUtility::GetTextFromWFile("HitEffect\\Hit1.txt", &(HitEffects[0]));
		HitEffectsColumnNum[1] = FileUtility::GetTextFromWFile("HitEffect\\Hit2.txt", &(HitEffects[1]));
		HitEffectsColumnNum[2] = FileUtility::GetTextFromWFile("HitEffect\\Hit3.txt", &(HitEffects[2]));

		// DeadEffect - 5프레임
		DeadEffectsColumnNum[0] = FileUtility::GetTextFromWFile("DeadEffect\\Dead1.txt", &(DeadEffects[0]));
		DeadEffectsColumnNum[1] = FileUtility::GetTextFromWFile("DeadEffect\\Dead2.txt", &(DeadEffects[1]));
		DeadEffectsColumnNum[2] = FileUtility::GetTextFromWFile("DeadEffect\\Dead3.txt", &(DeadEffects[2]));
		DeadEffectsColumnNum[3] = FileUtility::GetTextFromWFile("DeadEffect\\Dead4.txt", &(DeadEffects[3]));
		DeadEffectsColumnNum[4] = FileUtility::GetTextFromWFile("DeadEffect\\Dead5.txt", &(DeadEffects[4]));

		// PlayerBoomEffect - 5프레임
		PlayerBoomEffectsColumnNum[0] = FileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom1.txt", &(PlayerBoomEffects[0]));
		PlayerBoomEffectsColumnNum[1] = FileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom2.txt", &(PlayerBoomEffects[1]));
		PlayerBoomEffectsColumnNum[2] = FileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom3.txt", &(PlayerBoomEffects[2]));
		PlayerBoomEffectsColumnNum[3] = FileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom4.txt", &(PlayerBoomEffects[3]));
		PlayerBoomEffectsColumnNum[4] = FileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom5.txt", &(PlayerBoomEffects[4]));
	}

	void ContainersAllocate()
	{
		// HitEffects
		for (int i = 0; i < HITEFFECT_COUNT; i++)
		{
			HitEffects[i] = (wchar_t**)malloc(HITEFFECT_COUNT * sizeof(char*));
		}

		// DeadEffect
		for (int i = 0; i < DEADEFFECT_COUNT; i++)
		{
			DeadEffects[i] = (wchar_t**)malloc(DEADEFFECT_COUNT * sizeof(char*));
		}

		// PlayerBoomEffect
		for (int i = 0; i < PLAYERBOOMEFFECT_COUNT; i++)
		{
			PlayerBoomEffects[i] = (wchar_t**)malloc(PLAYERBOOMEFFECT_COUNT * sizeof(char*));
		}
	}
}