#pragma once


class CCollider;
class CTexture;
class CAnimator;

class CGameObject
{
protected:
	wstring			m_strName;		// 오브젝트 이름

	OBJ_TYPE		m_eType;		// 오브젝트 타입
	bool			m_bIsActive;	// 활성화 여부
	bool			m_bIsGravity;	// 중력 적용 여부

	Vec2			m_vPos;			// 위치
	Vec2			m_vRenderPos;	// 화면상 출력위치
	Vec2			m_vScale;		// 크기

	// 컴포넌트
	CTexture*		m_pTex;			// 텍스쳐
	CCollider*		m_pCollider;	// 충돌체
	CAnimator*		m_pAnimator;	// 애니메이터

public:
	CGameObject();
	CGameObject(OBJ_TYPE _eType);
	CGameObject(const CGameObject& _origin); // 복사 생성자
	virtual ~CGameObject();

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC _hDC) = 0;

	virtual void	FinalUpdate();	// 컴포넌트의 실행 유무는 오브젝트의 최상위 클래스에서 판단한다.
	virtual void	ComponentRender(HDC _hDC) final; // 컴포넌트가 있는 경우 하위 클래스에서 구현된 Render에서 호출한다.

	void			SetName(const wstring& _strName)	{ m_strName = _strName; }
	void			SetObjGroup(OBJ_TYPE _eObjType)		{ m_eType = _eObjType; }
	void			SetActive(bool _active)				{ m_bIsActive = _active; }
	void			SetGravity(bool _active)			{ m_bIsGravity = _active; }
	void			SetPos(Vec2 _pos)					{ m_vPos = _pos; }
	void			SetScale(Vec2 _scale)				{ m_vScale = _scale; }

	const wstring&	GetName()		{ return m_strName; }
	OBJ_TYPE		GetObjGroup()	{ return m_eType; }
	bool			GetActive()		{ return m_bIsActive; }
	bool			GetGravity()	{ return m_bIsGravity; }
	Vec2			GetPos()		{ return m_vPos; }
	Vec2			GetRenderPos()	{ return m_vRenderPos; }
	Vec2			GetScale()		{ return m_vScale; }
	CTexture*		GetTexture()	{ return m_pTex; }
	CCollider*		GetCollider()	{ return m_pCollider; }
	CAnimator*		GetAnimator()	{ return m_pAnimator; }
	
	// Component
	void			TextureRender(HDC _hDC);
	void			CreateCollider();
	void			CreateAnimator();


	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther) {};
	virtual void	OnCollisionExit(CCollider* _pOther) {};

	virtual CGameObject* Clone() = 0;


	
};

