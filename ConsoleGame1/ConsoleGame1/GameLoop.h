#pragma once

enum Scene
{
	MENU = 0,
	PLAY,
	END,
	SCENECOUNT
};

namespace GameLoop
{
	void Initialize();		// 실행 시 초기화
	void Update();			// 매 시간 업데이트할 함수
	void Render();			// 더블 버퍼링 내용 실행

	void SceneChangeByName(Scene sceneName);
	void SceneChangeToNext();
}