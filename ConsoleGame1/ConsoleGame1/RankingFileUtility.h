#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define RANKER_COUNT 3

#include <Windows.h>
#include <iostream>

namespace RankingFileUtility
{
	void Initialize();
	int UpdateScore(int score, const char* name);
	int CheckScore(int score);
	int GetHighScore(int rank, char** buffer);
	void WriteScore();
	void Release();
}