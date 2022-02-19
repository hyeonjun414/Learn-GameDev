#include "framework.h"
#include "CCore.h"


CCore::CCore()
{
	m_hBMP = 0;
	m_hMemDC = 0;
}
CCore::~CCore()
{
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

	// ������۸��� DC�� ��Ʈ���� ����
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBMP);
}

CGameObject g_Player(fPoint(WINSIZEX/2, WINSIZEY/2), fPoint(50,50));

void CCore::update()
{
	// ������ ������ ����

	// Ÿ�� �Ŵ��� ������Ʈ
	CTimeManager::getInst()->update();


	// �ش� Ű�� ���ȴ��� Ȯ���Ѵ�.
	// ��Ʈ���� �پ��� ������ �����Ѵ�. ù��°�� ���ȴ����� ���� ����
	// 1000 0000 0000 0000

	fPoint pos = g_Player.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) 
	{										
		// ����
		pos.x -= 100 * DT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{										
		// ������
		pos.x += 100 * DT;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// ����
		pos.y -= 100 * DT;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		// �Ʒ���
		pos.y += 100 * DT;
	}

	g_Player.SetPos(pos);

	// ������ ������ ���� �׷��ִ� �۾�
	// FPS ���
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	TextOutW(m_hDC, WINSIZEX - 60, 10, strFPS, 5);

}


void CCore::render()
{
	// ȭ�� Clear
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// �����̴� �簢�� ���
	Rectangle(m_hMemDC,
		g_Player.GetPos().x - g_Player.GetScale().x,
		g_Player.GetPos().y - g_Player.GetScale().y,
		g_Player.GetPos().x + g_Player.GetScale().x,
		g_Player.GetPos().y + g_Player.GetScale().y);


	// m_hMemDC�� ��� �׸� ������ m_hDC�� �ѹ��� �ٽ� �׸�.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::Init()
{
	// Core�� �ʱ�ȭ ����

	// Ÿ�� �Ŵ��� �ʱ�ȭ
	CTimeManager::getInst()->init();

	m_hDC = GetDC(hWnd);
	
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// ��Ʈ���� ���� DC�� �Ҵ�
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBMP);
	DeleteObject(hOldBit);
}
