#include "SoundController.h"

namespace SoundController
{
	FMOD::System* system = nullptr;
	FMOD::Sound* sound = nullptr;
	FMOD::Channel* mainMusicChannel = nullptr;
	FMOD::Channel* effectChannel = nullptr;

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

	void Update()
	{
		// 게임 루프나 메인 루프에서 시스템 업데이트 호출
		system->update();

		// 필요 시 채널 상태를 확인하고, 효과음이 끝난 후에 다음 작업을 할 수 있습니다.
		bool isEffectPlaying = false;
		if (effectChannel) {
			effectChannel->isPlaying(&isEffectPlaying);
			if (!isEffectPlaying) {
				//std::cout << "효과음이 종료되었습니다." << std::endl;
			}
		}
	}

	void PlayEffectSound(const char* fileName)
	{
		char maxPath[MAX_PATH];
		strcpy_s(maxPath, MAX_PATH, path);
		strcat_s(maxPath, MAX_PATH, fileName);

		FMOD::Sound* effect = nullptr;
		if (system->createSound(maxPath, FMOD_DEFAULT, nullptr, &effect) != FMOD_OK) {
			std::cerr << "효과음 로드 실패!" << std::endl;
			return;
		}

		// 효과음은 새로운 채널에서 재생 (메인 음악 채널과 분리)
		FMOD::Channel* newEffectChannel = nullptr;
		system->playSound(effect, nullptr, false, &effectChannel);
	}

	void PlayMainMusic(const char* fileName)
	{
		char maxPath[MAX_PATH];
		strcpy_s(maxPath, MAX_PATH, path);
		strcat_s(maxPath, MAX_PATH, fileName);

		FMOD::Sound* music = nullptr;
		if (system->createSound(maxPath, FMOD_LOOP_NORMAL, nullptr, &music) != FMOD_OK) {
			std::cerr << "메인 음악 로드 실패!" << std::endl;
			return;
		}

		// 메인 음악을 재생하고, 채널을 mainMusicChannel에 저장
		system->playSound(music, nullptr, false, &mainMusicChannel);
	}

	void Release()
	{
		sound->release();
		system->close();
		system->release();

		free(path);
	}
}