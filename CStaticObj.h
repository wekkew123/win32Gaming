#pragma once
#include "CObject.h"
class CStaticObj :
	public CObject
{
protected:
	CStaticObj();
	CStaticObj(const CStaticObj& obj);
	virtual ~CStaticObj();

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CStaticObj* Clone() = 0;
};

