#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>

namespace RankingFileUtility
{
	void Initialize();
	void ChceckScore(int score, const char* name);
	int GetHighScore(int rank, char** buffer);
	void WriteScore();
	void Release();
}