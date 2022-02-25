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
		//_cprintf(strFPS);//�ܼ�â���� ���

		SetWindowTextA(m_wHnd, strFPS);//������ Ÿ��Ʋ�� ��� char��
		//OutputDebugStringA(strFPS);//����� ��Ʃ��� �Ʒ�ĭ�� ���
//#endif // DEBUG
	}
}
