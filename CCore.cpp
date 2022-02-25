#include "CCore.h"
#include "Scene/CSceneManager.h"
#include "Core/CTimer.h"
#include "Core/CPathManager.h"
#include "Resources/CRecourceManager.h"
#include "Resources/CTexture.h"
#include "Core/CCamera.h"
#include "Core/CInput.h"
#include "Colliber/CColliderManager.h"
#include "Object/CMouse.h"

CCore* CCore::m_pInst = NULL;
bool CCore::m_bLoop = true;

CCore::CCore()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//�޸� ���� ��üũ
    //_CrtSetBreakAlloc();//��ǥ�� ���ڷ� ������ �����κ����� �ٷ� �̵��Ѵ� 

#ifdef  _DEBUG
    //�ܼ�â�� ���������ִ� �Լ�
    AllocConsole();

#endif //  _DEBUG

}

CCore::~CCore()
{
    DESTROY_SINGLE(CTimer);
    DESTROY_SINGLE(CSceneManager);
    DESTROY_SINGLE(CPathManager);
    DESTROY_SINGLE(CRecourceManager);
    DESTROY_SINGLE(CCamera);
    DESTROY_SINGLE(CInput);
    DESTROY_SINGLE(CColliderManager);
    ReleaseDC(m_hWnd, m_hDc);

#ifdef  _DEBUG
    FreeConsole();

#endif //  _DEBUG
}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

    MyRegisterClass();

    //�ػ� ����
    m_tRs.iW = 1080;
    m_tRs.iH = 620;

    Create();

    //ȭ�� DC�� ����� �ش� 
    m_hDc = GetDC(m_hWnd);

    //Ÿ�̸Ӱ����� �ʱ�ȭ
    if (!GET_SINGLE(CTimer)->Init(m_hWnd))
        return false;

    //��ΰ����� �ʱ�ȭ
    if (!GET_SINGLE(CPathManager)->Init())
        return false;

    //���ҽ� ������ �ʱ�ȭ
    if (!GET_SINGLE(CRecourceManager)->Init(hInst, m_hDc))
        return false;

    //�Է°����� �ʱ�ȭ
    if (!GET_SINGLE(CInput)->Init(m_hWnd))
        return false;

    //ī�޶� ������ �ʱ�ȭ
    if(!GET_SINGLE(CCamera)->Init(POSITION(0.f,0.f),m_tRs,RESOLUTION(1920,1080)))
        return false;

    //�������� �ʱ�ȭ
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;


	return true;
}

int CCore::Run()
{
    MSG msg;

    while (m_bLoop)
    {
        if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CCore::Logic()
{
    //Ÿ�̸� ����
    GET_SINGLE(CTimer)->Update();
    
    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    Input(fDeltaTime);
    if (Update(fDeltaTime) == SC_CHANGE)
        return;
    if (LateUpdate(fDeltaTime) == SC_CHANGE)
        return;
    Collision(fDeltaTime);
    Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
    GET_SINGLE(CInput)->Update(fDeltaTime);

    GET_SINGLE(CSceneManager)->Input(fDeltaTime);
    GET_SINGLE(CCamera)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
    SCENE_CHANGE    sc;
    sc = GET_SINGLE(CSceneManager)->Update(fDeltaTime);
    GET_SINGLE(CCamera)->Update(fDeltaTime);
    return sc;
}

int CCore::LateUpdate(float fDeltaTime)
{
    SCENE_CHANGE    sc;
   sc = GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
    return sc;
}

void CCore::Collision(float fDeltaTIme)
{
    GET_SINGLE(CSceneManager)->Collision(fDeltaTIme);

    GET_SINGLE(CColliderManager)->Collision(fDeltaTIme);
}

void CCore::Render(float fDeltaTime)
{
    //������۸�
    CTexture* pBackBuffer = GET_SINGLE(CRecourceManager)->GetBackBuffer();

    GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDc(), fDeltaTime);//backbufferDC�� �׸��� 

    //������ ���콺�� �׸���
    CMouse* pMouse = GET_SINGLE(CInput)->GetMouse();

    pMouse->Render(pBackBuffer->GetDc(), fDeltaTime);

    BitBlt(m_hDc, 0, 0, m_tRs.iW, m_tRs.iW, pBackBuffer->GetDc(), 0, 0, SRCCOPY);//window ȭ�鿡 ���

    SAFE_RELLASE(pBackBuffer);
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CCore::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"AR13API";
    wcex.hIconSm = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
    m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }
    //���� ������ Ÿ��Ʋ�ٳ� �޴��� ������ �������� ũ�⸦ �����ش�
    RECT rc = { 0,0,m_tRs.iW,m_tRs.iH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    //������ ������ ũ��� ������ Ŭ���̾�Ʈ ������ ũ�⸦ ���ϴ� ũ��� ������� �Ѵ�
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}
LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    wchar_t temp[80];

    if (message == WM_PAINT)
    {
        hdc = BeginPaint(hWnd, &ps);
        ua_tcscpy_s(temp, L"hello world");
        TextOut(hdc, 50, 50, temp, 11);
        EndPaint(hWnd, &ps);
        return 0;
    }
    else if (message == WM_DESTROY) {
        m_bLoop = false;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);

    return LRESULT();
}

