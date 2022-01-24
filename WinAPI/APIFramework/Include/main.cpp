//main.cpp
#include "CCore.h" // Window.h ���

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // ���� �ν��Ͻ� �ʱ�ȭ�� �����Ѵٸ�.
    if (!CCore::GetInst()->Init(hInstance))
    {
        CCore::DestroyInst(); // �ھ��� �޸𸮸� ����.
        return 0;
    }

    int iRev = CCore::GetInst()->Run();

    CCore::DestroyInst();

    return iRev;
}