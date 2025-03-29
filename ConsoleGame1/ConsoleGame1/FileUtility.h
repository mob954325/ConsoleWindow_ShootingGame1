#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace FileUtility
{
	void FileUtilityInitialize();
	int GetTextFromFile(const char* fileName, char*** outBuffer);
	int GetTextFromWFile(const char* fileName, wchar_t*** outBuffer);
	void FreeAll();
}