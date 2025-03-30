#include "ParticleManager.h";

#include "DebugUtility.h"
namespace ParticleManager
{
	int FindEmptyElement();
	void RenderPaticleByType(ScreenElement *obj); // ü������ ��������Ʈ �ε��� ����

	// ��ƼŬ ���� ���� 16��
	ScreenElement particleObjects[MAX_PARTICLE_COUNT];

	void Initialize()
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
		particleObjects[index].health = HITEFFECT_COUNT;
		SetElementTimer(frameTime, &particleObjects[index]);
	}

	int FindEmptyElement()
	{
		for (int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			if (particleObjects[i].remainTime <= 0)
			{
				return i;
			}
		}

		return 0; // ����
	}

	void RenderPaticleByType(ScreenElement *obj)
	{
		if (obj->additionalElement.particleType == ParticleType::Hit)
		{
			obj->remainTime -= Time::GetDeltaTime(); // �ð��� ���� 

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
				for (int i = 0; i < size; i++) // ũ�� �� -> ����Ʈ ũ�⸸ŭ ����
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[obj->health - 1], FG_BLUE_DARK);
				}
			}
		}
	}
}

//// �ؽ�Ʈ ���Ϸ� �ҷ��� ����Ʈ �׽�Ʈ 
//testTimer += Time::GetDeltaTime();
//if (testTimer > maxTime) { testTimer = 0, index++, index %= 3; }

//wchar_t** t = SpriteData::GetHitEffect(index);
//for (int i = 0; i < HITEFFECT_COUNT; i++)
//{
//	ConsoleRenderer::ScreenDrawString(10, 10 + i, t[i], FG_BLUE_DARK);
//}