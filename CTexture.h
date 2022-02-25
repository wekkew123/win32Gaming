#pragma once
#include "../CRef.h"

class CTexture :
	public CRef
{
private:
	friend class CRecourceManager;

private:
	CTexture();
	~CTexture();

private:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP m_hOldBitmap;
	BITMAP	m_tInfo;
	COLORREF m_ColorKey;
	bool	 m_bColorKeyEnable;

public:
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	void SetColorKey(COLORREF colorKey);
	COLORREF GetColorKey()	const
	{
		return m_ColorKey;
	}
	bool GetColorKeyEnable()	const
	{
		return m_bColorKeyEnable;
	}

public:
	bool LoadTexture(HINSTANCE hInst,HDC hdc,const string& strKey,
		const wchar_t* pFileName, const string& strPathKey=TEXTURE_PATH);
	HDC GetDc()	const
	{
		return m_hMemDC;
	}
};

