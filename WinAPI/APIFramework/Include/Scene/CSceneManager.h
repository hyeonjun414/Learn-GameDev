#pragma once

#include "../Game.h"
#include "Scene.h"
#include "InGameScene.h"
class CSceneManager
{
public :
	bool Init();
	DECLARE_SINGLE(CSceneManager);
private:
	class Scene* m_pScene; // 현재 씬을 가리킴.
	class Scene* m_pNextScene; // 장면 교체를 할때 사용.

public:

	template <typename T>
	T* CreateScene(SCENE_CREATE sc)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (sc)
		{
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}
		return pScene;
	}
};