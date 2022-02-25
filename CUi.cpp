#include "CUi.h"
#include "../Animation/CAnimation.h"
#include "../Resources/CTexture.h"

CUi::CUi()
{
}

CUi::CUi(const CUi& ui)	:
	CObject(ui)
{
}

CUi::~CUi()
{
}

void CUi::Input(float fDeltaTime)
{
	CObject::Input(fDeltaTime);
}

int CUi::Update(float fDeltaTime)
{
	CObject::Update(fDeltaTime);
	return 0;
}

int CUi::LateUpdate(float fDeltaTime)
{
	CObject::LateUpdate(fDeltaTime);
	return 0;
}

void CUi::Collision(float fDeltaTIme)
{
	CObject::Collision(fDeltaTIme);
}

void CUi::Render(HDC hdc, float fDeltaTime)
{
	if (m_pTexture)
	{
		POSITION	tImagePos;

		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			tImagePos.x = pClip->iFramX * m_tSize.x;
			tImagePos.y = pClip->iFramY * m_tSize.y;
		}

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hdc, m_tPos.x, m_tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDc(),
				tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hdc, m_tPos.x, m_tPos.y, m_tSize.x, m_tSize.y,
				m_pTexture->GetDc(), tImagePos.x, tImagePos.y, SRCCOPY);
		}
	}
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Render(hdc, fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELLASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
}
