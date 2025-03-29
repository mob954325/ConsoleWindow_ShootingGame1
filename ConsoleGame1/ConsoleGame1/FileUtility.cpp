#define _CRT_SECURE_NO_WARNINGS

#include "FileUtility.h"
#include <iostream>
#include <fstream>
#include <string>
#define MAX_BUFFER_SIZE 1024

namespace FileUtility
{
	char* path = (char*)malloc(MAX_PATH * sizeof(char)); // TODO : 할당해제
	
	void FileUtilityInitialize()
	{
		GetCurrentDirectoryA(MAX_PATH, path);
		strcat_s(path, MAX_PATH, "\\txtImg\\");
		printf("%s", path);
	}

	char* GetTextFromFile(const char* fileName)
	{
		char* maxPath = (char*)malloc(MAX_PATH * sizeof(char));
		strcpy_s(maxPath, MAX_PATH, path);
		strcat_s(maxPath, MAX_PATH, fileName);
		FILE* file = fopen(maxPath, "r");

		int count = 0;
		char** words = (char**)malloc(MAX_BUFFER_SIZE * sizeof(char*));
		char* buffer = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));

		while (fgets(buffer, sizeof(buffer), file))
		{
			int wordLength = strlen(buffer);
			count++;
			printf("%s", buffer);
		}
		
		fclose(file);

		return nullptr;
	}

	void FreeAll()
	{
		free(path);
	}
}