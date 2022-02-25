#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <functional>
#include <conio.h>

using namespace std;

#include "resource.h"
#include "Macro.h"
#include "Types.h"
#include "Flag.h"

//��32���� �����ϴ� ���� ���̺귯�� 
#pragma comment(lib,"msimg32")//�ڵ�� ��ũ�Ŵ� ���

#define PI 3.141592
#define GRAVITY 0.98f

//Path Key
#define ROOT_PATH	"RootPath"
#define TEXTURE_PATH	"TexturePath"

template<typename T>
void Safe_Delete_VecList(T& p)
{
	 typename T::iterator iter;
	 typename T::iterator iterEnd = p.end();

	 for (iter = p.begin(); iter != iterEnd; ++iter)
	 {
		 SAFE_DELETE((*iter));
	 }

	 p.clear();
}
template<typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELLASE((*iter));
	}

	p.clear();
}
template<typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELLASE(iter->second);
	}

	p.clear();
}
template<typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();
}