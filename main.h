#pragma once
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Comctl32.lib")

//インクルードファイル
#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <commctrl.h>

//定数
const int WID = 300;
const int HEI = 800;
const int WinWID = WID + GetSystemMetrics(SM_CXDLGFRAME) * 2;
const int WinHEI = HEI + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
extern HWND hEdit1, hEdit2, hEdit3, freeBox;
extern int dlgCounter;
extern HWND hStatus;
