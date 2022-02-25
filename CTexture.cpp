#include "CTexture.h"
#include "../Core/CPathManager.h"

CTexture::CTexture()	:
	m_hMemDC(NULL),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255,0,255))
{
}

CTexture::~CTexture()
{
	//기존에 지정되어 있던 도구를 다시 지정해준다
	SelectObject(m_hMemDC, m_hOldBitmap);

	//Bitmap을 지워준다
	DeleteObject(m_hBitmap);

	//DC를 지워준다
	DeleteDC(m_hMemDC);
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
	m_bColorKeyEnable = true;
}

bool CTexture::LoadTexture(HINSTANCE hInst,HDC hdc,const string& strKey,
	const wchar_t* pFileName, const string& strPathKey)
{
	//메모리 DC를 만들어준다
	m_hMemDC = CreateCompatibleDC(hdc);//hdc용 메모리 DC가 만들어진다 

	//전체 경로를 만들어준다
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)//문자열 포인터가 NULL를 갖고 있으면 아래와같이 데입시 크레쉬가난다
		strPath = pPath;

	strPath += pFileName;
	
	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//위에서 만들어준 비트맵 도구를 DC에 지정한다
	//지정할떄 반환되는 값은 DC에 기본으로 지정되어 있던
	//도구가 반환된다
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);//비트맵 정보를 가져온다 


	return true;
}
