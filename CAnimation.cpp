#include "CAnimation.h"
#include "../Resources/CTexture.h"
#include "../Resources/CRecourceManager.h"
#include "../Object/CObject.h"

CAnimation::CAnimation() :
	m_pCurClip(NULL),
	m_bMotionEnd(false)
{
}

CAnimation::CAnimation(const CAnimation& ani)
{
	*this = ani;
	m_bMotionEnd = false;

	m_mapClip.clear();

	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		PANIMATIONCLIP pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;

		for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
		{
			pClip->vecTexture[i]->AddRef();
		}
	}

	m_pCurClip = NULL;

	m_strCurClip = "";
	SetCurrentClip(ani.m_strCurClip);
}

CAnimation::~CAnimation()
{

	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		for (size_t i = 0; i < iter->second->vecTexture.size(); ++i)
		{
			SAFE_RELLASE(iter->second->vecTexture[i]);
		}
		SAFE_DELETE(iter->second);
	}

	m_mapClip.clear();
}



bool CAnimation::AddClip(const string& strName, ANIMATION_TYPE eType,
	ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFramMaxX, 
	int iFramMaxY, int iStarX, int iStarY, int iLengthX, int iLengthY, 
	float fOptionLimitTIme, const string& strTexKey, const wchar_t* pFileName,
	const string& strPathKey)
{
	PANIMATIONCLIP	pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iFramMaxX = iFramMaxX;
	pClip->iFramMaxY = iFramMaxY;
	pClip->iStarX = iStarX;
	pClip->iStarY = iStarY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTIme = fOptionLimitTIme;
	pClip->fAnimationFramTime = fAnimationLimitTime / (iLengthX * iLengthY);

	CTexture* pTexture = GET_SINGLE(CRecourceManager)->LoadTexture(strTexKey,pFileName,strPathKey);

	pClip->vecTexture.push_back(pTexture);
	
	pClip->fAnimationTime = 0.f;
	pClip->iFramX = iStarX;
	pClip->iFramY = iStarY;
	pClip->fOptionTIme = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
		SetDefaultClip(strName);

	if(m_strCurClip.empty())
		SetCurrentClip(strName);


	return true;
}

bool CAnimation::AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, 
	float fAnimationLimitTime, int iFramMaxX, int iFramMaxY, int iStarX, int iStarY, int iLengthX, 
	int iLengthY, float fOptionLimitTIme, const string& strTexKey, const vector<wstring>& vecpFileName,
	const string& strPathKey)
{
	PANIMATIONCLIP	pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iFramMaxX = iFramMaxX;
	pClip->iFramMaxY = iFramMaxY;
	pClip->iStarX = iStarX;
	pClip->iStarY = iStarY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTIme = fOptionLimitTIme;
	pClip->fAnimationFramTime = fAnimationLimitTime / (iLengthX * iLengthY);

	for (size_t i = 0; i < vecpFileName.size(); ++i)
	{
		char strKey[256] = {};
		sprintf_s(strKey, "%s%d", strTexKey.c_str(), i + 1);
		CTexture* pTexture = GET_SINGLE(CRecourceManager)->LoadTexture(strKey, vecpFileName[i].c_str(), strPathKey);

		pClip->vecTexture.push_back(pTexture);
	}

	pClip->fAnimationTime = 0.f;
	pClip->iFramX = iStarX;
	pClip->iFramY = iStarY;
	pClip->fOptionTIme = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
		SetDefaultClip(strName);

	if (m_strCurClip.empty())
		SetCurrentClip(strName);


	return true;
}

void CAnimation::SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	PANIMATIONCLIP pClip = FindClip(strClip);

	if (!pClip)
		return;

	for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
		pClip->vecTexture[i]->SetColorKey(r, g, b);

}

void CAnimation::SetCurrentClip(const string& strCurClip)
{
	ChangeClip(strCurClip);
}

void CAnimation::SetDefaultClip(const string& strDefaultClip)
{
	m_strDefaultClip = strDefaultClip;
}

void CAnimation::ChangeClip(const string& strClip)
{
	if (m_strCurClip == strClip)
		return;

	m_strCurClip = strClip;

	if (m_pCurClip)
	{
		m_pCurClip->iFramMaxX = m_pCurClip->iStarX;
		m_pCurClip->iFramMaxY = m_pCurClip->iStarY;
		m_pCurClip->fAnimationTime = 0.f;
		m_pCurClip->fOptionTIme = 0.f;
	}

	m_pCurClip = FindClip(strClip);

	if (m_pCurClip->eType == AT_ATLAS)
		m_pObj->SetTexture(m_pCurClip->vecTexture[0]);


	else if (m_pCurClip->eType == AT_FRAME)
		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFramX-1]);

}

void CAnimation::RetrunClip()
{
	ChangeClip(m_strDefaultClip);
}


PANIMATIONCLIP CAnimation::FindClip(const string& strName)
{
	unordered_map<string, PANIMATIONCLIP>::iterator iter = m_mapClip.find(strName);

	if (iter == m_mapClip.end())
		return NULL;


	return iter->second;
}

bool CAnimation::Init()
{
	return true;
}

void CAnimation::Update(float fTime)
{
	m_bMotionEnd = false;

	m_pCurClip->fAnimationTime += fTime;

	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFramTime)
	{
		m_pCurClip->fAnimationTime -= m_pCurClip->fAnimationFramTime;

		++m_pCurClip->iFramX;

		if (m_pCurClip->iFramX - m_pCurClip->iStarX == m_pCurClip->iLengthX)
		{
			m_pCurClip->iFramX = m_pCurClip->iStarX;
			++m_pCurClip->iFramY;

		/*	if (m_pCurClip->eType == AT_FRAME)
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFramX]);*/

			if (m_pCurClip->iFramY - m_pCurClip->iStarY == m_pCurClip->iLengthY)
			{
				m_pCurClip->iFramY = m_pCurClip->iStarY;

				m_bMotionEnd = true;
				switch (m_pCurClip->eOption)
				{
				case AO_ONCE_RETURN:
					ChangeClip(m_strDefaultClip);
					break;
				case AO_ONCE_DESTROY:
					m_pObj->Die();
					break;
				case AO_TIME_RETURN:
					break;
				case AO_TIME_DESTROY:
					break;
				}
			}
		}
		//else
		//{
		//	if (m_pCurClip->eType == AT_FRAME)
		//		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFramX]);
		//}
	}
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}
