#include "RankingFileUtility.h"

#define MAX_BUFFER_SIZE 1024

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
		int loopCount = 0;
		while (fgets(buffer, MAX_BUFFER_SIZE, file))
		{
			// 이름
			if (loopCount == 0)
			{
				int wordLength = (int)strlen(buffer);
				buffer[wordLength - 1] = '\0';
				wordLength--;

				rankerName[rankCount] = (char*)malloc((wordLength + 1) * sizeof(char));
				strcpy(rankerName[rankCount], buffer);
			}
			else if (loopCount == 1)
			{
				// 숫자
				int wordLength = (int)strlen(buffer);
				wordLength = (int)strlen(buffer);
				buffer[wordLength - 1] = '\0';
				wordLength--;

				int score = atoi(buffer);
				rankerScore[rankCount++] = score;

				loopCount = 0;
				continue;
			}

			loopCount++;
		}

		free(buffer);
	}

	void Release()
	{
		for (int i = 0; i < RANKER_COUNT; i++)
		{
			//free(rankerName[i]);
		}

		free(rankerName);
		free(rankerScore);
		free(path);
	}
	
	int UpdateScore(int score, const char* name)
	{
		if (name == nullptr) name = "AAA";
		
		int n = (int)strlen(name);
		char* buffer = (char*)malloc((n + 1) * sizeof(char));
		if(name) strcpy(buffer, name);
		for (int i = 0; i < RANKER_COUNT; i++)
		{
			if (score > rankerScore[i])
			{
				int prevScore = rankerScore[i];
				char* prevName = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
				if(rankerName[i]) strcpy(prevName, rankerName[i]);

				for (int j = i + 1; j < RANKER_COUNT; j++)
				{
					if (prevScore > rankerScore[j])
					{
						int temp = rankerScore[j];
						char* tempStr = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
						if(rankerName[j]) strcpy(tempStr, rankerName[j]);

						rankerScore[j] = prevScore;
						if(prevName) strcpy(rankerName[j], prevName);

						prevScore = temp;
						if(tempStr) strcpy(prevName, tempStr);
						free(tempStr);
						break;
					}
				}

				for (int j = i + 1; j < RANKER_COUNT; j++)
				{
					if (prevScore > rankerScore[j])
					{
						rankerScore[j] = prevScore;
						if(prevName) strcpy(rankerName[j], prevName);
						break;
					}
				}

				strcpy(rankerName[i], buffer);
				rankerScore[i] = score;
				free(prevName);
				return 1;
			}
		}

		free(buffer);

		return 0;
	}

	int CheckScore(int score)
	{
		for (int i = 0; i < RANKER_COUNT; i++)
		{
			if (score > rankerScore[i])
			{
				return 1;
			}
		}

		return 0;
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
			fprintf(file, "%s\n", scoreBuffer);
		}
	}
}

