#include "SpriteData.h"

namespace SpriteData
{
	void LoadTextFile();

	wchar_t** HitEffects[HITEFFECT_COUNT];
	int HitEffectsColumnNum[HITEFFECT_COUNT];

	wchar_t** DeadEffects[DEADEFFECT_COUNT];
	int DeadEffectsColumnNum[DEADEFFECT_COUNT];

	wchar_t** PlayerBoomEffects[PLAYERBOOMEFFECT_COUNT];
	int PlayerBoomEffectsColumnNum[PLAYERBOOMEFFECT_COUNT];

	void Initialize()
	{
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
			for (int j = 0; j < HitEffectsColumnNum[i]; j++)
			{
				free(HitEffects[i][j]);
			}
			free(HitEffects[i]);
		}

		// DeadEffect 
		for (int i = 0; i < DEADEFFECT_COUNT; i++)
		{
			for (int j = 0; j < DeadEffectsColumnNum[i]; j++)
			{
				free(DeadEffects[i][j]);
			}
			free(DeadEffects[i]);
		}

		// PlayerBoomEffect 
		for (int i = 0; i < PLAYERBOOMEFFECT_COUNT; i++)
		{
			for (int j = 0; j < PlayerBoomEffectsColumnNum[i]; j++)
			{
				free(PlayerBoomEffects[i][j]);
			}
			free(PlayerBoomEffects[i]);
		}
	}


	void LoadTextFile()
	{
		// HitEffect - 3프레임
		HitEffectsColumnNum[0] = SpriteFileUtility::GetTextFromWFile("HitEffect\\Hit1.txt", &(HitEffects[0]));
		HitEffectsColumnNum[1] = SpriteFileUtility::GetTextFromWFile("HitEffect\\Hit2.txt", &(HitEffects[1]));
		HitEffectsColumnNum[2] = SpriteFileUtility::GetTextFromWFile("HitEffect\\Hit3.txt", &(HitEffects[2]));

		// DeadEffect - 5프레임
		DeadEffectsColumnNum[0] = SpriteFileUtility::GetTextFromWFile("DeadEffect\\Dead1.txt", &(DeadEffects[0]));
		DeadEffectsColumnNum[1] = SpriteFileUtility::GetTextFromWFile("DeadEffect\\Dead2.txt", &(DeadEffects[1]));
		DeadEffectsColumnNum[2] = SpriteFileUtility::GetTextFromWFile("DeadEffect\\Dead3.txt", &(DeadEffects[2]));
		DeadEffectsColumnNum[3] = SpriteFileUtility::GetTextFromWFile("DeadEffect\\Dead4.txt", &(DeadEffects[3]));
		DeadEffectsColumnNum[4] = SpriteFileUtility::GetTextFromWFile("DeadEffect\\Dead5.txt", &(DeadEffects[4]));

		// PlayerBoomEffect - 5프레임
		PlayerBoomEffectsColumnNum[0] = SpriteFileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom1.txt", &(PlayerBoomEffects[0]));
		PlayerBoomEffectsColumnNum[1] = SpriteFileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom2.txt", &(PlayerBoomEffects[1]));
		PlayerBoomEffectsColumnNum[2] = SpriteFileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom3.txt", &(PlayerBoomEffects[2]));
		PlayerBoomEffectsColumnNum[3] = SpriteFileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom4.txt", &(PlayerBoomEffects[3]));
		PlayerBoomEffectsColumnNum[4] = SpriteFileUtility::GetTextFromWFile("PlayerBoomEffect\\PlayerBoom5.txt", &(PlayerBoomEffects[4]));
	}
}