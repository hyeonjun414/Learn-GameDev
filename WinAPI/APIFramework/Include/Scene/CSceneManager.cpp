#include "CSceneManager.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{

}

bool CSceneManager::Init()
{
	// ���� ���� ����.
	CreateScene<InGameScene>(SC_CURRENT);

	return true;
}
