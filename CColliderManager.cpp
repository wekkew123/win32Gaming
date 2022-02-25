#include "CColliderManager.h"
#include "../Object/CObject.h"
#include "CCollider.h"

DEFINITION_SINGLE(CColliderManager)

CColliderManager::CColliderManager()
{
}
CColliderManager::~CColliderManager()
{
}

void CColliderManager::AddObject(CObject* pObj)
{
	if (pObj->CheckCollider())
	{
		m_CollisionList.push_back(pObj);
	}
}

void CColliderManager::Collision(float fDeltaTIme)
{
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}

	//오브젝트간 충돌처리를 한다
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		list<CObject*>::iterator iter1 = iter;
		++iter1;
		list<CObject*>::iterator iter1End = m_CollisionList.end();
		for (; iter1 != iter1End; ++iter1)
		{
			Collision(*iter, *iter1, fDeltaTIme);
		}
	}

	m_CollisionList.clear();

}

bool CColliderManager::Collision(CObject* pScr, CObject* pDest, float fDeltaTIme)
{
	const list<CCollider*>* pSrcList = pScr->GetColliderList();
	const list<CCollider*>* pDestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator iterSrc;
	list<CCollider*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator iterDest;
	list<CCollider*>::const_iterator iterDestEnd = pDestList->end();

	bool bCollision = false;
	
	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc)
	{
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest)
		{
			if ((*iterSrc)->Collision(*iterDest))
			{
				bCollision = true;

				(*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

				//충돌목록에서 이전에 충돌된적이 없다면 처음 막충돌되었다는 의미이다
				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					//서로 상대방을 충동 목록으로 추가한다
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunciton(CS_ENTER, *iterDest, fDeltaTIme);
					(*iterDest)->CallFunciton(CS_ENTER, *iterSrc, fDeltaTIme);
				}
				//기존충돌된적이 있다면 계속 충동 상태인 것이다
				else
				{
					(*iterSrc)->CallFunciton(CS_STAY, *iterDest, fDeltaTIme);
					(*iterDest)->CallFunciton(CS_STAY, *iterSrc, fDeltaTIme);
				}

			}
			//현재 충돌이 안된 상태에서 이전에 충돌이 되고 있었다면 막 충돌상태에서 떨어젔다는 의미이다
			else if((*iterSrc)->CheckCollisionList(*iterDest))
			{
				//서로 충동리 안되므로 충돌목록에서 지워준다
				(*iterSrc)->EraseCollisionList((*iterDest));
				(*iterDest)->EraseCollisionList((*iterSrc));

				(*iterSrc)->CallFunciton(CS_LEAVE, *iterDest, fDeltaTIme);
				(*iterDest)->CallFunciton(CS_LEAVE, *iterSrc, fDeltaTIme);
			}
		}
	}

	return bCollision;
}

void CColliderManager::Clear()
{
	m_CollisionList.clear();
}
