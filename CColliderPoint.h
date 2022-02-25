#pragma once
#include "CCollider.h"
class CColliderPoint :
	public CCollider
{
protected:
	friend class CObject;

protected:
	CColliderPoint();
	CColliderPoint(const CColliderPoint& coll);
	virtual ~CColliderPoint();

protected:
	POSITION	m_tDist;
	POSITION	m_tPos;

public:
	POSITION GetPoint()	const
	{
		return m_tPos;
	}
public:
	void SetDistance(float x, float y)
	{
		m_tDist.x = x;
		m_tDist.y = y;
	}
	void SetDistance(const POSITION& pt)
	{
		m_tDist = pt;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CColliderPoint* Clone();
};

