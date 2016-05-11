#include "main.h"
#include "statusBar.h"
#include "resources.h"

//���p�O���[�o���ϐ�
HWND hWnd;
MSG msg;
const DWORD FPS = 60;
DWORD fps;
BOOL ENDFLAG = FALSE;
HINSTANCE hInst;
HDC WndHDC;
HDC BackHDC;

//����Wait�֐�
void Wait(DWORD waitTime)
{
	DWORD startTime = timeGetTime();

	do
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (waitTime > 0)
			Sleep(1);

	} while (timeGetTime() < waitTime + startTime);
}

//FPS�J�E���g
void FPScount(DWORD *fps)
{
	static DWORD beforeTime = timeGetTime();
	DWORD nowTime = timeGetTime();
	static DWORD fpsCtr = 0;

	if (nowTime - beforeTime >= 1000)
	{
		//������
		beforeTime = nowTime;
		*fps = fpsCtr;
		fpsCtr = 0;
	}

	fpsCtr++;
}

//�Q�[�����C���֐�
void GameMain()
{
	DWORD startTime, endTime, passTime;

	//timeGetTime()�̐��x����
	TIMECAPS Caps;
	timeGetDevCaps(&Caps, sizeof(TIMECAPS));
	timeBeginPeriod(Caps.wPeriodMin);

	//���C�����[�v
	while (!ENDFLAG)
	{
		startTime = timeGetTime();

		//�����ɏ���������
		//!�����ɏ���������

		endTime = timeGetTime();
		passTime = endTime - startTime;
		(1000 / FPS > passTime) ? Wait(1000 / FPS - passTime) : Wait(0);
		FPScount(&fps);
	}
	timeEndPeriod(Caps.wPeriodMin); //�㏈��
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, 0, 0L);
			break;
		case IDM_HELP:
			break;
		}
		break;
	case WM_CREATE:
		CreateMyStatus(hWnd, hInst);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, _T("�I�����܂����H"), _T("�m�F"), MB_YESNO) == IDNO)
			return 0;

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		ENDFLAG = TRUE;
		return 0;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd)
{
	WNDCLASSEX wc;

	//���E�B���h�E�N���X�̏���ݒ�
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MENU";
	wc.lpszClassName = TEXT("Default Class Name");

	//�E�B���h�E�N���X��o�^����
	if (RegisterClassEx(&wc) == 0)
		return 1;

	//���E�B���h�E�̕\���ʒu��ݒ肷��
	int x = (GetSystemMetrics(SM_CXSCREEN) - WinWID) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - WinHEI) / 2;

	//���E�B���h�E���쐬����
	hWnd = CreateWindow(wc.lpszClassName, TEXT("DesktopMemo"), WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, x, y, WinWID, WinHEI, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
		return 1;

	//�E�B���h�E��\������
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//�ϐ��錾
	hInstance = hInst;
	WndHDC = GetDC(hWnd);

	//�Q�[�����C���֐�
	GameMain();

	//�J��
	ReleaseDC(hWnd, WndHDC);

	return 0;
}