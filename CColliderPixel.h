#pragma once
#include "CCollider.h"


class CColliderPixel :
	public CCollider
{
protected:
	friend class CObject;

protected:
	CColliderPixel();
	CColliderPixel(const CColliderPixel& coll);
	virtual ~CColliderPixel();

private:
	vector<PIXEL>	m_vecPixel;
	int		m_iWidth;
	int		m_iHieght;

public:
	const vector<PIXEL>& GetPixel()		const
	{
		return m_vecPixel;
	}
	int GetWidth()	const
	{
		return m_iWidth;
	}
	int GetHieght()	const
	{
		return m_iHieght;
	}
public:
	bool SetPixelInfo(const char* pFileName, const string& strPathKey = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CColliderPixel* Clone();
};

