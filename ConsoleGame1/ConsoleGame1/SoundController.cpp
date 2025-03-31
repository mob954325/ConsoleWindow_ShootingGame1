#include "SoundController.h"

namespace SoundController
{
	FMOD::System* system = nullptr;
	FMOD::Sound* sound = nullptr;
	FMOD::Channel* channel = nullptr;

	char* path = (char*)malloc(MAX_PATH * sizeof(char));
	void Initialize()
	{
		GetCurrentDirectoryA(MAX_PATH, path);
		strcat_s(path, MAX_PATH, "\\Sound\\");

		// FMOD 시스템 초기화
		if (FMOD::System_Create(&system) != FMOD_OK) {
			std::cerr << "FMOD 시스템 생성 실패!" << std::endl;
			return;
		}
		system->init(512, FMOD_INIT_NORMAL, nullptr);
	}

	void SoundPlay(const char* fileName)
	{
		char* maxPath = (char*)malloc(MAX_PATH * sizeof(char));
		strcpy_s(maxPath, MAX_PATH, path);
		strcat_s(maxPath, MAX_PATH, fileName);

		// 오디오 파일 로드
		if (system->createSound(maxPath, FMOD_DEFAULT, nullptr, &sound) != FMOD_OK) {
			std::cerr << "사운드 로드 실패!" << std::endl;
			return;
		}

		// 오디오 재생
		system->playSound(sound, nullptr, false, &channel);
	}

	void Release()
	{
		sound->release();
		system->close();
		system->release();
	}
}