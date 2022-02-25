#pragma once
#include "../Game.h"

class CLayer
{
private:
	friend class CScene;

private:
	CLayer();

public:
	~CLayer();

private:
	class CScene* m_pScene;
	string m_strTag;
	int	   m_iZorder; 
	list <class CObject*>   m_ObjList;
	bool	m_bEnable;
	bool	m_bLife;
public:
	void SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
	}
	void Die()
	{
		m_bLife = false;
	}
	bool GetEnable()	const
	{
		return m_bEnable;
	}
	bool GetLife()	const
	{
		return m_bLife;
	}

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}
	void SetZorder(int iZorder)
	{
		m_iZorder = iZorder;
	}
	void SetScene(class CScene* PScene)
	{
		m_pScene = PScene;
	}
	int GetZorder()	const
	{
		return m_iZorder;
	}
	string GetTag()	const
	{
		return m_strTag;
	}
	CScene* GetScene()	const
	{
		return m_pScene;
	}

public:
	void AddObject(class CObject* pObj);

public:
	 void Input(float fDeltaTime);
	 int Update(float fDeltaTime);
	 int LateUpdate(float fDeltaTime);
	 void Collision(float fDeltaTIme);
	 void Render(HDC hdc, float fDeltaTime);
};

