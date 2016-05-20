#include "editBox.h"

HWND hEdit1, hEdit2, hEdit3, freeBox;

void createEditbox(HWND hWnd, HINSTANCE hInst)
{
	LPCTSTR FREE_TEXT = _T("自由欄。'文章クリア'で文章を削除出来ます。");

	hEdit1 = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | WS_HSCROLL, 10, 10, 265, 80, hWnd, (HMENU)ID_EDIT, hInst, NULL);
	hEdit2 = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | WS_HSCROLL, 10, 160, 265, 80, hWnd, (HMENU)ID_EDIT, hInst, NULL);
	hEdit3 = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | WS_HSCROLL, 10, 310, 265, 80, hWnd, (HMENU)ID_EDIT, hInst, NULL);
	freeBox = CreateWindow("EDIT", FREE_TEXT, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | WS_HSCROLL, 10, 460, 265, 80, hWnd, (HMENU)ID_EDIT, hInst, NULL);
}

void createEditbutton(HWND hWnd)
{
	HWND hEditbutton1, hEditbutton2, hEditbutton3, freeBoxbutton1, freeBoxbutton2;

	LPCTSTR TEXT_COPY = _T("文章をコピー");
	LPCTSTR TEXT_CLEAR = _T("文章をクリア");

	hEditbutton1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT_COPY,WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,10, 95, 130, 30,hWnd, (HMENU)ID_EDITBUTTON1,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	hEditbutton2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT_COPY, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 245, 130, 30, hWnd, (HMENU)ID_EDITBUTTON2, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	hEditbutton3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT_COPY, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 395, 130, 30, hWnd, (HMENU)ID_EDITBUTTON3, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	freeBoxbutton1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT_COPY, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 545, 130, 30, hWnd, (HMENU)ID_FREEBOXBUTTON1, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	freeBoxbutton2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT_CLEAR, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 145, 545, 130, 30, hWnd, (HMENU)ID_FREEBOXBUTTON2, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
}

int createClip(HWND hWnd,char copyText[10])
{
	HGLOBAL hg;
	PTSTR strMem;

	if (!OpenClipboard(hWnd))
		return 0;

	EmptyClipboard();

	hg = GlobalAlloc(GHND | GMEM_SHARE, 128);
	strMem = (PTSTR)GlobalLock(hg);
	lstrcpy(strMem, copyText);
	GlobalUnlock(hg);

	SetClipboardData(CF_TEXT, hg);

	CloseClipboard();

	return 0;
}