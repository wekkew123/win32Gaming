#pragma once
#include "CObject.h"

enum BUTTON_STATE
{
	BS_NONE,
	BS_MOUSEON,
	BS_CLICK
};

class CUi :
	public CObject
{
protected:
	CUi();
	CUi(const CUi& ui);
	virtual ~CUi()=0;

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CUi* Clone() = 0;
};

