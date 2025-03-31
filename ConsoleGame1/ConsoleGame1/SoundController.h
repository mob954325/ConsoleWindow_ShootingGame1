#pragma once
#include <iostream>
#include <fmod.hpp>
#include <Windows.h>

#pragma comment(lib, "fmod_vc.lib") // 종속성 링크

namespace SoundController
{
	void Initialize();
	void Update();
	void PlayEffectSound(const char* fileName);
	void PlayMainMusic(const char* fileName);
	void Release();
}