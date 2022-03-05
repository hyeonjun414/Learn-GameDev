#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CGameObject(_objGroup)
{
	m_bIsFloor = false;
	// 텍스쳐 불러오기
	//m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\monster01.bmp");
	SetScale(Vec2(55, 55));
	// Collider 만들기
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -m_vec2Scale.y / 2));
	m_pCollider->SetScale(GetScale());

	// 애니메이터 만들기
	CTexture* m_pTexture = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\Animation_Player.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pTexture, Vec2(0.f, 0.f), Vec2(70.f, 70.f),
									Vec2(70.f, 0.f), 0.2f, 2);

	GetAnimator()->Play(L"Player_Idle_Left", true);

	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset();

	// 특정 프레임만 조절 ( 이동 애니메이션 ) 

}

CPlayer::~CPlayer()
{
	delete m_pAnimator;
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	if (m_bIsGravity && !m_bIsFloor) m_vVelocity.y -= 500 * DT;
	m_vec2Pos.y += -m_vVelocity.y * DT;
	

	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		// 왼쪽
		m_vec2Pos.x -= 300 * DT;
		//GetAnimator()->Play(L"Player_Move_Left", true);
	}
	if (KEYCHECK(KEY::A) == KEY_STATE::AWAY)
	{
		//GetAnimator()->Play(L"Player_Idle_Left", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		// 오른쪽
		m_vec2Pos.x += 300 * DT;
		//GetAnimator()->Play(L"Player_Move_Right", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::AWAY)
	{
		//GetAnimator()->Play(L"Player_Idle_Right", true);
	}

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP && m_bIsFloor)
		m_vVelocity.y += 300;

	GetAnimator()->Update();
}

void CPlayer::Render(HDC _hDC)
{
	ComponentRender(_hDC);
}

void CPlayer::CreateMissile()
{
	CMissile* pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(0));
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2+ pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(false);
	pMissile->SetScale(m_vec2Scale);
	pMissile->GetCollider()->SetOffsetPos(Vec2(0, -m_vec2Scale.y / 2));
	CREATEOBJECT(pMissile);
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Floor" &&
		(_pOther->GetOffsetPos().x - _pOther->GetScale().x / 2 >= m_pCollider->GetFinalPos().x ||
			_pOther->GetOffsetPos().x + _pOther->GetScale().x / 2 <= m_pCollider->GetFinalPos().x))
	{
		if (m_vec2Pos.x < _pOther->GetOffsetPos().x)
			m_vec2Pos.x = _pOther->GetOffsetPos().x - _pOther->GetScale().x / 2 - m_pCollider->GetScale().x / 2;
		else
			m_vec2Pos.x = _pOther->GetOffsetPos().x + _pOther->GetScale().x / 2 + m_pCollider->GetScale().x / 2 ;
	}
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Floor" &&
	   (_pOther->GetOffsetPos().x - _pOther->GetScale().x/2 < m_pCollider->GetFinalPos().x&&
		_pOther->GetOffsetPos().x + _pOther->GetScale().x/2 > m_pCollider->GetFinalPos().x))
	{
		m_vVelocity.y = 0;
		m_vec2Pos.y = _pOther->GetOffsetPos().y - _pOther->GetScale().y/2 +1;
		m_bIsFloor = true;
	}


}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Floor")
	{
		m_bIsFloor = false;
	}
}
