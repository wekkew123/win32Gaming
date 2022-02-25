#include "CColliderSphere.h"
#include "../Object/CObject.h"
#include "CColliderRect.h"
#include "CColliderPoint.h"
#include "CColliderPixel.h"

CColliderSphere::CColliderSphere()
{
	m_eCollType = CT_SPHERE;
}

CColliderSphere::CColliderSphere(const CColliderSphere& coll)	:
	CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}

CColliderSphere::~CColliderSphere()
{
}

bool CColliderSphere::Init()
{
	return true;
}

void CColliderSphere::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderSphere::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderSphere::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION	tPos = m_pObj->GetPos();
	m_tWorldInfo.tCenter = tPos+m_tInfo.tCenter;
	m_tWorldInfo.fRadius = m_tInfo.fRadius;
	return 0;
}

bool CColliderSphere::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_SPHERE:
		return CollisionSphereToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_RECT:
		return CollisionRectToSphere(((CColliderRect*)pDest)->GetWorldInfo(), m_tWorldInfo);
	case CT_POINT:
		return CollisionSphereToPoint(m_tWorldInfo, ((CColliderPoint*)pDest)->GetPoint());
	}

	return false;
}

void CColliderSphere::Render(HDC hdc, float fDeltaTime)
{
	CCollider::Render(hdc, fDeltaTime);
}

CColliderSphere* CColliderSphere::Clone()
{
	return new CColliderSphere(*this);
}
