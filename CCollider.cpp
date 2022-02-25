#include "CCollider.h"
#include "../Object/CObject.h"
#include "../CMath.h"

CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider& coll)
{
	*this = coll;

	m_FunctList[CS_ENTER].clear();
	m_FunctList[CS_STAY].clear();
	m_FunctList[CS_LEAVE].clear();
}

CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EraseCollisionList(this);
	}
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDest)
{
	return false;
}


void CCollider::Render(HDC hdc, float fDeltaTime)
{
}

bool CCollider::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
{
	if (src.l > dest.r)
		return false;
	else if (src.r < dest.l)
		return false;

	else if (src.t > dest.b)
		return false;

	else if (src.b < dest.t)
		return false;

	return true;
}

bool CCollider::CollisionRectToSphere(const RECTANGLE& src, const SPHERE& dest)
{
	//���� ������ x��ǥ�� �簢���� ���ο��� �ȿ� �ִ���
	//���� ������ y��ǥ�� �簢���� ���� �����ȿ� �ִ��� üũ�Ѵ�
	//���� �ϳ��� �´ٸ� �簢���� ��,�Ʒ�, ��,�� ���� �ȿ� �����Ѵٴ� ���̴�
	if ((dest.tCenter.x >= src.l && dest.tCenter.x <= src.r) || (dest.tCenter.y >= src.t && dest.tCenter.y <= src.b))
	{
		RECTANGLE tRc = src;
		tRc.l -= dest.fRadius;
		tRc.r += dest.fRadius;
		tRc.t -= dest.fRadius;
		tRc.b += dest.fRadius;
		
		if (dest.tCenter.x < tRc.l)
			return false;
		else if (dest.tCenter.x > tRc.r)
			return false;
		else if (dest.tCenter.y < tRc.t)
			return false;
		else if (dest.tCenter.y > tRc.b)
			return false;
		
		return true;
	}

	//�簢���� 4���� ���� �ϳ��� ���ȿ� ���� ��� �浹�̴� 
	POSITION	tPos[4];
	tPos[0] = POSITION(src.l, src.t);
	tPos[1] = POSITION(src.r, src.t);
	tPos[2] = POSITION(src.l, src.b);
	tPos[3] = POSITION(src.r, src.b);

	for (int i = 0; i < 4; ++i)
	{
		float fDist = CMath::GetDistance(tPos[i], dest.tCenter);

		if (fDist <= dest.fRadius)
			return true;
	}

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE& src, const SPHERE& dest)
{
	float fDist = CMath::GetDistance(src.tCenter, dest.tCenter);

	return fDist <= src.fRadius + dest.fRadius;
}

bool CCollider::CollisionRectToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel,
	int iWidith, int iHeight)
{
	m_tHitPoint.x = -1;
	m_tHitPoint.y = -1;

	int iStartX, iEndX;
	int iStartY, iEndY;

	iStartX = src.l < 0 ? 0 : src.l;
	iEndX = src.r >= iWidith ? iWidith - 1 : src.r;

	iStartY = src.t < 0 ? 0 : src.t;
	iEndY = src.b >= iWidith ? iHeight - 1 : src.b;

	for (int i = iStartY; i <= iEndY; ++i)
	{
		for (int j = iStartX; j <= iEndX; ++j)
		{
			int idx = i * iWidith + j;
			const PIXEL& pixel = vecPixel[idx];
			if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
			{
				m_tHitPoint.x = j;
				m_tHitPoint.y = i;
				return true;
			}
		}
	}

	return false;
}

bool CCollider::CollisionSphereToPixel(const SPHERE& src, const vector<PIXEL>& vecPixel, 
	int iWidith, int iHeight)
{
	return false;
}

bool CCollider::CollisionRectToPoint(const RECTANGLE& src, const POSITION& dest)
{
	if (dest.x < src.l)
		return false;

	else if (dest.x > src.r)
		return false;

	else if (dest.y < src.t)
		return false;

	else if (dest.y > src.b)
		return false;

	return true;
}

bool CCollider::CollisionSphereToPoint(const SPHERE& scr, const POSITION& dest)
{
	return CMath::GetDistance(scr.tCenter, dest) <= scr.fRadius;
}

bool CCollider::CollsionPixelToPoint(const vector<PIXEL>& vecPixel, int iWidth, int iHeight, const POSITION& dest)
{
	if (dest.y < 0 || dest.x < 0 || dest.x >= iWidth || dest.y >= iHeight)
		return false;
	int idx = (int)dest.y * iWidth + (int)dest.x;
	const PIXEL& pixel = vecPixel[idx];
	if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
	{
		m_tHitPoint = dest;
		return true;
	}

	return false;
}
