#pragma once
#include "CGameObject.h"

class CTexture;

class CPlayer :
    public CGameObject
{
private:
    CTexture* m_pTex;
public :
    CPlayer();
    CPlayer(OBJ_TYPE objGroup);
    virtual ~CPlayer();

    virtual void Init();
    virtual void Update();
    virtual void Render(HDC hDC);

    void CreateMissile();
};

