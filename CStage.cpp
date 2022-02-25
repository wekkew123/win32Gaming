#include "CStage.h"
#include "../Resources/CTexture.h"
#include "../CCore.h"
#include "../Core/CCamera.h"
#include "../Colliber/CColliderRect.h"

CStage::CStage()
{
}

CStage::CStage(const CStage& obj)	:
	CStaticObj(obj)
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{

	SetPos(0.f, 0.f);
	SetSize(1920.f, 1080.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage1", L"MAP.bmp"); 

	return true;
}

void CStage::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTIme)
{
	CStaticObj::Collision(fDeltaTIme);
}

void CStage::Render(HDC hdc, float fDeltaTime)
{
	//CStaticObj::Render(hdc, fDeltaTime);
	if (m_pTexture)
	{
		POSITION	tPos = m_tPos - m_tSize * m_tPivot;
		POSITION	tCamPos = GET_SINGLE(CCamera)->GetPos();

		BitBlt(hdc, 0, 0, GetRESOLUTION.iW,GetRESOLUTION.iH,
			m_pTexture->GetDc(),tCamPos.x, tCamPos.y, SRCCOPY);
	}
}

CStage* CStage::Clone()
{
	return new CStage(*this);
}
