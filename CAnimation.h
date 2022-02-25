#pragma once
#include "../CRef.h"

class CAnimation :
	public CRef
{
private:
	friend class CObject;

private:
	CAnimation();
	CAnimation(const CAnimation& ani);
	~CAnimation();

private:
	unordered_map<string, PANIMATIONCLIP>	m_mapClip;
	PANIMATIONCLIP	m_pCurClip;
	string			m_strCurClip;
	string			m_strDefaultClip;
	class CObject* m_pObj;
	bool			m_bMotionEnd;

public:
	bool GetMotionEnd()	const
	{
		return m_bMotionEnd;
	}
	PANIMATIONCLIP GetCurrentClip()	const
	{
		return m_pCurClip;
	}
	void SetObj(class CObject* pObj)
	{
		m_pObj = pObj;
	}

	bool AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFramMaxX, int iFramMaxY, int iStarX, int iStarY,
		int iLengthX, int iLengthY, float fOptionLimitTIme, const string& strTexKey,
		const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

	bool AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFramMaxX, int iFramMaxY, int iStarX, int iStarY,
		int iLengthX, int iLengthY, float fOptionLimitTIme, const string& strTexKey,
		const vector<wstring>& vecpFileName, const string& strPathKey = TEXTURE_PATH);


	void SetClipColorKey(const string& strClip,unsigned char r, unsigned char g, unsigned char b);
	void SetCurrentClip(const string& strCurClip);
	void SetDefaultClip(const string& strDefaultClip);
	void ChangeClip(const string& strClip);
	void RetrunClip();


private:
	PANIMATIONCLIP FindClip(const string& strName);

public:
	bool Init();
	void Update(float fTime);
	CAnimation* Clone();
};

