#pragma once
#include "../CRef.h"
#include "../Scene/CLayer.h"
#include "../Colliber/CCollider.h"

class CObject	:
	public CRef
{
protected:
	friend class CScene;

protected:
	CObject();
	CObject(const CObject& obj);
	virtual ~CObject();

private:
	static list<CObject*>	m_ObjList;

public:
	static void AddObj(CObject* pObj);
	static CObject* FindObject(const string& strTag);
	static void EraseObj(CObject* pObj);
	static void EraseObj(const string& strTag);
	static void EraseObj();

protected:
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}
	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}
	class CScene* GetScene() const
	{
		return m_pScene;
	}
	class CLayer* GetLayer() const
	{
		return m_pLayer;
	}

protected:
	bool	m_bIsPhysics;
	float	m_fGravityTime;



public:
	void SetPhysics(bool bPhysics)
	{
		m_bIsPhysics = bPhysics;
	}
	bool GetPhysics()	const
	{
		return m_bIsPhysics;
	}

public:
	void ClearGravity()
	{
		m_fGravityTime = 0.f;
	}


protected:
	string		m_strTag;
	POSITION	m_tPos;
	_SIZE		m_tSize;
	POSITION	m_tPivot;
	class CTexture* m_pTexture;
	list<CCollider*>	m_ColliderList;
	class CAnimation*	 m_pAnimation;

public:
	class CAnimation* CreateAnimation(const string& strTag);
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFramMaxX, int iFramMaxY, int iStarX, int iStarY,
		int iLengthX, int iLengthY, float fOptionLimitTIme, const string& strTexKey,
		const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFramMaxX, int iFramMaxY, int iStarX, int iStarY,
		int iLengthX, int iLengthY, float fOptionLimitTIme, const string& strTexKey,
		const vector<wstring>& vecpFileName, const string& strPathKey = TEXTURE_PATH);

	template<typename T>
	T* AddCollider(const string& strTag)
	{
		T* pCollider = new T;

		pCollider->SetObject(this);
		pCollider->SetTag(strTag);

		if (!pCollider->Init())
		{
			SAFE_RELLASE(pCollider);
			return NULL;
		}

		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);

		return pCollider;
	}

	bool CheckCollider()
	{
		return !m_ColliderList.empty();
	}
	const list<CCollider*>* GetColliderList()	const
	{
		return &m_ColliderList;
	}

	CCollider* GetCollider(const string& strTag);

	template<typename T>
	void AddCollsionFunction(const string& strTag, COLLISION_STATE eState, T* pObj,
		void(T::* pFunc)(CCollider*, CCollider*, float))
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterENd = m_ColliderList.end();

		for(iter = m_ColliderList.begin();iter != iterENd; iter++)
		{
			if ((*iter)->GetTag() == strTag)
			{
				(*iter)->AddCollsionFunction(eState, pObj, pFunc);
				break;
			}
		}

	}

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}
	void SetPos(const POSITION& pos)
	{
		m_tPos = pos;
	}
	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}
	void SetSize(const _SIZE& ps)
	{
		m_tSize = ps;
	}
	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}
	void SetPivot(const POSITION& pt)
	{
		m_tPivot = pt;
	}
	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}
	string GetTag() const
	{
		return m_strTag;
	}
	POSITION GetPos() const 
	{
		return m_tPos;
	}
	_SIZE GetSize()	const
	{
		return m_tSize;
	}
	POSITION GetPivot() const	
	{
		return m_tPivot;
	}
	float GetLeft()	const
	{
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}
	float GetRight() const
	{
		return GetLeft() + m_tSize.x;
	}
	float GetTop()	const
	{
		return m_tPos.y - m_tSize.y * m_tPivot.y;
	}
	float GetBottom() const
	{
		return GetTop() + m_tSize.y;
	}
	POSITION GetCenter() const
	{
		return POSITION(GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f);
	}

public:
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strKey, const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	void SetAnimationClipColorKey(const string& strClip, unsigned char r,
		unsigned char g, unsigned char b);


public:
    virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CObject* Clone() = 0;

public:
	template <typename T>
	static T* CreateObj(const string& strTag, class CLayer* pLayer = NULL)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELLASE(pObj);
			return NULL;
		}

		if (pLayer)
		{
			pLayer->AddObject(pObj);//Layer에 추가
		}

		AddObj(pObj);//전체 오브젝트에 추가

		return pObj;
	}

	static CObject* CreateClone(const string& strPrototypeKey, const string& strTag, SCENE_CREATE sc,class CLayer* pLayer = NULL);
	
};

