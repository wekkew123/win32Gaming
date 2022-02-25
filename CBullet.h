#pragma once
#include "CMoveObj.h"
class CBullet :
	public CMoveObj
{
private:
	friend class CMoveObj;
	friend class CScene;

private:
	CBullet();
	CBullet(const CBullet& bullet);
	~CBullet();

private:
	float	m_fDist;
	float	m_fDistMax;


public:
	void SetbulletDistance(float fDist)
	{
		m_fDistMax = fDist;
	}

public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CBullet* Clone();

public:
	void Hit(class CCollider* pScr,class CCollider* pDest, float fDeltaTIme);
};

