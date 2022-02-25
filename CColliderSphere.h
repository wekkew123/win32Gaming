#pragma once
#include "CCollider.h"
class CColliderSphere :
	public CCollider
{
protected:
	friend class CObject;

protected:
	CColliderSphere();
	CColliderSphere(const CColliderSphere& coll);
	virtual ~CColliderSphere();

private:
	SPHERE		m_tInfo;
	SPHERE		m_tWorldInfo;
	
public:
	void SetSphere(const POSITION& tCenter, float fRadius)
	{
		m_tInfo.tCenter = tCenter;
		m_tInfo.fRadius = fRadius;
	}
	SPHERE GetInfo()	const
	{
		return m_tInfo;
	}
	SPHERE GetWorldInfo()	const
	{
		return m_tWorldInfo;
	}
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CColliderSphere* Clone();
};

