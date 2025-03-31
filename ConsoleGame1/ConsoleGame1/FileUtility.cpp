#include "FileUtility.h"

#define MAX_BUFFER_SIZE 1024

namespace FileUtility
{
	char* path = (char*)malloc(MAX_PATH * sizeof(char));
	wchar_t* wPath = (wchar_t*)malloc(MAX_PATH * sizeof(wchar_t));
	
	void FileUtilityInitialize()
	{
		GetCurrentDirectoryA(MAX_PATH, path);
		GetCurrentDirectoryW(MAX_PATH, wPath);
		strcat_s(path, MAX_PATH, "\\txtImg\\");
		wcscat_s(wPath, MAX_PATH, L"\\txtImg\\");
	}

	int GetTextFromFile(const char* fileName, char*** outBuffer)
	{
		char* maxPath = (char*)malloc(MAX_PATH * sizeof(char));
		strcpy_s(maxPath, MAX_PATH, path);
		strcat_s(maxPath, MAX_PATH, fileName);
		FILE* file = fopen(maxPath, "r");

		int rowCount = 0;
		char** words = (char**)malloc(MAX_BUFFER_SIZE * sizeof(char*));
		char* buffer = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));

		while (fgets(buffer, sizeof(buffer), file))
		{
			int wordLength = strlen(buffer);
			words[rowCount] = (char*)malloc(wordLength * sizeof(char*));
			strcpy(words[rowCount++], buffer);
		}

		*outBuffer = (char**)malloc(rowCount * sizeof(char*));

		int colCount = 0;
		for (int i = 0; i < rowCount; i++)
		{
			int len = strlen(words[i]);
			(*outBuffer)[i] = (char*)malloc((len + 1) * sizeof(char));
			strcpy((*outBuffer)[i], words[i]);
			free(words[i]);
		}

		fclose(file);
		free(maxPath);
		free(words);

		return rowCount;
	}

	int GetTextFromWFile(const char* fileName, wchar_t*** outBuffer)
	{
		char* maxPath = (char*)malloc(MAX_PATH * sizeof(char));
		strcpy_s(maxPath, MAX_PATH, path);
		strcat_s(maxPath, MAX_PATH, fileName);

		// 파일 열기
		FILE* file = fopen(maxPath, "r");
		if (!file) // 파일 열기 실패
		{ 
			free(maxPath);
			return NULL;
		}

		int rowCount = 0;
		wchar_t** words = (wchar_t**)malloc(MAX_BUFFER_SIZE * sizeof(wchar_t*));
		char buffer[MAX_BUFFER_SIZE]; // char buffer로 먼저 읽어오기
		wchar_t wbuffer[MAX_BUFFER_SIZE]; // wchar_t로 변환할 버퍼

		while (fgets(buffer, MAX_BUFFER_SIZE, file))
		{
			int len = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wbuffer, MAX_BUFFER_SIZE); // char -> wchar_t로 
			words[rowCount] = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));

			if (words[rowCount] == NULL) // 메모리 할당 실패
			{
				fclose(file);
				free(maxPath);
				for (int i = 0; i < rowCount; i++)
				{
					free(words[i]);
				}
				free(words);
				return NULL;
			}

			// 마지막 줄바꿈 문자 제거
			for (int i = 0; i < len; i++)
			{
				if (wbuffer[i] == '\n')
				{
					wbuffer[i] = L'\0';
					break;
				}
			}

			wcscpy(words[rowCount++], wbuffer);
		}

		*outBuffer = (wchar_t**)malloc(rowCount * sizeof(wchar_t*));

		int colCount = 0;
		for (int i = 0; i < rowCount; i++)
		{
			int len = wcslen(words[i]);
			(*outBuffer)[i] = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
			wcscpy((*outBuffer)[i], words[i]);
			free(words[i]);
		}
		
		fclose(file);
		free(maxPath);
		free(words);

		return rowCount;
	}

	void FreeAll()
	{
		free(path);
		free(wPath);
	}
}