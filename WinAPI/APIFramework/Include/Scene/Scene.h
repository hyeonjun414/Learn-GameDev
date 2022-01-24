#pragma once

#include "../Game.h"

class Scene
{
protected:
	friend class SceneManager;

protected:
	Scene();
	virtual ~Scene(); // 가상함수로 만들어줘서 추상 클래스로 사용한다.

public:
	virtual bool Init();
};