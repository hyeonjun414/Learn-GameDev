#include "CCore.h"
#include "Scene/CSceneManager.h"

CCore* CCore::m_pInst = NULL;
bool CCore::m_bLoop = true;


CCore::CCore()
{
}

CCore::~CCore()
{
    DESTORY_SINGLE(CSceneManager); // 장면 관리자 메모리 해제.
}

bool CCore::Init(HINSTANCE hInst)
{
    this->m_hInst = hInst;

    MyRegisterClass();

    //해상도 설정
    m_tRS.iW = 1280;
    m_tRS.iH = 720;

    //장면 관리자 초기화
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;

    Create();

    return true;
}

int CCore::Run()
{
    MSG msg;

    // 기본 메시지 루프입니다:
    while (m_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 윈도우 데드타임일 경우
        else
        {

        }
    }
    return (int)msg.wParam;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        EndPaint(hWnd, &ps);
    }
    break;
    // 윈도우 종료시킬때 들어오는 메세지이다.
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL CCore::Create()
{
    m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE; // 생성실패
    }

    // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해준다.
    RECT rc = { 0,0,800,600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야한다.
    // HWND_TOPMOST : 창을 띄울때 최상단에 띄우는 옵션이다.
    // SWP_NOMOVE : 해당 위치에서 움직이지 못하게 하는 옵션.
    // SWP_NOZORDER : ZORDER에 관계없이 창을 출력한다.
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CCore::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_PROJECT2);
    wcex.lpszClassName = L"AR13API";

    return RegisterClassExW(&wcex);
}