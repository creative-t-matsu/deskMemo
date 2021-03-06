#include "main.h"
#include "statusBar.h"
#include "resources.h"
#include "dialogBox.h"
#include "bmp.h"
#include "editBox.h"

//マクロ定義
#define HOT_KEY_ID 100001
#define ID_MYTIMER 100002

//共用グローバル変数
HWND hWnd;
MSG msg;
const DWORD FPS = 60;
DWORD fps;
BOOL ENDFLAG = FALSE;
HINSTANCE hInst;
HDC WndHDC;
HDC BackHDC;

char copyText[10];

//自作Wait関数
void Wait(DWORD waitTime)
{
	DWORD startTime = timeGetTime();

	do
	{
		//メッセージ処理
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (waitTime > 0)
			Sleep(1);

	} while (timeGetTime() < waitTime + startTime);
}

//FPSカウント
void FPScount(DWORD *fps)
{
	static DWORD beforeTime = timeGetTime();
	DWORD nowTime = timeGetTime();
	static DWORD fpsCtr = 0;

	if (nowTime - beforeTime >= 1000)
	{
		//初期化
		beforeTime = nowTime;
		*fps = fpsCtr;
		fpsCtr = 0;
	}

	fpsCtr++;
}

//ゲームメイン関数
void GameMain()
{
	DWORD startTime, endTime, passTime;

	//timeGetTime()の精度向上
	TIMECAPS Caps;
	timeGetDevCaps(&Caps, sizeof(TIMECAPS));
	timeBeginPeriod(Caps.wPeriodMin);

	//dlgCounterの初期化
	dlgCounter = 0;

	//メインループ
	while (!ENDFLAG)
	{
		startTime = timeGetTime();

		//此処に処理を書く
		//!此処に処理を書く

		endTime = timeGetTime();
		passTime = endTime - startTime;
		(1000 / FPS > passTime) ? Wait(1000 / FPS - passTime) : Wait(0);
		FPScount(&fps);
	}
	timeEndPeriod(Caps.wPeriodMin); //後処理
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	SYSTEMTIME sTime;
	char str[256];
	char *str_org = "現在の時刻は%2d時%2d分%2d秒です";


	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, 0, 0L);
			break;
		case IDM_HELP:
			break;
		case ID_EDITBUTTON1:
			GetWindowText(hEdit1, copyText, sizeof(copyText));
			createClip(hWnd, copyText);
			break;
		case ID_EDITBUTTON2:
			GetWindowText(hEdit2, copyText, sizeof(copyText));
			createClip(hWnd, copyText);
			break;
		case ID_EDITBUTTON3:
			GetWindowText(hEdit3, copyText, sizeof(copyText));
			createClip(hWnd, copyText);
			break;
		case ID_FREEBOXBUTTON1:
			GetWindowText(freeBox, copyText, sizeof(copyText));
			createClip(hWnd, copyText);
			break;
		case ID_FREEBOXBUTTON2:
			SetWindowText(freeBox, NULL);
			break;
		}
		break;
	case WM_CREATE:
		SetWindowPos(hWnd, HWND_TOPMOST,200, 200, WID, HEI, SWP_NOREPOSITION);
		SetTimer(hWnd, ID_MYTIMER, 300, NULL);
		SetForegroundWindow(hWnd);
		RegisterHotKey(hWnd, HOT_KEY_ID, MOD_CONTROL, '1');
		createEditbox(hWnd, hInst);
		createEditbutton(hWnd);
		CreateMyStatus(hWnd, hInst);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, _T("終了しますか？"), _T("確認"), MB_YESNO) == IDNO)
			return 0;

		break;
	case WM_HOTKEY:
		switch (wp)
		{
		case HOT_KEY_ID:
			DialogBox(hInst, "MAINDLG", hWnd, (DLGPROC)MyDlgProc);
			break;
		}
		break;
	case WM_TIMER:
		GetLocalTime(&sTime);
		wsprintf(str, str_org, sTime.wHour, sTime.wMinute, sTime.wSecond);
		SendMessage(hStatus, SB_SETTEXT, 255 | 0, (WPARAM)(LPSTR)str);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, ID_MYTIMER);
		UnregisterHotKey(hWnd, HOT_KEY_ID);
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

	//※ウィンドウクラスの情報を設定
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)CreateHatchBrush(HS_BDIAGONAL, 0XFF << 14);
	wc.lpszMenuName = "IDD_MENU01";
	wc.lpszClassName = TEXT("Default Class Name");

	//ウィンドウクラスを登録する
	if (RegisterClassEx(&wc) == 0)
		return 1;

	//※ウィンドウの表示位置を設定する
	int x = (GetSystemMetrics(SM_CXSCREEN) - WinWID) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - WinHEI) / 2;

	//※ウィンドウを作成する
	hWnd = CreateWindow(wc.lpszClassName, TEXT("DesktopMemo"), WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, x, y, WinWID, WinHEI, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
		return 1;

	//ウィンドウを表示する
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//変数宣言
	hInstance = hInst;
	WndHDC = GetDC(hWnd);

	//ゲームメイン関数
	GameMain();

	//開放
	ReleaseDC(hWnd, WndHDC);

	return 0;
}