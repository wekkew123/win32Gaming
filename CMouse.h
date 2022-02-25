#pragma once
#include "CUi.h"
class CMouse :
	public CUi
{
private:
	friend class CObject;
	friend class CScene;

private:
	CMouse();
	CMouse(const CMouse& mouse);
	~CMouse();

private:
	POSITION	m_tMove;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CMouse* Clone();

public:
	void Hit(class CCollider* pScr, class CCollider* pDest, float fDeltaTIme);
};

