#include "CBullet.h"
#include "../Resources/CTexture.h"
#include "../Colliber/CColliderSphere.h"

CBullet::CBullet()	:
	m_fDist(0.f),
	m_fDistMax(400.f)
{
}

CBullet::CBullet(const CBullet& bullet)	:
	CMoveObj(bullet)
{
	m_fDist = bullet.m_fDist;
	m_fDistMax = bullet.m_fDistMax;
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	SetSpeed(600.f);

	SetTexture("Bullet", L"C.bmp");

	m_pTexture->SetColorKey(RGB(255, 242, 0));

	CColliderSphere* pSphere = AddCollider<CColliderSphere>("BulletBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 25.f);

	SAFE_RELLASE(pSphere);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveAngle(fDeltaTime);

	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fDistMax)
		Die();


	return 0;
}

int CBullet::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBullet::Collision(float fDeltaTIme)
{
	CMoveObj::Collision(fDeltaTIme);
}

void CBullet::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);
}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}

void CBullet::Hit(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
	if (GetTag() == "PlayerBullet" && pDest->GetTag() == "MinionBody")
		Die();

	else if (GetTag() == "MinionBullet" && pDest->GetTag() == "PlayerBody")
		Die();
}
