#pragma once
#include "CUi.h"
class CUiButton :
	public CUi
{
private:
	friend class CObject;
	friend class CScene;

private:
	CUiButton();
	CUiButton(const CUiButton& uibutton);
	~CUiButton();
private:
	function<void(float fTime)>	m_btnCallBack;
	bool	m_bEnableCallback;
	BUTTON_STATE	m_eState;

public:
	template<typename T>
	void SetCallback(T* pObj, void (T::* pFunc)(float))
	{
		m_btnCallBack = bind(pFunc, pObj, placeholders::_1);
		m_bEnableCallback = true;
	}

	void SetCallback(void (*pFunc)(float))
	{
		m_btnCallBack = bind(pFunc, placeholders::_1);
		m_bEnableCallback = true;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTIme);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CUiButton* Clone();

public:
	void MouseOn(class CCollider* pScr, class CCollider* pDest, float fDeltaTIme);
	void MouseOut(class CCollider* pScr, class CCollider* pDest, float fDeltaTIme);
};

