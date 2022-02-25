#include "CColliderPixel.h"
#include "../Object/CObject.h"
#include "CColliderSphere.h"
#include "CColliderRect.h"
#include "CColliderPoint.h"
#include "../Core/CPathManager.h"

CColliderPixel::CColliderPixel()
{
	m_eCollType = CT_PIXEL;
	m_iHieght = 0;
	m_iWidth = 0;
}

CColliderPixel::CColliderPixel(const CColliderPixel& coll)	:
	CCollider(coll)
{
	m_iHieght = coll.m_iHieght;
	m_iWidth = coll.m_iWidth;
}

CColliderPixel::~CColliderPixel()
{
}

bool CColliderPixel::SetPixelInfo(const char* pFileName, const string& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(strPathKey);
	string strPath;
	
	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	FILE* pFile = NULL;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (!pFile)
		return false;

	BITMAPFILEHEADER fh; //��Ʈ�� ������� ����
	BITMAPINFOHEADER ih; //��Ʈ�� ������� ����

	fread(&fh, sizeof(fh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	m_iWidth =ih.biWidth;
	m_iHieght = ih.biHeight;

	m_vecPixel.clear();

	m_vecPixel.resize(m_iWidth * m_iHieght);

	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	//�� �Ʒ��� ���������ش�
	
	PPIXEL pPixelArr = new PIXEL[m_iWidth];

	for (int i = 0; i < m_iHieght / 2; ++i) // 5ĭ�� ��� ��� �ϳ��� �ȹٲ㵵�ȴ� 
	{
		//���� �ε����� �弿 ������ �����صд�
		memcpy(pPixelArr, &m_vecPixel[i * m_iWidth], sizeof(PIXEL)*m_iWidth);
		memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHieght - i-1)*m_iWidth], sizeof(PIXEL) * m_iWidth);
		memcpy( &m_vecPixel[(m_iHieght - i - 1) * m_iWidth], pPixelArr,sizeof(PIXEL) * m_iWidth);

	}

	delete[]	pPixelArr;

	fclose(pFile);

	//fopen_s(&pFile, "Test.bmp", "wb");//���� �о ���
	//
	//if (pFile)
	//	return false;

	//fwrite(&fh,sizeof(fh), 1,pFile);
	//fwrite(&ih, sizeof(ih), 1, pFile);
	//fwrite(&m_vecPixel[0],sizeof(PIXEL),m_vecPixel.size(), pFile);
	//fclose(pFile);

	return true;
}

bool CColliderPixel::Init()
{
	return true;
}

void CColliderPixel::Input(float fDeltaTime)
{
}

int CColliderPixel::Update(float fDeltaTime)
{
	return 0;
}

int CColliderPixel::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CColliderPixel::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToPixel(((CColliderRect*)pDest)->GetWorldInfo(),
			m_vecPixel,m_iWidth,m_iHieght);
	case CT_POINT:
		return CollsionPixelToPoint(m_vecPixel, m_iWidth, m_iHieght, ((CColliderPoint*)pDest)->GetPoint());
	}

	return false;
}

void CColliderPixel::Render(HDC hdc, float fDeltaTime)
{
}

CColliderPixel* CColliderPixel::Clone()
{
	return new	CColliderPixel(*this);
}
