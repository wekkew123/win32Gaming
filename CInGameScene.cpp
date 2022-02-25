#include "CInGameScene.h"
#include "../Object/CPlayer.h"
#include "../Object/CMinion.h"
#include "../Object/CBullet.h"
#include "../Object/CStage.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Colliber/CColliderPixel.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	//부모 Scene 클래스의 초기화 함수를 호출해준다 
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("Default");

	CPlayer* pPlayer = CObject::CreateObj<CPlayer>("Player", pLayer);

	GET_SINGLE(CCamera)->SetTarget(pPlayer);

	SAFE_RELLASE(pPlayer);

	CMinion* pMinion = CObject::CreateObj<CMinion>("Minion", pLayer);

	SAFE_RELLASE(pMinion);

	//총알 프로토타입을 만들어준다
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet",m_eSceneType);

	pBullet->SetSize(50.f, 50.f);

	SAFE_RELLASE(pBullet);

	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObject::CreateObj<CStage>("Stage", pStageLayer);

	CColliderPixel* pPixel = pStage->AddCollider<CColliderPixel>("StageColl");

	pPixel->SetPixelInfo("MAP.bmp");

	SAFE_RELLASE(pPixel);

	SAFE_RELLASE(pStage);

	return true;
}
