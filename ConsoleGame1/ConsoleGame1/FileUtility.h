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
	// 내부에서 버퍼 동적 할당함
	int GetTextFromFile(const char* fileName, char*** outBuffer); 
	// 내부에서 버퍼 동적 할당함
	int GetTextFromWFile(const char* fileName, wchar_t*** outBuffer); 
	void FreeAll();
}