#pragma once
#include "../Game.h"

class CRecourceManager
{	
private:
	unordered_map<string, class CTexture*>	m_mapTexture;
	HINSTANCE m_hInst;
	HDC		  m_hDc;
	class CTexture* m_pBackBuffer;

public:
	class CTexture* GetBackBuffer()	const;
public:
	bool Init(HINSTANCE hInst,HDC hdc);
	class CTexture* LoadTexture(const string& strKey, const wchar_t* pFileName,
		const string& strPathKey=TEXTURE_PATH);
	class CTexture* FindTexture(const string& strKey);

	DECLARE_SINGLE(CRecourceManager)
};

