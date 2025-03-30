#include "ParticleManager.h";

#include "DebugUtility.h"
namespace ParticleManager
{
	int FindEmptyElement();
	void RenderPaticleByType(ScreenElement *obj); // 체력으로 스프라이트 인덱스 구분

	// 파티클 개수 제한 16개
	ScreenElement particleObjects[MAX_PARTICLE_COUNT];

	void Initialize()
	{
		// 모든 요소 초기화
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
		// 비어있는 파티클 위치 찾기
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

		return 0; // 없음
	}

	void RenderPaticleByType(ScreenElement *obj)
	{
		if (obj->additionalElement.particleType == ParticleType::Hit)
		{
			obj->remainTime -= Time::GetDeltaTime(); // 시간이 안쭘 

			// 인덱스 결정 -> 시간이 끝날때마다 인덱스 감소
			if (obj->remainTime <= 0)
			{
				obj->health--;
				obj->remainTime = obj->maxTime;
			}

			if (obj->health <= 0) // 애니메이션 이벤트 끝
			{
				*obj = SetScreenElementValue({ 0,0 }, 0, { 0,0 }, { 0,0 }, Tag::None); // 해당 파티클 정보 초기화
			}
			else // 애니메이션 이벤트 진행
			{
				// 파티클 출력
				int size = 0;
				wchar_t** t = SpriteData::GetHitEffect(obj->health - 1, &size);
				for (int i = 0; i < size; i++) // 크기 모름 -> 이펙트 크기만큼 실행
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[obj->health - 1], FG_BLUE_DARK);
				}
			}
		}
	}
}

//// 텍스트 파일로 불러온 이펙트 테스트 
//testTimer += Time::GetDeltaTime();
//if (testTimer > maxTime) { testTimer = 0, index++, index %= 3; }

//wchar_t** t = SpriteData::GetHitEffect(index);
//for (int i = 0; i < HITEFFECT_COUNT; i++)
//{
//	ConsoleRenderer::ScreenDrawString(10, 10 + i, t[i], FG_BLUE_DARK);
//}