// fract01.cpp : Defines the entry point for the application.
//

#include <math.h>

// Windows Header Files:
#include <windows.h>
#include <assert.h>
#include <stdio.h>

#include "resource.h"

#include	"showhighfield.h"
#include	"makeTerrain.h"
#include	"globals.h"
#include	"fractTools.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// TODEL
double	data[512*512];
HCURSOR cursorCross, cursorArrow, cursorWait;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)


{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	for (int i=0; i<512*512; i++)
		data[i] = 0;


	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FRACT01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_FRACT01);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
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
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_FRACT01);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_FRACT01;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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

	cursorCross = LoadCursor (NULL, IDC_CROSS);
	cursorArrow = LoadCursor (NULL, IDC_ARROW);
	cursorWait = LoadCursor (NULL, IDC_ARROW);

	assert (cursorCross && cursorArrow);

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, 650, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void	unsupported (HWND hWnd)
{
	TCHAR szUnsupported[MAX_LOADSTRING];

	LoadString(hInst, IDS_UNSUPPORTED, szUnsupported, MAX_LOADSTRING);
	MessageBox (hWnd, szUnsupported, "Error", MB_OK);
}
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
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
	RECT rt;
	int wmId, wmEvent,i,j;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	static RECT active;
	static HBITMAP bitmap;
	HPEN pen = CreatePen (PS_DOT, 1, RGB (255, 255, 255));
	static bool	draw = false;
	double	dim;
	char	str[100];
	double dat[128*128];

	static int xPos, yPos,x,y;

	switch (message) 
	{
		case WM_CREATE:
			int diff;

			GetClientRect(hWnd, &rt);

			// obliczanie obszaru zmiany kurasora			
			diff = rt.right - rt.left;
			assert (diff >= dataSizeX);
			active.left = (diff - dataSizeX)/2;

			diff = rt.bottom - rt.top;
			assert (diff >= dataSizeY);
			active.top = (diff - dataSizeY)/2;
			active.bottom=active.top+dataSizeY;
			active.right=active.left+dataSizeX;

			// obliczanie prostokata, gdzie bedzie potrzebna zmiana kursora
			srand (GetTickCount ());
			makeFractal (data, 0, 0, dataSizeX-1, dataSizeY-1, 0.7);

			break;

		case WM_SETCURSOR:
			break;

		case WM_LBUTTONDOWN:
			xPos = LOWORD(lParam);  // horizontal position of cursor 
			yPos = HIWORD(lParam);  // vertical position of cursor 

			xPos -= 64;
			yPos -= 64;

			if (xPos + 128 > active.right) xPos = active.right - 128;
			if (xPos < active.left) xPos = active.left;

			if (yPos + 128 > active.bottom) yPos = active.bottom - 128;
			if (yPos < active.top) yPos = active.top;

			hdc=GetDC (hWnd);

			SelectObject (hdc, pen);

			MoveToEx (hdc, xPos, yPos, NULL);
			LineTo (hdc, xPos, yPos+128);
			LineTo (hdc, xPos+128, yPos+128);
			LineTo (hdc, xPos+128, yPos);
			LineTo (hdc, xPos, yPos);

			ReleaseDC(hWnd, hdc);
			draw = true;
			break;

		case WM_LBUTTONUP:

			xPos -= active.left;
			yPos -= active.top;

			// liczenie wymiaru fraktalnego
			for (i=0; i<128; i++)
				for (j=0; j<128; j++)
					dat[i+j*128] = data[i+xPos + (j+yPos)*dataSizeX];

			dim = computeBCDim (dat, 128, 5);
			dim -= 0.3;
//			sprintf (str, "Fractal dimension: %f", (float)dim);
//			MessageBox (hWnd, str, "Result", MB_OK);

			zoom (data, xPos, yPos);	// zoom

			makeFractal (data, 0, 0, dataSizeX-1, dataSizeY-1,sqrt(3.0-dim));
			GetClientRect (hWnd, &rt);
			InvalidateRect (hWnd, &rt, true);
			draw=false;

			break;

		case WM_MOUSEMOVE:
			x = LOWORD(lParam);  // horizontal position of cursor 
			y = HIWORD(lParam);  // vertical position of cursor 

			if (draw)
			{
				SetCursor (cursorArrow);
				break;
			}

			if (x >= active.left && x <= active.right 
				&& y >= active.top && y <= active.bottom)
			{
				SetCursor (cursorCross);
			}
			else
				SetCursor (cursorArrow);

			break;
			
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case IDM_LOAD:
					unsupported (hWnd);
					break;
				case IDM_DIM:
					dim = computeBCDim(data,512, 5);
					sprintf (str, "Fractal dimension: %f", (float)dim);
					MessageBox (hWnd, str, "Result", MB_OK);
					break;
				case IDM_RANDMAP:
					for (i=0; i<dataSizeX*dataSizeY; i++)
						data[i] = 0.0;

					makeFractal (data, 0, 0, dataSizeX-1, dataSizeY-1,1,2);
					GetClientRect (hWnd, &rt);
					InvalidateRect (hWnd, &rt, true);
					break;

				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			GetClientRect(hWnd, &rt);


			showHighfield (hdc, rt, data);

			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
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

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
