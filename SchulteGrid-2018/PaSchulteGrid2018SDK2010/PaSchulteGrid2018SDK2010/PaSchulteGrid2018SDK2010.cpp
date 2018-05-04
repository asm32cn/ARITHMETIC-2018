// PaSchulteGrid2018SDK2010.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PaSchulteGrid2018SDK2010.h"
#include <stdlib.h>
//#include <stdio.h>
#include <time.h>

#define MAX_LOADSTRING 100
#define COUNT 25

typedef struct{
	int n;
	int next;
}StructSource;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

StructSource A_objSource[COUNT] = {0};
INT A_nMatrix[COUNT];
WCHAR A_szMatrix[COUNT][6] = {0};

HFONT font;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void PA_DoInitData();
void PA_DoPaint(HWND hWnd, HDC hdc);
HFONT PA_CreateFont(HDC hdc, LPCTSTR face, int height, int angle);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	PA_DoInitData();

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PASCHULTEGRID2018SDK2010, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PASCHULTEGRID2018SDK2010));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PASCHULTEGRID2018SDK2010));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PASCHULTEGRID2018SDK2010);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		PA_DoPaint(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void PA_DoInitData(){
	srand((UINT)time(NULL));

	for(int i = 0; i < COUNT; i++){
		A_objSource[i].n = A_objSource[i].next = i + 1;
	}

	int current = 0;
	int prev = COUNT - 1;
	A_objSource[prev].next = current;
	for(int i = 0; i < COUNT; i++){
		int r = rand() % (COUNT - i);
		for(int n = 0; n < r; n++){
			prev = current;
			current = A_objSource[current].next;
		}

		A_nMatrix[i] = A_objSource[current].n;
		wsprintfW(A_szMatrix[i], _T("%d"), A_nMatrix[i]);

		A_objSource[prev].next = A_objSource[current].next;
		A_objSource[current].next = -1;
		current = A_objSource[prev].next;
	}
}

void PA_DoPaint(HWND hWnd, HDC hdc){
	RECT rect;
	GetClientRect(hWnd, &rect);
	int w = rect.right;
	int h = rect.bottom;
	int m_nCellW = (w > h ? h : w) / 6;
	int m_nStartX = (w - m_nCellW * 5) / 2;
	int m_nStartY = (h - m_nCellW * 5) / 2;
	int m_nGridW = m_nCellW * 5;

	int m_nFontSizePt = (int)(m_nCellW * 0.8);
	int m_nFontOffsetY = m_nCellW / 10;
	int m_nFontOffsetX1 = m_nCellW / 10 * 3;
	int m_nFontOffsetX2 = m_nCellW / 10;

	HFONT m_pFontText = PA_CreateFont(hdc, _T("Arial Black"), m_nFontSizePt, 0);

	HFONT m_pOldFont = (HFONT)SelectObject(hdc, m_pFontText);

	int m_nOffsetX = m_nStartX;
	int m_nOffsetY = m_nStartY;
	for(int i = 0; i < 6; i++){
		if(i<5){
			for(int j = 0; j < 5; j++){
				int n = j * 5 + i;
				int m_nFontOffsetX = A_nMatrix[n] < 10 ? m_nFontOffsetX1 : m_nFontOffsetX2;
				int m_nFontOfssetY1 = m_nStartY + m_nCellW * j + m_nFontOffsetY;
				TextOut(hdc, m_nOffsetX + m_nFontOffsetX, m_nFontOfssetY1, A_szMatrix[n], 6);
			}
		}
		MoveToEx(hdc, m_nStartX, m_nOffsetY, NULL);
		LineTo(hdc, m_nStartX + m_nGridW, m_nOffsetY);

		MoveToEx(hdc, m_nOffsetX, m_nStartY, NULL);
		LineTo(hdc, m_nOffsetX, m_nStartY + m_nGridW);


		m_nOffsetX += m_nCellW;
		m_nOffsetY += m_nCellW;
	}

	SelectObject(hdc, m_pOldFont);
	DeleteObject(m_pFontText);
}


HFONT PA_CreateFont(HDC hdc, LPCTSTR face, int height, int angle)
{
    HFONT hFont;
    hFont = CreateFont(height,  //字体的逻辑高度
        0,  //逻辑平均字符宽度
        angle,  //与水平线的角度
        0,  //基线方位角度
        FW_REGULAR,  //字形：常规
        FALSE,  //字形：斜体
        FALSE,  //字形：下划线
        FALSE,  //字形：粗体
        GB2312_CHARSET,  //字符集
        OUT_DEFAULT_PRECIS,  //输出精度
        CLIP_DEFAULT_PRECIS,  //剪截精度
        PROOF_QUALITY,  //输出品质
        FIXED_PITCH | FF_MODERN, //倾斜度
        face);  //字体
    return hFont;
}
