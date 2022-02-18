#include "framework.h"
#include "CCore.h"


CCore::CCore()
{
	m_hBMP = 0;
	m_hMemDC = 0;
}
CCore::~CCore()
{
	// 메인 DC 해제
	ReleaseDC(hWnd, m_hDC);

	// 더블버퍼링용 DC와 비트맵을 해제
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBMP);
}

CGameObject g_Player(fPoint(WINSIZEX/2, WINSIZEY/2), fPoint(50,50));

void CCore::update()
{
	// 게임의 정보를 갱신

	// 타임 매니저 업데이트
	CTimeManager::getInst()->update();


	// 해당 키가 눌렸는지 확인한다.
	// 비트별로 다양한 정보를 전달한다. 첫번째는 눌렸는지에 대한 정보
	// 1000 0000 0000 0000

	fPoint pos = g_Player.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) 
	{										
		// 왼쪽
		pos.x -= 100 * DT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{										
		// 오른쪽
		pos.x += 100 * DT;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// 위쪽
		pos.y -= 100 * DT;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		// 아래쪽
		pos.y += 100 * DT;
	}

	g_Player.SetPos(pos);

	// 게임의 정보를 토대로 그려주는 작업
	// FPS 출력
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	TextOutW(m_hDC, WINSIZEX - 60, 10, strFPS, 5);

}


void CCore::render()
{
	// 화면 Clear
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// 움직이는 사각형 출력
	Rectangle(m_hMemDC,
		g_Player.GetPos().x - g_Player.GetScale().x,
		g_Player.GetPos().y - g_Player.GetScale().y,
		g_Player.GetPos().x + g_Player.GetScale().x,
		g_Player.GetPos().y + g_Player.GetScale().y);


	// m_hMemDC에 모아 그린 정보를 m_hDC로 한번에 다시 그림.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::Init()
{
	// Core의 초기화 과정

	// 타임 매니저 초기화
	CTimeManager::getInst()->init();

	m_hDC = GetDC(hWnd);
	
	// 더블 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// 비트맵을 만든 DC에 할당
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBMP);
	DeleteObject(hOldBit);
}
