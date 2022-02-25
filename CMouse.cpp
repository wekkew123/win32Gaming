#include "CMouse.h"
#include "../CCore.h"
#include "../Colliber/CColliderPoint.h"

CMouse::CMouse()
{
}

CMouse::CMouse(const CMouse& mouse)	:
	CUi(mouse)
{
}

CMouse::~CMouse()
{
}

bool CMouse::Init()
{
	POINT	pt;
	//스크린 좌표 기준으로 나온다 
	GetCursorPos(&pt);
	ScreenToClient(GETWINDOWHANDLE, &pt);

	ShowCursor(FALSE);

	m_tPos.x = pt.x;
	m_tPos.y = pt.y;

	CColliderPoint* pColl = AddCollider<CColliderPoint>("Mouse");

	SAFE_RELLASE(pColl);

	return true;
}

void CMouse::Input(float fDeltaTime)
{
	CUi::Input(fDeltaTime);
}

int CMouse::Update(float fDeltaTime)
{
	CUi::Update(fDeltaTime);

	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(GETWINDOWHANDLE, &pt);

	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y;

	m_tPos.x = pt.x;
	m_tPos.y = pt.y;

	return 0;
}

int CMouse::LateUpdate(float fDeltaTime)
{
	CUi::LateUpdate(fDeltaTime);
	return 0;
}

void CMouse::Collision(float fDeltaTIme)
{
	CUi::Collision(fDeltaTIme);
}

void CMouse::Render(HDC hdc, float fDeltaTime)
{
	CUi::Render(hdc,fDeltaTime);
}

CMouse* CMouse::Clone()
{
	return new CMouse(*this);
}

void CMouse::Hit(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
}
