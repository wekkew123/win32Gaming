#include "CColliderRect.h"
#include "../Object/CObject.h"
#include "CColliderSphere.h"
#include "CColliderPixel.h"
#include "CColliderPoint.h"
#include "../Core/CCamera.h"

CColliderRect::CColliderRect()
{
	m_eCollType = CT_RECT;
}

CColliderRect::CColliderRect(const CColliderRect& coll)	:
	CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}

CColliderRect::~CColliderRect()
{
}

void CColliderRect::SetRect(float l, float t, float r, float b)
{
	m_tInfo.l = l;
	m_tInfo.t = t;
	m_tInfo.r = r;
	m_tInfo.b = b;
}

bool CColliderRect::Init()
{
	return true;
}

void CColliderRect::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderRect::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION	tPos = m_pObj->GetPos();
	m_tWorldInfo.l = tPos.x + m_tInfo.l;
	m_tWorldInfo.t = tPos.y + m_tInfo.t;
	m_tWorldInfo.r = tPos.x + m_tInfo.r;
	m_tWorldInfo.b = tPos.y + m_tInfo.b;


	return 0;
}

bool CColliderRect::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo, ((CColliderRect*)pDest)->GetWorldInfo());
	case CT_SPHERE:
		return CollisionRectToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_PIXEL:
		return CollisionRectToPixel(m_tWorldInfo, ((CColliderPixel*)pDest)->GetPixel(),
			((CColliderPixel*)pDest)->GetWidth(), ((CColliderPixel*)pDest)->GetHieght());
	case CT_POINT:
		return CollisionRectToPoint(m_tWorldInfo,((CColliderPoint*)pDest)->GetPoint());
	}

	return false;
}
 
void CColliderRect::Render(HDC hdc, float fDeltaTime)
{
	CCollider::Render(hdc,fDeltaTime);

	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

	RECTANGLE tRc = m_tWorldInfo;
	tRc.l -= tCamPos.x;
	tRc.t -= tCamPos.y;
	tRc.r -= tCamPos.x;
	tRc.b -= tCamPos.y;

	MoveToEx(hdc, m_tInfo.l, m_tInfo.t, NULL);
	LineTo(hdc, m_tInfo.r, m_tInfo.t);
	LineTo(hdc, m_tInfo.r, m_tInfo.b);
	LineTo(hdc, m_tInfo.l, m_tInfo.b);
	LineTo(hdc, m_tInfo.l, m_tInfo.t);
}

CCollider* CColliderRect::Clone()
{
	return new CColliderRect(*this);
}
