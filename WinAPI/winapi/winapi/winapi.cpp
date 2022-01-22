// winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "winapi.h"
#include <list>

using namespace std;
#define MAX_LOADSTRING 100

typedef struct _tagRectangle
{
    float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

// 총알 구조체
typedef struct _tagBullet
{
    RECTANGLE rc;
    float fDist; // 현재 거리
    float fLimitDist; // 제한 거리
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

RECTANGLE g_tPlayerRC = { 100, 100, 200, 200 };

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

#pragma region 전역 함수 부분
void Run();
#pragma endregion



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
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 화면용 DC 생성
    g_hDC = GetDC(g_hWnd);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

    QueryPerformanceFrequency(&g_tSecond); // 초당 실행 빈도수
    QueryPerformanceCounter(&g_tTime); // 이전 프레임의 시간을 얻어옴.

    // 기본 메시지 루프입니다:
    while (g_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
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

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

void Run()
{
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

    // 플레이어 초당 이동속도 : 300
    float fSpeed = 300 * g_fDeltaTime * fTimeScale;

    if (GetAsyncKeyState('D') & 0x8000)
    {
        g_tPlayerRC.l += fSpeed;
        g_tPlayerRC.r += fSpeed;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        g_tPlayerRC.l -= fSpeed;
        g_tPlayerRC.r -= fSpeed;
    }
    if (GetAsyncKeyState('W') & 0x8000)
    {
        g_tPlayerRC.t -= fSpeed;
        g_tPlayerRC.b -= fSpeed;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        g_tPlayerRC.t += fSpeed;
        g_tPlayerRC.b += fSpeed;
    }

    RECT rcWindow;
    GetClientRect(g_hWnd, &rcWindow);


    if (g_tPlayerRC.l < rcWindow.left)
    {
        g_tPlayerRC.l = rcWindow.left;
        g_tPlayerRC.r = rcWindow.left + 100;
    }
    else if (g_tPlayerRC.r > rcWindow.right)
    {
        g_tPlayerRC.l = rcWindow.right-100;
        g_tPlayerRC.r = rcWindow.right;
    }

    if (g_tPlayerRC.t < rcWindow.top)
    {
        g_tPlayerRC.t = rcWindow.top;
        g_tPlayerRC.b = rcWindow.top + 100;
    }
    else if (g_tPlayerRC.b > rcWindow.bottom)
    {
        g_tPlayerRC.t = rcWindow.bottom-100;
        g_tPlayerRC.b = rcWindow.bottom;
    }

    // 총알 생성 부
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        BULLET tBullet;

        tBullet.rc.l = g_tPlayerRC.r;
        tBullet.rc.r = g_tPlayerRC.r + 50.f;
        tBullet.rc.t = (g_tPlayerRC.t + g_tPlayerRC.b) / 2.f - 25.f;
        tBullet.rc.b = (g_tPlayerRC.t + g_tPlayerRC.b) / 2.f + 25.f;
        tBullet.fDist = 0.f; // 현재 거리는 0;
        tBullet.fLimitDist = 400.f; // 최대 거리는 400;

        g_PlayerBulletList.push_back(tBullet);
    }

    // 총알 리스트 반복자
    list<BULLET>::iterator iter;
    list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

    // 총알 속도
    fSpeed = 600.f * g_fDeltaTime * fTimeScale;

    // 플레이어 총알 이동
    for (iter = g_PlayerBulletList.begin(); iter != iterEnd;) //++iter 제거
    {
        (*iter).rc.l += fSpeed;
        (*iter).rc.r += fSpeed;
        (*iter).fDist += fSpeed;

        // 현재 거리가 최대 거리를 넘어가면 
        if ((*iter).fDist >= (*iter).fLimitDist)
        {
            // erase하면 다음 iterator를 가져옴.
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }

        // 화면 영역을 벗어나면
        else if ((*iter).rc.l > 800)//rcWindow.right)
        {
            // erase하면 다음 iterator를 가져옴.
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }
        else
            ++iter; //삭제가 안되면 정상적으로 반복자를 올려줌.
    }

    // 총알 출력
    for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
    {
        Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
    }

    Rectangle(g_hDC, g_tPlayerRC.l, g_tPlayerRC.t, g_tPlayerRC.r, g_tPlayerRC.b);
}