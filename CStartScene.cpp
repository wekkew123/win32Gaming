#include "CStartScene.h"
#include "../Object/CUiPanel.h"
#include "../Object/CUiButton.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Colliber/CColliderRect.h"
#include "../CCore.h"
#include "CSceneManager.h"
#include "CInGameScene.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	//부모 Scene 클래스의 초기화 함수를 호출해준다 
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("UI");


	CUiPanel* pBakcPanel = CObject::CreateObj<CUiPanel>("BackPanel", pLayer);

	pBakcPanel->SetSize(GetRESOLUTION.iW,GetRESOLUTION.iH);

	pBakcPanel->SetTexture("StartBack", L"StartBack.bmp");

	SAFE_RELLASE(pBakcPanel);

	CUiButton* pStartButton = CObject::CreateObj<CUiButton>("StartButton", pLayer);

	pStartButton->SetPos(GetRESOLUTION.iW/2 - 100, GetRESOLUTION.iH/2 -100);
	pStartButton->SetSize(200,200);
	pStartButton->SetTexture("StartButton", L"StartButton.bmp");

	CColliderRect* pRc = (CColliderRect*)pStartButton->GetCollider("ButtonBody");

	POSITION tPos = pStartButton->GetPos();
	pRc->SetRect(0.f, 0.f,200,200);

	pRc->AddCollsionFunction(CS_ENTER, pStartButton, &CUiButton::MouseOn);
	pRc->AddCollsionFunction(CS_LEAVE, pStartButton, &CUiButton::MouseOut);

	SAFE_RELLASE(pRc);

	pStartButton->SetCallback(this, &CStartScene::StartButtonCallback);

	SAFE_RELLASE(pStartButton);

	CUiButton* pEndButton = CObject::CreateObj<CUiButton>("EndButton", pLayer);

	pEndButton->SetPos(GetRESOLUTION.iW / 2 - 100, GetRESOLUTION.iH / 2 +100);
	pEndButton->SetSize(200, 200);
	pEndButton->SetTexture("StartButton", L"StartButton.bmp");

	pRc = (CColliderRect*)pEndButton->GetCollider("ButtonBody");

	tPos = pEndButton->GetPos();
	pRc->SetRect(0.f, 0.f, 200, 200);

	pRc->AddCollsionFunction(CS_ENTER, pEndButton, &CUiButton::MouseOn);
	pRc->AddCollsionFunction(CS_LEAVE, pEndButton, &CUiButton::MouseOut);

	SAFE_RELLASE(pRc);

	pEndButton->SetCallback(this, &CStartScene::EndButtonCallback);

	SAFE_RELLASE(pEndButton);

	return true;
}

void CStartScene::StartButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}
