#pragma once
#include "../Game.h"
class CColliderManager
{
private:
	list<class CObject*>	m_CollisionList;

public:
	void AddObject(class CObject* pObj);
	void Collision(float fDeltaTIme);
	bool Collision(class CObject* pScr, class CObject* pDest, float fDeltaTIme);
	void Clear();

	DECLARE_SINGLE(CColliderManager)
};

