#include "framework.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE objGroup) :
	CGameObject(objGroup)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	if (m_bIsActive)
	{
		if (KEYCHECK(KEY::LEFT) == KEY_STATE::HOLD)
		{
			// 왼쪽
			m_vec2Pos.x -= 300 * DT;
		}
		if (KEYCHECK(KEY::RIGHT) == KEY_STATE::HOLD)
		{
			// 오른쪽
			m_vec2Pos.x += 300 * DT;
		}
		if (KEYCHECK(KEY::UP) == KEY_STATE::HOLD)
		{
			// 위쪽
			m_vec2Pos.y -= 300 * DT;
		}
		if (KEYCHECK(KEY::DOWN) == KEY_STATE::HOLD)
		{
			// 아래쪽
			m_vec2Pos.y += 300 * DT;
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	// 움직이는 사각형 출력
	Rectangle(hDC,
		m_vec2Pos.x - m_vec2Scale.x,
		m_vec2Pos.y - m_vec2Scale.y,
		m_vec2Pos.x + m_vec2Scale.x,
		m_vec2Pos.y + m_vec2Scale.y);
}
