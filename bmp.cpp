#include "bmp.h"

HDC LoadBmpFile(HDC hdc, LPCTSTR fileName)
{
	HBITMAP hbmp;
	HDC hdcLocal;//作業用ハンドル

	hbmp = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hdcLocal = CreateCompatibleDC(hdc);
	SelectObject(hdcLocal, hbmp);
	DeleteObject(hbmp);

	return hdcLocal;
}