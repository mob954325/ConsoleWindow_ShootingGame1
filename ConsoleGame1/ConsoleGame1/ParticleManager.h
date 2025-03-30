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

// TODO �ۼ��� ���ʿ��� spriteData ��� �޴� �ҽ����� Ȯ���ϱ�