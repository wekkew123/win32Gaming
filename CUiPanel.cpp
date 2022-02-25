#include "CUiPanel.h"

CUiPanel::CUiPanel()
{
}

CUiPanel::CUiPanel(const CUiPanel& uipanel)	:
	CUi(uipanel)
{
}

CUiPanel::~CUiPanel()
{
}

bool CUiPanel::Init()
{
	return true;
}

void CUiPanel::Input(float fDeltaTime)
{
	CUi::Input(fDeltaTime);
}

int CUiPanel::Update(float fDeltaTime)
{
	CUi::Update(fDeltaTime);
	return 0;
}

int CUiPanel::LateUpdate(float fDeltaTime)
{
	CUi::LateUpdate(fDeltaTime);
	return 0;
}

void CUiPanel::Collision(float fDeltaTIme)
{
	CUi::Collision(fDeltaTIme);
}

void CUiPanel::Render(HDC hdc, float fDeltaTime)
{
	CUi::Render(hdc,fDeltaTime);
}

CUiPanel* CUiPanel::Clone()
{
	return new CUiPanel(*this);
}
