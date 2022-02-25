#include "CLayer.h"
#include "../Object/CObject.h"
#include "../Colliber/CColliderManager.h"

CLayer::CLayer() :
	m_iZorder(0),
	m_strTag(""),
	m_pScene(NULL),
	m_bEnable(true),
	m_bLife(true)
{
}
CLayer::~CLayer()
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;++iter)
	{
		CObject::EraseObj(*iter);
		SAFE_RELLASE((*iter));
	}
	m_ObjList.clear();
}

void CLayer::AddObject(CObject* pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();

	m_ObjList.push_back(pObj);
}

void CLayer::Input(float fDeltaTime)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			CObject::EraseObj(*iter);
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
			++iter;
	}
}

int CLayer::Update(float fDeltaTime)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			CObject::EraseObj(*iter);
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
			++iter;

	}
	return 0;
}

int CLayer::LateUpdate(float fDeltaTime)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			CObject::EraseObj(*iter);
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
			++iter;
	}
	return 0;
}

void CLayer::Collision(float fDeltaTIme)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTIme);

		if (!(*iter)->GetLife())
		{
			CObject::EraseObj(*iter);
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
		{
			GET_SINGLE(CColliderManager)->AddObject(*iter);
			++iter;
		}
	}
}

void CLayer::Render(HDC hdc, float fDeltaTime)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
 		(*iter)->Render(hdc,fDeltaTime);

		if (!(*iter)->GetLife())
		{
			CObject::EraseObj(*iter);
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
			++iter;

	}
}
