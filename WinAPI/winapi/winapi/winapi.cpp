// winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "winapi.h"
#include <list>

using namespace std;
#define MAX_LOADSTRING 100
#define PI 3.14159; // 파이를 정의

#pragma region 전역 변수, 함수, 구조체
enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

typedef struct _tagRectangle
{
	float l, t, r, b;
}RECTANGLE, * PRECTANGLE;

// 원형 구조체
typedef struct _tagSphere
{
	float x, y; // 원점
	float r; // 반지름
}SPHERE, * PSPHERE;

// 총알 구조체
typedef struct _tagBullet
{
	SPHERE tSphere;
	float fDist; // 현재 거리
	float fLimitDist; // 제한 거리
	float fAngle; // 발사 각도 , 이부분 추가
}BULLET, * PBULLET;

// 몬스터 구조체
typedef struct _tagMonster {
	RECTANGLE   tRC;
	float       fSpeed; // 몬스터의 이동속도
	float       fTime; // 도달 시간
	float       fLimitTime; // 제한 시간
	int         iDir; // 어느 방향으로 움직이는지. -1~1
}MONSTER, * PMONSTER;

// 몬스터 총알
list<BULLET> g_MonsterBulletList;


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
HDC  g_hDC;
bool g_bLoop = true;


SPHERE g_tPlayer = { 50.f, 50.f, 50.f };
MONSTER     g_tMonster;

POINT g_tGunPos; // 총구의 위치
float g_fGunLength = 70.f; // 총구 길이
float g_fPlayerAngle; // 플레이어의 각도


// 플레이어 총알
list<BULLET> g_PlayerBulletList;

// 시간을 구하기 위한 변수들
LARGE_INTEGER g_tSecond; // 초당 값
LARGE_INTEGER g_tTime;   // 현재 값
float         g_fDeltaTime; // 시간 변화 값

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run();
#pragma endregion

#pragma region wWinMain
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 화면용 DC 생성
	g_hDC = GetDC(g_hWnd);

	// 몬스터 초기화. 800*600 에서 가장 오른쪽에 위치시킨다.
	g_tMonster.tRC.l = 800.f - 100.f;
	g_tMonster.tRC.r = 800.f;
	g_tMonster.tRC.t = 0.f;
	g_tMonster.tRC.b = 100.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.f;
	g_tMonster.fLimitTime = 2.f;
	g_tMonster.iDir = MD_FRONT;


	// 플레이어 총구의 위치를 구해준다.
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

	MSG msg;

	QueryPerformanceFrequency(&g_tSecond); // 초당 실행 빈도수
	QueryPerformanceCounter(&g_tTime); // 이전 프레임의 시간을 얻어옴.

	// 기본 메시지 루프입니다:
	while (g_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 실제 게임 구현 부분
			Run();
		}
	}

	ReleaseDC(g_hWnd, g_hDC);

	return (int)msg.wParam;
}
#pragma endregion

#pragma region MyRegisterClass
//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINAPI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}
#pragma endregion

#pragma region InitInstance

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd; // 초기화 부분에 윈도우 핸들러를 넣어준다.

	// 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해준다.
	RECT rc = { 0,0,800,600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// 위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야한다.
	// HWND_TOPMOST : 창을 띄울때 최상단에 띄우는 옵션이다.
	// SWP_NOMOVE : 해당 위치에서 움직이지 못하게 하는 옵션.
	// SWP_NOZORDER : ZORDER에 관계없이 창을 출력한다.
	SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

#pragma endregion

#pragma region WndProc

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		g_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

#pragma endregion

#pragma region About


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
#pragma endregion

#pragma region 구현 부분

void Run()
{

#pragma region 시간 연산
	// DeltaTime을 구해준다.
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime); // 현재 프레임의 틱을 얻어온다.

	// DeltaTime = (현재 틱 - 이전 틱) / 초당 틱
	// ex) 1500000 - 1450000 / 1000000 = 1/20
	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / (float)g_tSecond.QuadPart;

	g_tTime = tTime;



	static float fTimeScale = 1.f;

	// F1 키 : 속도 줄어듬.
	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		fTimeScale -= g_fDeltaTime;

		if (fTimeScale < 0.f) fTimeScale = 0.f;
	}

	// F2 키 : 속도 늘어남.
	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		fTimeScale += g_fDeltaTime;

		if (fTimeScale > 1.f) fTimeScale = 1.f;
	}
#pragma endregion

#pragma region 키보드 입력 기반 플레이어 이동

	// Run함수의 인풋 이벤트 부분
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// 마우스 위치를 얻어온다.
		POINT ptMouse;

		// 마우스 위치를 스크린 좌표 기준으로 받아옴.
		GetCursorPos(&ptMouse);
		// 스크린 좌표를 클라이언트 좌표로 변환함.
		ScreenToClient(g_hWnd, &ptMouse);

	}


	// 플레이어 초당 이동속도 : 300
	float fSpeed = 300 * g_fDeltaTime * fTimeScale;

	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_fPlayerAngle += fTimeScale * g_fDeltaTime * PI;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_fPlayerAngle -= fTimeScale * g_fDeltaTime * PI;
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		g_tPlayer.x += fSpeed * cosf(g_fPlayerAngle);
		g_tPlayer.y += fSpeed * sinf(g_fPlayerAngle);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		g_tPlayer.x -= fSpeed * cosf(g_fPlayerAngle);
		g_tPlayer.y -= fSpeed * sinf(g_fPlayerAngle);
	}

	// 총구 위치를 구한다.
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;

	// 1번을 누르면 3발씩 발사
	if (GetAsyncKeyState('1') & 0x8000)
	{
		float fAngle = g_fPlayerAngle - 3.14f / 12.f; // 15도 빼줌.

		for (int i = 0; i < 3; ++i)
		{
			BULLET tBullet;

			// 총구의 끝에 총알을 위치시킨다.
			tBullet.tSphere.x = g_tGunPos.x + cosf(fAngle) * 25.f;
			tBullet.tSphere.y = g_tGunPos.y + sinf(fAngle) * 25.f;

			tBullet.tSphere.r = 25.f;
			tBullet.fDist = 0.f; // 현재 거리는 0;
			tBullet.fLimitDist = 400.f; // 최대 거리는 400;
			tBullet.fAngle = fAngle; // 플레이어의 현재 각도

			g_PlayerBulletList.push_back(tBullet);

			fAngle += 3.14f / 12.f;
		}
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		float fAngle = 0.f;

		for (int i = 0; i < 36; ++i)
		{
			BULLET tBullet;

			// 총구의 끝에 총알을 위치시킨다.
			tBullet.tSphere.x = g_tGunPos.x + cosf(fAngle) * 25.f;
			tBullet.tSphere.y = g_tGunPos.y + sinf(fAngle) * 25.f;

			tBullet.tSphere.r = 25.f;
			tBullet.fDist = 0.f; // 현재 거리는 0;
			tBullet.fLimitDist = 400.f; // 최대 거리는 400;
			tBullet.fAngle = fAngle; // 플레이어의 현재 각도

			g_PlayerBulletList.push_back(tBullet);

			fAngle += 3.14 / 18.f;
		}
	}

#pragma endregion

#pragma region 플레이어 및 몬스터 총알 발사

	// 총알 속도
	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	// 총알 생성 부
// 총알 발사 버튼
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		BULLET tBullet;

		// 총구의 끝에 총알을 위치시킨다.
		tBullet.tSphere.x = g_tGunPos.x + cosf(g_fPlayerAngle) * 25.f;
		tBullet.tSphere.y = g_tGunPos.y + sinf(g_fPlayerAngle) * 25.f;

		tBullet.tSphere.r = 25.f;
		tBullet.fDist = 0.f; // 현재 거리는 0;
		tBullet.fLimitDist = 400.f; // 최대 거리는 400;
		tBullet.fAngle = g_fPlayerAngle; // 플레이어의 현재 각도

		g_PlayerBulletList.push_back(tBullet);
	}

	// 몬스터 총알 발사 로직
	g_tMonster.fTime += g_fDeltaTime; // 시간누적

	// 누적된 시간이 제한시간을 초과하면
	if (g_tMonster.fTime >= g_tMonster.fLimitTime)
	{
		// 제한시간 만큼 다시 빼줌.
		g_tMonster.fTime -= g_tMonster.fLimitTime;

		// 총알은 몬스터의 왼쪽에 위치
		BULLET tBullet;

		tBullet.tSphere.x = g_tMonster.tRC.l - 50.f;
		tBullet.tSphere.y = g_tMonster.tRC.t + 50.f;
		tBullet.tSphere.r = 25.f;
		tBullet.fDist = 0.f; // 현재 거리는 0;
		tBullet.fLimitDist = 800.f; // 최대 거리는 400;

		g_MonsterBulletList.push_back(tBullet);
	}
#pragma endregion

#pragma region 총알 이동 및 충돌 처리
	// 총알 리스트 반복자 : 리스트의 크기가 변동될때 사용된다.
	list<BULLET>::iterator iter;
	list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();


	// 플레이어 총알 이동
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;) //++iter 제거
	{
		(*iter).tSphere.x += cosf((*iter).fAngle) * fSpeed;
		(*iter).tSphere.y += sinf((*iter).fAngle) * fSpeed;
		(*iter).fDist += fSpeed;

		// 현재 거리가 최대 거리를 넘어가면 
		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			// erase하면 다음 iterator를 가져옴.
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		// 화면 영역을 벗어나면
		else if (((*iter).tSphere.x - (*iter).tSphere.r) > 800)//rcWindow.right)
		{
			// erase하면 다음 iterator를 가져옴.
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else
			++iter; //삭제가 안되면 정상적으로 반복자를 올려줌.
	}

	// 몬스터 총알 이동
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd;) //++iter 제거
	{
		(*iter).tSphere.x -= fSpeed;
		(*iter).fDist += fSpeed;

		// 현재 거리가 최대 거리를 넘어가면 
		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			// erase하면 다음 iterator를 가져옴.
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}

		// 화면 영역을 벗어나면
		else if (((*iter).tSphere.x + (*iter).tSphere.r) <= 0)
		{
			// erase하면 다음 iterator를 가져옴.
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		else
			++iter; //삭제가 안되면 정상적으로 반복자를 올려줌.
	}
#pragma endregion

#pragma region 몬스터 이동 로직
	// 몬스터 이동. iDir을 통해 이동하는 방향을 구해줌.
	g_tMonster.tRC.t += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
	g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

	// 위아래 경계선에 닿을때마다 방향을 바꿔준다.
	if (g_tMonster.tRC.b >= 600)
	{
		g_tMonster.iDir = MD_BACK;
		g_tMonster.tRC.b = 600;
		g_tMonster.tRC.t = 500;
	}
	else if (g_tMonster.tRC.t <= 0)
	{
		g_tMonster.iDir = MD_FRONT;
		g_tMonster.tRC.b = 100;
		g_tMonster.tRC.t = 0;
	}
#pragma endregion

#pragma region 렌더 부분
	// 총알 출력
	for (iter = g_PlayerBulletList.begin(); iter != g_PlayerBulletList.end(); ++iter)
	{
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r,
			(*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r,
			(*iter).tSphere.y + (*iter).tSphere.r);
	}
	for (iter = g_MonsterBulletList.begin(); iter != g_MonsterBulletList.end(); ++iter)
	{
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r,
			(*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r,
			(*iter).tSphere.y + (*iter).tSphere.r);
	}

	// 플레이어 원형 출력
	Ellipse(g_hDC, g_tPlayer.x - g_tPlayer.r,
		g_tPlayer.y - g_tPlayer.r,
		g_tPlayer.x + g_tPlayer.r,
		g_tPlayer.y + g_tPlayer.r);
	// 총구 출력
	MoveToEx(g_hDC, g_tPlayer.x, g_tPlayer.y, NULL);
	LineTo(g_hDC, g_tGunPos.x, g_tGunPos.y);


	// 몬스터 사각형 출력
	Ellipse(g_hDC, g_tMonster.tRC.l, g_tMonster.tRC.t, g_tMonster.tRC.r, g_tMonster.tRC.b);
#pragma endregion

}

#pragma endregion


