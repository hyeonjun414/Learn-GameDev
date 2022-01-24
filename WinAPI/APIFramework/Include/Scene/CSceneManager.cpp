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
	// ÇöÀç ¾ÀÀ» ¸¸µë.
	CreateScene<InGameScene>(SC_CURRENT);

	return true;
}
