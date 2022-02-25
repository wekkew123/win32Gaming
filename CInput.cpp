#include "CInput.h"
#include "../Object/CMouse.h"
#include "../Animation/CAnimation.h"
#include "../Scene/CLayer.h"
#include "../Colliber/CColliderManager.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_pCreateKey(NULL),
	m_pMouse(NULL)
{
}
CInput::~CInput()
{
	CObject::EraseObj(m_pMouse);
	SAFE_RELLASE(m_pMouse);
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey("MoveLeft",'A');
	AddKey("MoveRight", 'D');
	AddKey("Fire", VK_SPACE);
	AddKey("Skill", 'X',VK_CONTROL);
	AddKey("MouseButton", VK_LBUTTON);

	//마우스 위치를 얻어오는 함수이다
	GetCursorPos(&m_tMousePos);

	//마우스 생성
	m_pMouse = CObject::CreateObj<CMouse>("Mouse");

	m_pMouse->SetSize(30, 30);
	CAnimation* pAni = m_pMouse->CreateAnimation("MouseAnimation");

	m_pMouse->AddAnimationClip("Mouse", AT_ATLAS, AO_LOOP, 0.9f, 9, 1, 0, 0, 9, 1, 0.f,
		"NormalMouse", L"Mouse.bmp");
	m_pMouse->SetAnimationClipColorKey("Mouse", 255, 255, 255);

	SAFE_RELLASE(pAni);

	return true;
}

void CInput::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int iPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++iPushCount;
		}
		if (iPushCount == iter->second->vecKey.size())
		{
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bDown = true;
				iter->second->bPress = true;
			}
			else if (iter->second->bDown)
				iter->second->bDown = false;
		}
		else
		{
			if (iter->second->bDown || iter->second->bPress)
			{
				iter->second->bUp = true;
				iter->second->bPress = false;
				iter->second->bDown = false;
			}
			else if (iter->second->bUp)
				iter->second->bUp = false;
		}
	}

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);

	GET_SINGLE(CColliderManager)->AddObject(m_pMouse);
}

bool CInput::KeyDown(const string& strKey) const
{
	PKEYINFO  pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bDown;
}

bool CInput::KeyPress(const string& strKey) const
{
	PKEYINFO  pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bPress;
}

bool CInput::KeyUp(const string& strKey) const
{
	PKEYINFO  pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bUp;
}

PKEYINFO CInput::FindKey(const string& strKey)	 const
{
	unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}
