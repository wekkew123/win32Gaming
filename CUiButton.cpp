#include "CUiButton.h"
#include "../Colliber/CColliderRect.h"
#include "../Core/CInput.h"

CUiButton::CUiButton()	:
	m_bEnableCallback(false),
	m_eState(BS_NONE)
{
}

CUiButton::CUiButton(const CUiButton& uibutton)	:
	CUi(uibutton)
{
	m_bEnableCallback = false;
	m_eState = BS_NONE;
}

CUiButton::~CUiButton()
{
}

bool CUiButton::Init()
{
	CColliderRect* pColl = AddCollider<CColliderRect>("ButtonBody");

	SAFE_RELLASE(pColl);

	return true;
}

void CUiButton::Input(float fDeltaTime)
{
	CUi::Input(fDeltaTime);
}

int CUiButton::Update(float fDeltaTime)
{
	CUi::Update(fDeltaTime);
	return 0;
}

int CUiButton::LateUpdate(float fDeltaTime)
{
	CUi::LateUpdate(fDeltaTime);

	if (m_eState != BS_NONE)
	{
		if (KEYPRESS("MouseButton"))
		{
			m_eState = BS_CLICK;
		}
	}

	if (m_eState == BS_CLICK && KEYUP("MouseButton"))
	{
		m_eState = BS_MOUSEON;
		if (m_bEnableCallback)
			m_btnCallBack(fDeltaTime);
	}

	return 0;
}

void CUiButton::Collision(float fDeltaTIme)
{
	CUi::Collision(fDeltaTIme);
}

void CUiButton::Render(HDC hdc, float fDeltaTime)
{
	CUi::Render(hdc,fDeltaTime);

}

CUiButton* CUiButton::Clone()
{
	return new CUiButton(*this);
}

void CUiButton::MouseOn(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_MOUSEON;
	}
}

void CUiButton::MouseOut(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_NONE;
	}
}
