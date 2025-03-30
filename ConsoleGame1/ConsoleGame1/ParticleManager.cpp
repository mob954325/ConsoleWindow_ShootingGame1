#include "ParticleManager.h";

#include "DebugUtility.h"
namespace ParticleManager
{
	int FindEmptyElement();
	void RenderPaticleByType(ScreenElement *obj); // ü������ ��������Ʈ �ε��� ����

	// ��ƼŬ ���� ���� 16��
	ScreenElement particleObjects[MAX_PARTICLE_COUNT];

	void ParticleManagerInitialize()
	{
		// ��� ��� �ʱ�ȭ
		for (int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			particleObjects[i] = SetScreenElementValue({ 0,0 }, 0, { 0,0 }, { 0,0 }, Tag::None);
		}
	}
	
	void ParticleRender()
	{
		for (int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			RenderPaticleByType(&particleObjects[i]);
		}
	}

	void ShowParticleAtPosition(int x, int y, ParticleType type, float frameTime)
	{

	}

	void ShowParticleAtPosition(Vector2 vec, ParticleType type, float frameTime)
	{
		// ����ִ� ��ƼŬ ��ġ ã��
		int index = FindEmptyElement();

		particleObjects[index].position = vec;
		particleObjects[index].additionalElement.particleType = type;
		SetElementTimer(frameTime, &particleObjects[index]);
		if (type == ParticleType::Hit)
		{
			particleObjects[index].health = HITEFFECT_COUNT;
		}
		else if(type == ParticleType::Dead)
		{
			particleObjects[index].health = DEADEFFECT_COUNT;
		}
		else if (type == ParticleType::PlayerBoom)
		{
			particleObjects[index].health = PLAYERBOOMEFFECT_COUNT;
		}
	}

	int FindEmptyElement()
	{
		for (int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			if (particleObjects[i].health <= 0)
			{
				return i;
			}
		}

		return 0; // ����
	}

	// note : �̰� ���� ���� ���� �ٿ��ֱ� �Ѱǵ� ��ġ�� �ð������� �ȵǼ� �ϴ� �ڵ� �̷��� �ۼ��� [0330]
	void RenderPaticleByType(ScreenElement *obj)
	{
		if (obj->additionalElement.particleType == ParticleType::Hit)
		{
			obj->remainTime -= Time::GetDeltaTime();

			// �ε��� ���� -> �ð��� ���������� �ε��� ����
			if (obj->remainTime <= 0)
			{
				obj->health--;
				obj->remainTime = obj->maxTime;
			}

			if (obj->health <= 0) // �ִϸ��̼� �̺�Ʈ ��
			{
				*obj = SetScreenElementValue({ 0,0 }, 0, { 0,0 }, { 0,0 }, Tag::None); // �ش� ��ƼŬ ���� �ʱ�ȭ
			}
			else // �ִϸ��̼� �̺�Ʈ ����
			{
				// ��ƼŬ ���
				int size = 0;
				wchar_t** t = SpriteData::GetHitEffect(obj->health - 1, &size);
				for (int i = 0; i < size; i++)
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[i], FG_BLUE_DARK);
				}
			}
		}
		else if (obj->additionalElement.particleType == ParticleType::Dead)
		{
			obj->remainTime -= Time::GetDeltaTime();

			// �ε��� ���� -> �ð��� ���������� �ε��� ����
			if (obj->remainTime <= 0)
			{
				obj->health--;
				obj->remainTime = obj->maxTime;
			}

			if (obj->health <= 0) // �ִϸ��̼� �̺�Ʈ ��
			{
				*obj = SetScreenElementValue({ 0,0 }, 0, { 0,0 }, { 0,0 }, Tag::None); // �ش� ��ƼŬ ���� �ʱ�ȭ
			}
			else // �ִϸ��̼� �̺�Ʈ ����
			{
				// ��ƼŬ ���
				int size = 0;
				wchar_t** t = SpriteData::GetBoomEffect(obj->health - 1, &size);
				for (int i = 0; i < size; i++)
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[i], FG_WHITE);
				}
			}
		}
		else if (obj->additionalElement.particleType == ParticleType::PlayerBoom)
		{
			obj->remainTime -= Time::GetDeltaTime();

			// �ε��� ���� -> �ð��� ���������� �ε��� ����
			if (obj->remainTime <= 0)
			{
				obj->health--;
				obj->remainTime = obj->maxTime;
			}

			if (obj->health <= 0) // �ִϸ��̼� �̺�Ʈ ��
			{
				*obj = SetScreenElementValue({ 0,0 }, 0, { 0,0 }, { 0,0 }, Tag::None); // �ش� ��ƼŬ ���� �ʱ�ȭ
			}
			else // �ִϸ��̼� �̺�Ʈ ����
			{
				// ��ƼŬ ���
				int size = 0;
				wchar_t** t = SpriteData::GetPlayerBoomEffect(obj->health - 1, &size);
				for (int i = 0; i < size; i++)
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[i], FG_YELLOW_DARK);
				}
			}
		}
	}
}