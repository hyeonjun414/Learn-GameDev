#pragma once
#include "Game.h"

class CCore
{

private:
	// static ������ ���������� ����ϰ� ����� �� �ִ�.
	static CCore* m_pInst; // Ŭ������ ���� Ÿ���� ��.
	// �ٺ������� ��������̴�.
	// �Ϲ� ������ �� �������� �޸𸮴� ������.
	// ����ƽ ��������� �ش� ��������� ���� ������� ������ �޸𸮰� �ϳ��� �������
	// �ܺο��� ������-�Ҹ��ڿ� �������� ���ϰ��Ѵ�.

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
		// �������� ���� ����������� ������ �ϳ��� �����ϰ� ����.
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst); //�޸� ����
	}

	bool Init(HINSTANCE hInst);
	int Run();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	BOOL Create();




};