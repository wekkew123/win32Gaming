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
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//메모리 누수 릭체크
    //_CrtSetBreakAlloc();//좌표을 인자로 넣으면 문제부분으로 바로 이동한다 

#ifdef  _DEBUG
    //콘솔창을 생성시켜주는 함수
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

    //해상도 설정
    m_tRs.iW = 1080;
    m_tRs.iH = 620;

    Create();

    //화면 DC를 만들어 준다 
    m_hDc = GetDC(m_hWnd);

    //타이머관리자 초기화
    if (!GET_SINGLE(CTimer)->Init(m_hWnd))
        return false;

    //경로관리자 초기화
    if (!GET_SINGLE(CPathManager)->Init())
        return false;

    //리소스 관리자 초기화
    if (!GET_SINGLE(CRecourceManager)->Init(hInst, m_hDc))
        return false;

    //입력관리자 초기화
    if (!GET_SINGLE(CInput)->Init(m_hWnd))
        return false;

    //카메라 관리자 초기화
    if(!GET_SINGLE(CCamera)->Init(POSITION(0.f,0.f),m_tRs,RESOLUTION(1920,1080)))
        return false;

    //장면관리자 초기화
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
    //타이머 갱신
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
    //더블버퍼링
    CTexture* pBackBuffer = GET_SINGLE(CRecourceManager)->GetBackBuffer();

    GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDc(), fDeltaTime);//backbufferDC에 그린다 

    //마지막 마우스를 그린다
    CMouse* pMouse = GET_SINGLE(CInput)->GetMouse();

    pMouse->Render(pBackBuffer->GetDc(), fDeltaTime);

    BitBlt(m_hDc, 0, 0, m_tRs.iW, m_tRs.iW, pBackBuffer->GetDc(), 0, 0, SRCCOPY);//window 화면에 출력

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
    //실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해준다
    RECT rc = { 0,0,m_tRs.iW,m_tRs.iH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    //위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야 한다
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

