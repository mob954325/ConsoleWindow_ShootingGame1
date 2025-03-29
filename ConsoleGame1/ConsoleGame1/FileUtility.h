#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

namespace FileUtility
{
	void FileUtilityInitialize();
	char* GetTextFromFile(const char* fileName);
	void FreeAll();
}