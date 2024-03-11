#include "Sr_Pr1.h"
#include "winres.h"

HINSTANCE hInst;
LPCWSTR g_lpszClassName = TEXT("sp_pr1_3_class");
LPCWSTR g_lpszAplicationTitle = TEXT("Sp lab 1.3");

ATOM				RegisterClassWnd(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(
	_In_ HINSTANCE	hInstance,
	_In_ HINSTANCE	hPrevInstance,
	_In_ LPSTR		lpszCmdLine,
	_In_ int		nCmdShow
) 
{
	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpszCmdLine);

	RegisterClassWnd(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

ATOM RegisterClassWnd(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEXW));
	wcex.cbSize = sizeof(WNDCLASSEXW);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;

	// IDI_ICON1 ÑÅÑÄ Ñ{ÑpÑ{ÑÄÑz-ÑÑÑÄ ÑÅÑÇÑyÑâÑyÑ~Ñu Ñ~Ñu ÑÅÑÄÑtÑáÑrÑpÑÑÑçÑrÑpÑuÑÑÑÉÑë
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));

	// Ñë ÑÅÑÇÑÄÑqÑÄÑrÑpÑ|, Ñ~ÑÄ Ñ{ÑpÑÉÑÑÑÄÑ}Ñ~ÑçÑu Ñ{ÑÖÑÇÑÉÑÄÑÇÑç Ñ~Ñu ÑsÑÇÑÖÑxÑëÑÑÑÉÑë
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszClassName = g_lpszClassName;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(g_lpszClassName, g_lpszAplicationTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}