#include "CScene.h"
#include "CLayer.h"
#include "../Object/CObject.h"

unordered_map<string, CObject*> CScene::m_mapPrototype[CS_END];

CScene::CScene()
{
	CLayer* pLayer = CreateLayer("UI", INT_MAX);
	pLayer = CreateLayer("HUD",INT_MAX-1);
	pLayer = CreateLayer("Default", 1);
	pLayer = CreateLayer("Stage");
	m_eSceneType = SC_CURRENT;
}
CScene::~CScene()
{
	ErasePrototype(m_eSceneType);
	Safe_Delete_VecList(m_LayerList);
}

CLayer* CScene::CreateLayer(const string& strTag, int iZorder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZorder(iZorder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(CScene::LayerSort);
	
	return pLayer;
}

void CScene::ErasePrototype(SCENE_CREATE sc)
{
	Safe_Release_Map(m_mapPrototype[sc]);
}

void CScene::ErasePrototype(const string& strTag,SCENE_CREATE sc)
{
	unordered_map<string, CObject*>::iterator iter = m_mapPrototype[sc].find(strTag);

	if (!iter->second)
		return;

	SAFE_RELLASE(iter->second);
	m_mapPrototype[sc].erase(iter);
}
CObject* CScene::FindPrototype(const string& strKey, SCENE_CREATE sc)
{
	unordered_map<string, CObject*>::iterator iter = m_mapPrototype[sc].find(strKey);

	if (iter == m_mapPrototype[sc].end())
		return NULL;

	return iter->second;
}

void CScene::ChangePrototype()
{
	ErasePrototype(SC_CURRENT);
	m_mapPrototype[SC_CURRENT] = m_mapPrototype[SC_NEXT];
	m_mapPrototype[SC_NEXT].clear();
}

CLayer* CScene::FindLayer(const string& strTag)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
			return *iter;
	}

	return NULL;
}

bool CScene::Init()
{
	return true;
}

void CScene::Input(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
}

int CScene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
	return 0;
}

void CScene::Collision(float fDeltaTIme)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTIme);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
}

void CScene::Render(HDC hdc, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Render(hdc,fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
}

bool CScene::LayerSort(CLayer* pL1, CLayer* pL2)
{
	return pL1->GetZorder() < pL2->GetZorder();
}
