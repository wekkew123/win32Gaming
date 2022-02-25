#pragma once
#include "../Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene()=0;

private:
	static unordered_map<string, class CObject*>	m_mapPrototype[CS_END];

public:
	static void ErasePrototype(SCENE_CREATE sc);
	static void ErasePrototype(const string& strTag, SCENE_CREATE sc);

protected:
	list<class CLayer*> m_LayerList;
	SCENE_CREATE	m_eSceneType;

public:
	void SetSceneType(SCENE_CREATE eType)
	{
		m_eSceneType = eType;
	}

	SCENE_CREATE GetSceneType()
	{
		return m_eSceneType;
	}

public:
	class CLayer* CreateLayer(const string& strTag, int iZorder = 0);
	class CLayer* FindLayer(const string& strTag);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);

public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);

public:
	template <typename T>
	static T* CreatePrototype(const string& strTag, SCENE_CREATE sc)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELLASE(pObj);
			return NULL;
		}

		pObj->AddRef();
		m_mapPrototype[sc].insert(make_pair(strTag, pObj));

		return pObj;
	}

public:
	static CObject* FindPrototype(const string& strKey, SCENE_CREATE sc);
	static void ChangePrototype();

};

