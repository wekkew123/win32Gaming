#pragma once
#include "../Game.h"

class CCamera
{
private:
	POSITION	m_tPos;
	RESOLUTION	m_tClientRS;
	RESOLUTION	m_tWorldRS;
	POSITION	m_tPivot;
	class CObject* m_pTarget;
	class CObject* m_pSKTarget;
	

public:
	void SetTarget(class CObject* pObj);
	void SetSKTarget(CObject* pObj);

	void SetPivot(const POSITION& tPivot)
	{
		m_tPivot = tPivot;
	}
	void SetPivot(float x, float y)
	{
		m_tPivot = POSITION(x, y);
	}
	void SetPos(const POSITION& ps)
	{
		m_tPos = ps;
	}
	void SetPos(float x,float y)
	{
		m_tPos = POSITION(x, y);
	}
	void SetClientResolution(const RESOLUTION& rs)
	{
		m_tClientRS = rs;
	}
	void SetClientResolution(int x, int y)
	{
		m_tClientRS = RESOLUTION(x, y);
	}
	void SetWorldResolution(const RESOLUTION& rs)
	{
		m_tWorldRS = rs;
	}
	void SetWorldResolution(int x, int y)
	{
		m_tWorldRS = RESOLUTION(x, y);
	}

	POSITION GetPos()	const
	{
		return m_tPos;
	}

public:
	bool Init(const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTime);
	
	DECLARE_SINGLE(CCamera);
};

