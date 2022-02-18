#pragma once
class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;
	
	HBITMAP m_hBMP;
	HDC		m_hMemDC;

public :
	void update(); // 게임 업데이트
	void render(); // 게임 그리기

	void Init();
};

