#include "framework.h"
#include "CKeyManager.h"

// 가상 키값을 알아야한다. -> 설정한 키 인덱스와 순서를 일치.
int g_arrVK[(int)KEY::SIZE] = 
{
	VK_UP,		//	UP,
	VK_DOWN,	//	DOWN,
	VK_LEFT,	//	LEFT,
	VK_RIGHT,	//	RIGHT,
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','Z','X','C','V','B',
	VK_MENU,	//	ALT,
	VK_CONTROL,	//	LSHIFT,
	VK_LSHIFT,	//	CTRL,
	VK_SPACE,	//	SPACE,
	VK_RETURN,	//	ENTER,
	VK_ESCAPE,	//	ESC,

	//	LAST
};


CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::Init()
{
	// 키 매니저 초기화
	
	// 우선 벡터에 키 정보를 초기화 해줘야한다.
	// LAST가 KEY INDEX의 끝에 있기 때문에 반복해야하는 횟수로 사용할 수 있다. ==> size()
	for (int i = 0; i < (int)KEY::SIZE; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyManager::Update()
{
	// 현재 선택된 윈도우가 게임 윈도우인가를 확인한다.
	HWND curWnd = GetFocus();

	// 게임 윈도우가 선택되지 않은 상태를 경우
	if (hWnd != curWnd)
	{
		// 전체 키를 안눌린 상태로 만들어준다.
		for (int i = 0; i < (int)KEY::SIZE; i++)
		{
			// 안눌린 상태로 만들때 이전에 눌린 키에 대한 처리를 진행한다.
			if (m_vecKey[i].bPrevPush)
				// 이전에 눌려있었다면 AWAY로
				m_vecKey[i].eState = KEY_STATE::AWAY;

			else
				// 안눌려있었다면 아예 눌린정보가 없게
				m_vecKey[i].eState = KEY_STATE::NONE;

			m_vecKey[i].bPrevPush = false;
		}
		// AWAY로 상태가 변환된 키는 다음 업데이트때 NONE으로 변환된다.

		return;
	}

	// 게임 윈도우가 포커싱 되어있으면

	// 모든 키에 대해 확인을 진행한다.
	for (int i = 0; i < (int)KEY::SIZE; i++)
	{
		// 키가 눌렸는지 가상키 배열을 돌면서 확인
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			// 이전에도 눌려있었다면 해당 키의 상태를 
			if (m_vecKey[i].bPrevPush)
			{
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			// 안눌려 있었다면
			else
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}
			m_vecKey[i].bPrevPush = true;
		}
		// 키가 안눌렸다
		else
		{
			// 이전에는 눌려있었다면
			if (m_vecKey[i].bPrevPush)
				// 이전에 눌려있었다면 AWAY로
				m_vecKey[i].eState = KEY_STATE::AWAY;

			else
				// 안눌려있었다면 아예 눌린정보가 없게
				m_vecKey[i].eState = KEY_STATE::NONE;

			m_vecKey[i].bPrevPush = false;

		}
	}
}
