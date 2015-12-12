#include <windows.h>
#include"LinesRotation\RotationDetection.h"
#include"Convex-Hull\Graham\GrahamConvexHulCalcl.h"
#include"Convex-Hull\Gift-Wrapping\GiftWrappingConvexHullCalc.h"
#include<string>

using namespace std;

#define CALCULATE_CONVEX_HULL_GIFT_WRAPPING 1
#define CALCULATE_CONVEX_HULL_GRAHAM_SCAN 2
#define QUIT 3

//---------------------------------------------------------------------------
HWND hWnd;
LPCTSTR ClsName = "Computational geometry";
LPCTSTR WindowCaption = "Computational geometry";
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG         Msg;
	WNDCLASSEX  WndClsEx;

	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = WndProc;
	WndClsEx.cbClsExtra = NULL;
	WndClsEx.cbWndExtra = NULL;
	WndClsEx.hInstance = hInstance;
	WndClsEx.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClsEx.lpszMenuName = NULL;
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	RegisterClassEx(&WndClsEx);

	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		ClsName,
		WindowCaption,
		WS_OVERLAPPEDWINDOW,
		100,
		120,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;	
	static int StartX, StartY;
	static int EndX, EndY;
	static int clickCounter = 0;

	switch (Msg)
	{
	case WM_CREATE:
		HMENU hMenubar;
		HMENU hMenu;

		hMenubar = CreateMenu();
		hMenu = CreateMenu();

		AppendMenuW(hMenu, MF_STRING, CALCULATE_CONVEX_HULL_GIFT_WRAPPING, L"&Calculate ConvexHull Gift-Wrapping");
		AppendMenuW(hMenu, MF_STRING, CALCULATE_CONVEX_HULL_GRAHAM_SCAN, L"&Calculate ConvexHull GrahamScan");
		AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenuW(hMenu, MF_STRING, QUIT, L"&Quit");

		AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Tools");
		SetMenu(hWnd, hMenubar);
		return 0;

	case WM_LBUTTONDOWN:
		{
			hDC = GetDC(hWnd);
			StartX = LOWORD(lParam);
			StartY = HIWORD(lParam);

			EndX = LOWORD(lParam);
			EndY = HIWORD(lParam);

			
			GWC->AddPoint(StartX, StartY);
			GCH->AddPoint(StartX, StartY);
			Ellipse(hDC, StartX - 5, StartY - 5, StartX + 5, StartY + 5);	
			
			OutputDebugStringA(std::to_string(clickCounter).c_str());
			
			SetROP2(hDC, R2_XORPEN);
			clickCounter++;

			ReleaseDC(hWnd, hDC);
		}

		return 0;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case CALCULATE_CONVEX_HULL_GIFT_WRAPPING:
				hDC = GetDC(hWnd);
				GWC->SetHDC(hDC);
				GWC->CalculateConvexHullPoints();
				break;
			case CALCULATE_CONVEX_HULL_GRAHAM_SCAN:
				hDC = GetDC(hWnd);
				GCH->SetHDC(hDC);
				GCH->CalculateConvexHullPoints();
				break;

			case QUIT:
				PostQuitMessage(0);
				break;

			break;
		}

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return TRUE;
}
//---------------------------------------------------------------------------