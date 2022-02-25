#pragma once
#include "../Game.h"

class CPathManager
{
private:
	unordered_map<string, wstring>	m_mapPath;
	char m_strPath[MAX_PATH];

public:
	bool Init();
	bool CreatePath(const string& strKey, const wchar_t* pPath,
		const string& strBaseKey = ROOT_PATH);
	const wchar_t* FindPath(const string& strKey);
	const char* FindPathMultiByte(const string& strKey);


	DECLARE_SINGLE(CPathManager) 

};

