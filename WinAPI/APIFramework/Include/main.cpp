//main.cpp
#include "CCore.h" // Window.h 대신

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // 만약 인스턴스 초기화를 실패한다면.
    if (!CCore::GetInst()->Init(hInstance))
    {
        CCore::DestroyInst(); // 코어의 메모리를 해제.
        return 0;
    }

    int iRev = CCore::GetInst()->Run();

    CCore::DestroyInst();

    return iRev;
}