#include "CPlayer.h"
#include "CBullet.h"
#include "../Core/CCamera.h"
#include "../Resources/CTexture.h"
#include "CBullet.h"
#include "../Core/CInput.h"
#include "../Colliber/CColliderRect.h"
#include "../Colliber/CColliderManager.h"
#include "../Core/CCamera.h"
#include "../Animation/CAnimation.h"
#include "../Scene/CScene.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& player)	:
	CMoveObj(player)
{
}

CPlayer::~CPlayer()
{
}

 bool CPlayer:: Init()
{
	 SetPos(50.f, 50.f);
	 SetSize(100.f, 100.f);
	 SetSpeed(400.f);
	 SetPivot(0.5f, 0.5f);

	//SetTexture("Player", L"A.bmp");
	//SetColorKey(255, 255, 230);

	 CColliderRect* pRc = AddCollider<CColliderRect>("PlayerBody");

	 pRc->SetRect(-50.f, -50.f, 50.f, 50.f);
	 pRc->AddCollsionFunction(CS_ENTER, this, &CPlayer::Hit);
	 pRc->AddCollsionFunction(CS_STAY, this, &CPlayer::HitStay);
	 SAFE_RELLASE(pRc);

	 m_iHP = 1000;

	 //중력을 적용한다
	 SetPhysics(true);

	 //점프할 힘을 설정한다
	 SetForce(150.f);

	 CAnimation* pAni =  CreateAnimation("PlayerAnimation");

	 AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 0.4f, 4,1, 0,0, 4, 1, 0.f, 
		 "PlayerIdleRight", L"Idle/Right/IdleRight.bmp");
	 SetAnimationClipColorKey("IdleRight", 255, 255, 255);

	 AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP, 0.4f, 4, 1, 0, 0, 4, 1, 0.f,
		 "PlayerIdleLeft", L"Idle/Left/IdleLeft.bmp");
	 SetAnimationClipColorKey("IdleLeft", 255, 255, 255);

	 AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 0.6f, 6, 1, 0, 0, 6, 1, 0.f,
		 "PlayerRunRight", L"Idle/Right/RunRight.bmp");
	 SetAnimationClipColorKey("RunRight", 255, 255, 255);

	 AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 0.6f, 6, 1, 0, 0, 6, 1, 0.f,
		 "PlayerRunLeft", L"Idle/Left/RunLeft.bmp");
	 SetAnimationClipColorKey("RunLeft", 255, 255, 255);

	 AddAnimationClip("AttackRight", AT_ATLAS, AO_ONCE_RETURN, 0.4f, 4, 1, 0, 0, 4, 1, 0.f,
		 "PlayerAttackRight", L"Idle/Right/Attack.bmp");
	 SetAnimationClipColorKey("AttackRight", 255, 255, 255);

	 AddAnimationClip("AttackLeft", AT_ATLAS, AO_ONCE_RETURN, 0.4f, 4, 1, 0, 0, 4, 1, 0.f,
		 "PlayerAttackLeft", L"Idle/Left/Attack.bmp");
	 SetAnimationClipColorKey("AttackLeft", 255, 255, 255);

	/* vector<wstring> vecFileName;  플레임 애니메이션

	 for (int i = 8; i <= 16; ++i)
	 {
		 wchar_t strFileName[MAX_PATH] = {};
		 wsprintf(strFileName, L"Idle/Left/%d.bmp", i);
		 vecFileName.push_back(strFileName);
	 }

	 AddAnimationClip("AttackLeft", AT_FRAME, AO_ONCE_RETURN, 0.4f, 4, 1, 0, 0, 4, 1, 0.f,
		 "PlayerAttackLeft", vecFileName);
	 SetAnimationClipColorKey("AttackLeft", 255, 255, 255);*/

	 SAFE_RELLASE(pAni);

	 m_iDir = 1;
	 
	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveFront"))
	{
		/*MoveYFromSpeed(fDeltaTime, MD_BACK);*/
		Jump();
	}
	if (KEYPRESS("MoveBack"))
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunRight");
		m_iDir = 1;
		m_pAnimation->SetDefaultClip("IdleRight");
	}
	if (KEYPRESS("MoveLeft"))
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunLeft");
		m_iDir = -1;
		m_pAnimation->SetDefaultClip("IdleLeft");
	}
	if (KEYDOWN("Fire"))
	{
		Fire();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip("AttackLeft");

		else
			m_pAnimation->ChangeClip("AttackRight");
	}
	if (KEYDOWN("Skill"))
	{
		Skill();
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (m_bAttack && m_pAnimation->GetMotionEnd())
		m_bAttack = false;

	if (!m_bMove && !m_bAttack)
		m_pAnimation->RetrunClip();

	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTIme)
{
	CMoveObj::Collision(fDeltaTIme);
}

void CPlayer::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);

	wchar_t strHP[32] = {  };
	wsprintf(strHP, L"HP : %d", m_iHP);
	POSITION	tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
	TextOut(hdc, tPos.x, tPos.y, strHP, wcslen(strHP));
	
	
	/*WCHAR	pnt[30] = {};
	wsprintf(pnt, L"x : %d y : %d", (int)m_tPos.x, (int)m_tPos.y);
	TextOut(hdc, 0, 0, pnt, wcslen(pnt));*/
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}


void CPlayer::Fire()
{
	m_bAttack = true;

	CObject* pBullet = CObject::CreateClone("Bullet", "PlayerBullet",m_pScene->GetSceneType(),m_pLayer);

	pBullet->AddCollsionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

	//오른쪽 가운데를 구한다
	POSITION	tPos;

	/*tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;*/

	if (m_iDir == 1)
		tPos.x = m_tPos.x + (1.f - m_tPivot.x) * m_tSize.x;

	else
		tPos.x = m_tPos.x - (1.f - m_tPivot.x) * m_tSize.x;

	tPos.y = m_tPos.y + (0.5f - m_tPivot.y) * m_tSize.y;

	pBullet->SetPos(tPos.x+pBullet->GetSize().x/2.f, tPos.y -pBullet->GetSize().y/2.f);

	if (m_iDir == -1)
		((CBullet*)pBullet)->SetAngle(PI);

	SAFE_RELLASE(pBullet);
}

void CPlayer::Skill()
{
	CObject* pBullet = CObject::CreateClone("Bullet", "PlayerBullet", m_pScene->GetSceneType(),m_pLayer);

	POSITION	tPos;

	tPos.x = m_tPos.x + (1.f - m_tPivot.x) * m_tSize.x;
	tPos.y = m_tPos.y + (0.5f - m_tPivot.y) * m_tSize.y;

	pBullet->SetPos(tPos.x, tPos.y - pBullet->GetSize().y / 2.f);

	GET_SINGLE(CCamera)->SetSKTarget(pBullet);

	SAFE_RELLASE(pBullet);
}

void CPlayer::Hit(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
	if(pDest->GetObject()->GetTag()=="MinionBullet")
		m_iHP -= 5;
	else if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pScr->GetHitPoint().y - m_tPivot.y * m_tSize.y;

	}
}

void CPlayer::HitStay(CCollider* pScr, CCollider* pDest, float fDeltaTIme)
{
	if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pScr->GetHitPoint().y - m_tPivot.y*m_tSize.y;
	}
}
