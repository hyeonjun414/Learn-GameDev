#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC         m_hDC;              
    HBITMAP     m_hBMP;
    BITMAP      m_bmpInfo;

    // ���ҽ� �Ŵ����� �ش� ��ü�� ������ �� �ְ� private�� ���� ��
    // friend Ŭ������ CResourceManager�� �������ش�.
    friend CResourceManager;
    CTexture();
    virtual ~CTexture();

public:
    void        Load(const wstring& _strFilePath);

    UINT        Width() { return m_bmpInfo.bmWidth; }
    UINT        Height() { return m_bmpInfo.bmHeight; }

    HDC         GetDC() { return m_hDC; }
    HBITMAP     GetBitmap() { return m_hBMP; }
};
