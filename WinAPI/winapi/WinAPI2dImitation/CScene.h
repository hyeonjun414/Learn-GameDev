#pragma once

// ���� ���� : �ش� Ŭ������ ������ ������ ����� �� �ְ����ش�. -> �������� ũ�⸸ �˷���.
// 1. ��������� ������ ȣ��Ǿ� #pragma once ����θ� Ȯ�� �Ұ��� ���� �ذ�
// 2. ������ �ӵ��� ����.
class CGameObject;

class CScene
{
protected:
	vector<CGameObject*>	m_vecObjectList[(int)OBJ_TYPE::SIZE]; // ���� ������Ʈ�� �׷캰�� ������ ����
	wstring					m_strName;
	SCENE_TYPE				m_enumSceneType;

public:
	CScene();
	CScene(wstring _sceneName, SCENE_TYPE _sceneType);
	virtual ~CScene();

	virtual void	Update();
	virtual void	FinalUpdate();
	virtual void	Render(HDC _hDC);

	virtual void	Enter() = 0;
	virtual void	Exit() = 0;

	void			SetName(const wstring& _strName){ m_strName = _strName; }
	wstring			GetName()						{ return m_strName; }


	void			AddObject(CGameObject* _pObj);
	void			EraseObject(CGameObject* _pObj);

protected:
	void			ClearObject();
};
