#pragma once

#include "main.h"

#define ID_EDIT 100
#define ID_EDITBUTTON1 800
#define ID_EDITBUTTON2 801
#define ID_EDITBUTTON3 802
#define ID_FREEBOXBUTTON1 803
#define ID_FREEBOXBUTTON2 804

void createEditbox(HWND hWnd, HINSTANCE hInst);
void createEditbutton(HWND hWnd);
int createClip(HWND hWnd, char copyText[10]);
