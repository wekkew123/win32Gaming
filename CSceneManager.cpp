#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CStartScene.h"
#include "../Colliber/CColliderManager.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager() :
	m_pScene(NULL),
	m_pNextScene(NULL)
{
}
CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
}

bool CSceneManager::Init()
{
	CreateScene<CStartScene>(SC_CURRENT);

	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

SCENE_CHANGE CSceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	return ChangeScene();
}

SCENE_CHANGE CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
	return ChangeScene();
}

void CSceneManager::Collision(float fDeltaTIme)
{
	m_pScene->Collision(fDeltaTIme);
}

void CSceneManager::Render(HDC hdc, float fDeltaTime)
{
	m_pScene->Render(hdc,fDeltaTime);
}

SCENE_CHANGE CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_DELETE(m_pScene);
		m_pScene = m_pNextScene;
		m_pNextScene = NULL;

		GET_SINGLE(CColliderManager)->Clear();

		m_pScene->SetSceneType(SC_CURRENT);

		CScene::ChangePrototype();

		return SC_CHANGE;
	}

	return SC_NONE;
}

