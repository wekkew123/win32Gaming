#pragma once
#include "CMoveObj.h"
class CPlayer :
	public CMoveObj
{
private:
	friend class CObject;
	friend class CScene;

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	int m_iHP;
	bool m_bAttack;
	int	 m_iDir;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CPlayer* Clone();

private:
	void Fire();
	void Skill();
	void Hit(class CCollider* pScr, class CCollider* pDest, float fDeltaTIme);
	void HitStay(class CCollider* pScr, class CCollider* pDest, float fDeltaTIme);
};

