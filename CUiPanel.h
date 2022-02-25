#pragma once
#include "CUi.h"
class CUiPanel :
	public CUi
{
private:
	friend class CObject;
	friend class CScene;

private:
	CUiPanel();
	CUiPanel(const CUiPanel& uipanel);
	~CUiPanel();
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CUiPanel* Clone();
};

