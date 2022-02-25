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

	//������Ʈ�� �浹ó���� �Ѵ�
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

				//�浹��Ͽ��� ������ �浹������ ���ٸ� ó�� ���浹�Ǿ��ٴ� �ǹ��̴�
				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					//���� ������ �浿 ������� �߰��Ѵ�
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunciton(CS_ENTER, *iterDest, fDeltaTIme);
					(*iterDest)->CallFunciton(CS_ENTER, *iterSrc, fDeltaTIme);
				}
				//�����浹������ �ִٸ� ��� �浿 ������ ���̴�
				else
				{
					(*iterSrc)->CallFunciton(CS_STAY, *iterDest, fDeltaTIme);
					(*iterDest)->CallFunciton(CS_STAY, *iterSrc, fDeltaTIme);
				}

			}
			//���� �浹�� �ȵ� ���¿��� ������ �浹�� �ǰ� �־��ٸ� �� �浹���¿��� ����ٴ� �ǹ��̴�
			else if((*iterSrc)->CheckCollisionList(*iterDest))
			{
				//���� �浿�� �ȵǹǷ� �浹��Ͽ��� �����ش�
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
