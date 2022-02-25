#include "CStaticObj.h"

CStaticObj::CStaticObj()
{
}

CStaticObj::CStaticObj(const CStaticObj& obj)	:
	CObject(obj)
{
}

CStaticObj::~CStaticObj()
{
}

void CStaticObj::Input(float fDeltaTime)
{
	CObject::Input(fDeltaTime);
}

int CStaticObj::Update(float fDeltaTime)
{
	CObject::Update(fDeltaTime);
	return 0;
}

int CStaticObj::LateUpdate(float fDeltaTime)
{
	CObject::LateUpdate(fDeltaTime);
	return 0;
}

void CStaticObj::Collision(float fDeltaTIme)
{
	CObject::Collision(fDeltaTIme);
}

void CStaticObj::Render(HDC hdc, float fDeltaTime)
{
	CObject::Render(hdc,fDeltaTime);
}
