#include "CMinion.h"
#include "../CCore.h"
#include "../Resources/CTexture.h"
#include "../Colliber/CColliderRect.h"
#include "CBullet.h"
#include "../CMath.h"
#include "../Scene/CScene.h"

CMinion::CMinion()	:
	m_fFireTime(0.f),
	m_fFireLimitTime(1.13f)
{
}

CMinion::CMinion(const CMinion& minion)	:
	CMoveObj(minion)
{
	m_eDir = minion.m_eDir;
	m_fFireLimitTime = minion.m_fFireLimitTime;
	m_fFireTime = minion.m_fFireTime;
}

CMinion::~CMinion()
{
}

bool CMinion::Init()
{
	SetPos(700.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(300.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Minion", L"B.bmp");

	m_pTexture->SetColorKey(RGB(255, 255, 255));

	m_eDir = MD_FRONT;

	CColliderRect* pRc = AddCollider<CColliderRect>("MinionBody");

	pRc->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRc->AddCollsionFunction(CS_ENTER, this, &CMinion::CollisionBullet);	

	SAFE_RELLASE(pRc);


	CColliderRect* pRc1 = AddCollider<CColliderRect>("MinionTrace");

	pRc1->SetRect(-300.f, -300.f, 300.f, 300.f);
	pRc1->AddCollsionFunction(CS_STAY, this, &CMinion::Trace);

	SAFE_RELLASE(pRc1);

	return true;
}

int CMinion::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	/*MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.y + m_tSize.y >= GetRESOLUTION.iH)
	{
		m_tPos.y = GetRESOLUTION.iH - m_tSize.y;
		m_eDir = MD_BACK;
	}

	else if (m_tPos.y < 0.f)
	{
		m_tPos.y = 0.f;
		m_eDir = MD_FRONT;
	}
	m_fFireTime += fDeltaTime;
	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime -= m_fFireLimitTime;
		Fire();
	}*/
	return 0;
}

int CMinion::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMinion::Collision(float fDeltaTIme)
{
	CMoveObj::Collision(fDeltaTIme);
}

void CMinion::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);
	//WCHAR	pnt[30] = {};
	//wsprintf(pnt, L"x : %d y : %d", (int)m_tPos.x, (int)m_tPos.y);
	//TextOut(hdc, 100, 0, pnt, wcslen(pnt));
}

CMinion* CMinion::Clone()
{
	return new CMinion(*this);
}

void CMinion::CollisionBullet(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
}

void CMinion::Fire()
{
	CObject* pBullet = CObject::CreateClone("Bullet", "MinionBullet", m_pScene->GetSceneType() ,m_pLayer);

	pBullet->AddCollsionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

	((CMoveObj*)pBullet)->SetAngle(PI);

	float x = GetLeft() - (pBullet->GetSize().x * (1.f-pBullet->GetPivot().x));
	float y = GetCenter().y;

	pBullet->SetPos(x, y);

	SAFE_RELLASE(pBullet);
}

void CMinion::Trace(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
	if (pScr->GetTag() == "MinionTrace" && pDest->GetTag() == "PlayerBody")
	{
		POSITION ps(((CColliderRect*)pDest)->GetWorldInfo().r- 50.f,
			((CColliderRect*)pDest)->GetWorldInfo().b- 50.f);
		
		if (ps.x <= m_tPos.x && ps.y <= m_tPos.y)
		{
			float fDist = CMath::GetDistance(ps, m_tPos);

			m_tPos.x -= fDist * fDeltaTIme;
			m_tPos.y -= fDist * fDeltaTIme;
		}
		else if (ps.x >= m_tPos.x && ps.y >= m_tPos.y)
		{
			float fDist = CMath::GetDistance(ps, m_tPos);

			m_tPos.x += fDist * fDeltaTIme;
			m_tPos.y += fDist * fDeltaTIme;
		}
		else if (ps.x <= m_tPos.x)
		{
			float fDist = CMath::GetDistance(ps, m_tPos);

			m_tPos.x -= fDist * fDeltaTIme;
			m_tPos.y += fDist * fDeltaTIme;
		}
		else
		{
			float fDist = CMath::GetDistance(ps, m_tPos);

			m_tPos.x += fDist * fDeltaTIme;
			m_tPos.y -= fDist * fDeltaTIme;
		}

	}
}
