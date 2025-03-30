#pragma once
#include "ConsoleRenderer.h"
#include "Vector.h"
#include "SpriteData.h"
#include "Time.h"
#include "DataTypes.h"

#define MAX_PARTICLE_COUNT 16

namespace ParticleManager
{
	void ParticleManagerInitialize();
	void ParticleRender();
	void ShowParticleAtPosition(int x, int y, ParticleType type, float frameTime);
	void ShowParticleAtPosition(Vector2 vec, ParticleType type, float frameTime);
}

// TODO 작성후 불필요한 spriteData 헤더 받는 소스파일 확인하기