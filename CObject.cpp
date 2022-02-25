#include "CObject.h"
#include "../Scene/CLayer.h"
#include "../Scene/CSceneManager.h"
#include "../Scene/CScene.h"
#include "../Resources/CRecourceManager.h"
#include "../Resources/CTexture.h"
#include "../Core/CCamera.h"
#include "../Animation/CAnimation.h"

list<CObject*> CObject::m_ObjList;

CObject::CObject() :
	m_pTexture(NULL),
	m_pAnimation(NULL),
	m_bIsPhysics(false),
	m_fGravityTime(0.f)
{
}

CObject::CObject(const CObject& obj)
{
	*this = obj;

	if (obj.m_pAnimation)
		m_pAnimation = obj.m_pAnimation->Clone();

	m_fGravityTime = 0.f;

	if (m_pTexture)
		m_pTexture->AddRef();

	m_ColliderList.clear();

	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = obj.m_ColliderList.end();

	for (iter = obj.m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		CCollider* pColl = (*iter)->Clone();

		pColl->SetObject(this);

		m_ColliderList.push_back(pColl);
	}
}

CObject::~CObject()
{
	SAFE_RELLASE(m_pAnimation);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELLASE(m_pTexture);
}

void CObject::AddObj(CObject* pObj)
{
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

CObject* CObject::FindObject(const string& strTag)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd;

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return NULL;
}

void CObject::EraseObj(CObject* pObj)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;++iter)
	{
		if (*iter == pObj)
		{
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObject::EraseObj(const string& strTag)
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd;

	for (iter = m_ObjList.begin(); iter != iterEnd;iter++)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELLASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObject::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

CAnimation* CObject::CreateAnimation(const string& strTag)
{
	SAFE_RELLASE(m_pAnimation);

	m_pAnimation = new CAnimation;

	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObj(this);

	if (!m_pAnimation->Init())
	{
		SAFE_RELLASE(m_pAnimation);
		return NULL;
	}

	m_pAnimation->AddRef();

	return m_pAnimation;
}

bool CObject::AddAnimationClip(const string& strName, ANIMATION_TYPE eType, 
	ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFramMaxX, int iFramMaxY, 
	int iStarX, int iStarY, int iLengthX, int iLengthY, float fOptionLimitTIme,
	const string& strTexKey, const wchar_t* pFileName, const string& strPathKey)
{
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime, iFramMaxX, iFramMaxY,
		iStarX, iStarY, iLengthX, iLengthY, fOptionLimitTIme, strTexKey, pFileName, strPathKey);

	return true;
}

bool CObject::AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime, 
	int iFramMaxX, int iFramMaxY, int iStarX, int iStarY, int iLengthX, int iLengthY, 
	float fOptionLimitTIme, const string& strTexKey, const vector<wstring>& vecpFileName,
	const string& strPathKey)
{
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime, iFramMaxX, iFramMaxY,
		iStarX, iStarY, iLengthX, iLengthY, fOptionLimitTIme, strTexKey, vecpFileName, strPathKey);

	return true;
}

CCollider* CObject::GetCollider(const string& strTag)
{
	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}
	return NULL;
}

void CObject::SetTexture(CTexture* pTexture)
{
	SAFE_RELLASE(m_pTexture);
	m_pTexture = pTexture;

	if (pTexture)
		pTexture->AddRef();
}

void CObject::SetTexture(const string& strKey, const wchar_t* pFileName, 
	const string& strPathKey)
{
	SAFE_RELLASE(m_pTexture);

	m_pTexture = GET_SINGLE(CRecourceManager)->LoadTexture(strKey, pFileName, strPathKey);
}

void CObject::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void CObject::SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	if (m_pAnimation)
		m_pAnimation->SetClipColorKey(strClip, r, g, b);
}

void CObject::Input(float fDeltaTime)
{
}

int CObject::Update(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELLASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
	return 0;
}

int CObject::LateUpdate(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELLASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
	if (m_pAnimation)
		m_pAnimation->Update(fDeltaTime);

	return 0;
}

void CObject::Collision(float fDeltaTIme)
{
}

void CObject::Render(HDC hdc, float fDeltaTime)
{
	if (m_pTexture)
	{
		POSITION	tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		POSITION	tImagePos;

		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			tImagePos.x = pClip->iFramX * m_tSize.x;
			tImagePos.y = pClip->iFramY * m_tSize.y;
		}

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hdc, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDc(),
				tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hdc, tPos.x, tPos.y, m_tSize.x, m_tSize.y,
				m_pTexture->GetDc(), tImagePos.x, tImagePos.y, SRCCOPY);
		}
	}
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Render(hdc,fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELLASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
}

CObject* CObject::CreateClone(const string& strPrototypeKey, const string& strTag, SCENE_CREATE sc, class CLayer* pLayer)
{
	CObject* pProto = CScene::FindPrototype(strPrototypeKey,sc);

	if (!pProto)
		return NULL;

	CObject* pObj = pProto->Clone();

	pObj->SetTag(strTag);

	if (pLayer)
	{
		pLayer->AddObject(pObj);
	}

	AddObj(pObj);

	return pObj;
}


