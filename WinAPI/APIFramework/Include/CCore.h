#pragma once
#include "Game.h"

class CCore
{

private:
	// static 변수는 전역변수와 비슷하게 사용할 수 있다.
	static CCore* m_pInst; // 클래스도 변수 타입일 뿐.
	// 근본적으로 멤버변수이다.
	// 일반 변수는 각 변수마다 메모리는 가진다.
	// 스태틱 멤버변수는 해당 멤버변수를 통해 만들어진 변수의 메모리가 하나만 만들어짐
	// 외부에서 생성자-소멸자에 관여하지 못하게한다.

	CCore();
	~CCore();

	ATOM MyRegisterClass();

	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	RESOLUTION	m_tRS;
	static bool	m_bLoop;


public:
	static CCore* GetInst()
	{
		// 없을때만 새로 만들어줌으로 언제나 하나만 존재하게 만듬.
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst); //메모리 해제
	}

	bool Init(HINSTANCE hInst);
	int Run();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	BOOL Create();




};