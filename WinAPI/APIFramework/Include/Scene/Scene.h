#pragma once

#include "../Game.h"

class Scene
{
protected:
	friend class SceneManager;

protected:
	Scene();
	virtual ~Scene(); // �����Լ��� ������༭ �߻� Ŭ������ ����Ѵ�.

public:
	virtual bool Init();
};