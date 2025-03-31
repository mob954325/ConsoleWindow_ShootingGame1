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

		return 0; // 없음
	}

	// note : 이거 같은 내용 복사 붙여넣기 한건데 합치면 시간관리가 안되서 일단 코드 이렇게 작성함 [0330]
	void RenderPaticleByType(ScreenElement *obj)
	{
		if (obj->additionalElement.particleType == ParticleType::Hit)
		{
			obj->remainTime -= Time::GetDeltaTime();

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
				for (int i = 0; i < size; i++)
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[i], FG_BLUE_DARK);
				}
			}
		}
		else if (obj->additionalElement.particleType == ParticleType::Dead)
		{
			obj->remainTime -= Time::GetDeltaTime();

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
				wchar_t** t = SpriteData::GetPlayerBoomEffect(obj->health - 1, &size);
				for (int i = 0; i < size; i++)
				{
					ConsoleRenderer::ScreenDrawString(obj->position.x, obj->position.y + (i - 1), t[i], FG_YELLOW_DARK);
				}
			}
		}
	}
}