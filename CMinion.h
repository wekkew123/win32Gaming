#pragma once
#include "CMoveObj.h"
class CMinion :
	public CMoveObj
{
private:
	friend class CObject;
	friend class CScene;

private:
	CMinion();
	CMinion(const CMinion& minion);
	~CMinion();

private:
	MOVE_DIR	m_eDir;
	float		m_fFireTime;
	float		m_fFireLimitTime;

public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CMinion* Clone();

public:
	void CollisionBullet(class CCollider* pScr, class CCollider* pDest, float fDeltaTIme);

private:
	void Fire();
	void Trace(CCollider* pScr, CCollider* pDest, float fDeltaTIme);
};

