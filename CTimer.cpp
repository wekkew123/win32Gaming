#include "CTimer.h"

DEFINITION_SINGLE(CTimer)

CTimer::CTimer() :
	m_fTimeScale(1.f)
{
}
CTimer::~CTimer()
{
}

bool CTimer::Init(HWND hwnd)
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_wHnd = hwnd;
	m_fDeltaTime = 0.f;
	m_fFPS = 0;
	m_fFPSTime = 0.f;
	m_iFrame = 0;

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER tTIme;
	QueryPerformanceCounter(&tTIme);

	m_fDeltaTime = (tTIme.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart;

	m_tTime = tTIme;

	m_fFPSTime += m_fDeltaTime;
	++m_iFrame;

	if(m_fFPSTime >= 1.f)
	{
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;

//#ifdef _DEBUG

		char strFPS[64] = {};
		sprintf_s(strFPS, "FPS : %.f\n", m_fFPS);
		//_cprintf(strFPS);//콘솔창에서 출력

		SetWindowTextA(m_wHnd, strFPS);//윈도우 타이틀바 출력 char용
		//OutputDebugStringA(strFPS);//비쥬얼 스튜비오 아래칸에 출력
//#endif // DEBUG
	}
}
