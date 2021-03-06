#include "framework.h"
#include "CTextObject.h"

CTextObject::CTextObject()
{
}

CTextObject::CTextObject(wstring _strText, OBJ_TYPE _objGroup) :
	CGameObject(_objGroup)
{
	m_strText = _strText;
}

CTextObject::~CTextObject()
{
}

void CTextObject::Init()
{
}

void CTextObject::Update()
{
}

void CTextObject::Render(HDC _hDC)
{
	WCHAR str[50];
	swprintf_s(str, L"%s", m_strText.c_str());
	TextOutW(_hDC, (int)m_vec2Pos.x, (int)m_vec2Pos.y, str, (int)m_strText.size());
}
