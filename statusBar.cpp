#include "statusBar.h"

HWND hStatus;

HWND CreateMyStatus(HWND hWnd, HINSTANCE hInst)
{
	//コモンコントロールのdllを初期化
	InitCommonControls();

	hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)ID_STATUS, hInst, NULL);
	SendMessage(hStatus, SB_SIMPLE, TRUE, 0L);
	return hStatus;
}