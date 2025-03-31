#include "RankingFileUtility.h"

#define MAX_BUFFER_SIZE 1024
#define RANKER_COUNT 3

namespace RankingFileUtility
{
	char* path = (char*)malloc(MAX_PATH * sizeof(char));

	char** rankerName;
	int* rankerScore;

	void Initialize()
	{
		GetCurrentDirectoryA(MAX_PATH, path);
		strcat_s(path, MAX_PATH, "\\Ranking\\Ranking.txt");

		// TODO 할당해제하기
		rankerName = (char**)malloc(RANKER_COUNT * sizeof(char*));
		rankerScore = (int*)malloc(RANKER_COUNT * sizeof(int));

		// 랭커 파일 읽기
		FILE* file = fopen(path, "r");
		char* buffer = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
		int rankCount = 0;
		while (fgets(buffer, sizeof(buffer), file))
		{
			// 이름
			int wordLength = strlen(buffer);
			rankerName[rankCount] = (char*)malloc((wordLength + 1)* sizeof(char));
			strcpy(rankerName[rankCount], buffer);

			// 숫자
			fgets(buffer, sizeof(buffer), file);
			int score = atoi(buffer);
			rankerScore[rankCount++] = score;
		}

		free(buffer);
	}

	void Release()
	{
	/*	for (int i = 0; i < RANKER_COUNT; i++)
		{
			free(rankerName[i]);
		}*/

		free(rankerName);
		free(rankerScore);
		free(path);
	}
	
	void ChceckScore(int score, const char* name)
	{
		if (name == nullptr) name = "AAA";

		int n = strlen(name);
		char* buffer = (char*)malloc((n + 1) * sizeof(char));
		strcpy(buffer, name);
		for (int i = 0; i < RANKER_COUNT; i++)
		{
			if (score > rankerScore[i])
			{
				strcpy(rankerName[i], buffer);
				rankerScore[i] = score;
				break;
			}
		}

		free(buffer);
	}
	
	int GetHighScore(int rank, char** buffer)
	{
		if (rank <= 0 && rank > RANKER_COUNT) return 1;

		if (buffer != nullptr)
		{
			*buffer = rankerName[rank - 1];
		}

		return rankerScore[rank - 1];
	}

	void WriteScore()
	{
		GetCurrentDirectoryA(MAX_PATH, path);
		strcat_s(path, MAX_PATH, "\\Ranking\\Ranking.txt");

		char scoreBuffer[100];

		// 랭커 파일 읽기
		FILE* file = fopen(path, "w");
		for (int i = 0; i < RANKER_COUNT; i++)
		{
			fprintf(file, "%s\n",rankerName[i]);

			_itoa_s(rankerScore[i], scoreBuffer, 10);
			fprintf(file, "%d", scoreBuffer);
		}
	}
}

