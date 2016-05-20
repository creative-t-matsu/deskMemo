#include "dialogBox.h"
#include "resources.h"

int dlgCounter;

//---関数プロトタイプ
void setText(char inputText[10]);

LRESULT CALLBACK MyDlgProc(HWND hDlgWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	char inputText[100];
	LONG lSize;

	switch (msg)
	{
	case WM_INITDIALOG:
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case IDOK:
			GetDlgItemText(hDlgWnd, IDC_MAINBOX, inputText, sizeof(inputText));
			setText(inputText);
			EndDialog(hDlgWnd, IDOK);
			break;
		default:
			return FALSE;
		}
	case WM_KEYDOWN:
		if (wp == VK_SEPARATOR)
			SendMessage(hDlgWnd, IDOK, 0, 0L);

		return FALSE;
	default:
		return FALSE;
	}
	return TRUE;
}

void setText(char inputText[10])
{
	switch (dlgCounter)
	{
	case 0:
		SetWindowText(hEdit1, inputText);
		dlgCounter++;
		break;
	case 1:
		SetWindowText(hEdit2, inputText);
		dlgCounter++;
		break;
	case 2:
		SetWindowText(hEdit3, inputText);
		dlgCounter = 0;
		break;
	default:
		break;
	}
}