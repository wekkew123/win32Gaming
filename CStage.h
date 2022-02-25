#pragma once
#include "CStaticObj.h"
class CStage :
	public CStaticObj
{
private:
	friend class CObject;
	friend class CScene;

private:
	CStage();
	CStage(const CStage& obj);
	virtual ~CStage();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CStage* Clone();
};

