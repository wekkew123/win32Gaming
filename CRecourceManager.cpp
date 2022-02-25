#include "CRecourceManager.h"
#include "CTexture.h"

DEFINITION_SINGLE(CRecourceManager)

CRecourceManager::CRecourceManager()
{
}
CRecourceManager::~CRecourceManager()
{
	SAFE_RELLASE(m_pBackBuffer);
	Safe_Release_Map(m_mapTexture);
}

CTexture* CRecourceManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();
	return m_pBackBuffer;
}

bool CRecourceManager::Init(HINSTANCE hInst,HDC hdc)
{
	m_hInst = hInst;
	m_hDc = hdc;

	//백버퍼를 불러온다 
	m_pBackBuffer = LoadTexture("BackBuffer", L"BF.bmp");

	return true;
}

CTexture* CRecourceManager::LoadTexture(const string& strKey,
	const wchar_t* pFileName, const string& strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;

	if(!pTexture->LoadTexture(m_hInst,m_hDc,strKey,pFileName,strPathKey))
	{
		SAFE_RELLASE(pTexture);
		return NULL;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

CTexture* CRecourceManager::FindTexture(const string& strKey)
{
	unordered_map<string, CTexture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return NULL;

	iter->second->AddRef();


	return iter->second;
}
