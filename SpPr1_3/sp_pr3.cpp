#include "framework.h"
#include "resource1.h"

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

	
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszClassName = g_lpszClassName;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	HWND hWnd = CreateWindowW(g_lpszClassName, g_lpszAplicationTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, hMenu, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void ShowMsgBox(HWND hWnd, LPCWSTR text, LPCWSTR menuName) {
	MessageBox(hWnd, text, menuName, MB_OK);
}

LRESULT CALLBACK CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int id = LOWORD(wParam);
	switch (id)
	{
	case IDM_NEWFILE:
		ShowMsgBox(hWnd, TEXT("ÑBÑçÑqÑÇÑpÑ~ ÑÅÑÖÑ~Ñ{ÑÑ 'New'"), TEXT("ÑMÑuÑ~Ñê ÑUÑpÑzÑ|"));
		break;
	case IDM_OPENFILE:
		ShowMsgBox(hWnd, TEXT("ÑBÑçÑqÑÇÑpÑ~ ÑÅÑÖÑ~Ñ{ÑÑ 'Open'"), TEXT("ÑMÑuÑ~Ñê ÑUÑpÑzÑ|"));
		break;
	case IDM_EXIT:
		ShowMsgBox(hWnd, TEXT("ÑBÑçÑqÑÇÑpÑ~ ÑÅÑÖÑ~Ñ{ÑÑ 'Exit'"), TEXT("ÑMÑuÑ~Ñê ÑUÑpÑzÑ|"));
		PostQuitMessage(0);
		break;

	case IDM_HIGHLIGHT:
	case IDM_CUT:
	case IDM_COPY:
	case IDM_PASTE:
		break;

	case IDM_HELP:
		ShowMsgBox(hWnd, TEXT("ÑBÑçÑqÑÇÑpÑ~ ÑÅÑÖÑ~Ñ{ÑÑ 'Help'\n\nCopilot Ñr ÑÅÑÄÑ}ÑÄÑãÑé"), TEXT("ÑMÑuÑ~Ñê ÑRÑÅÑÇÑpÑrÑ{Ñp"));
		break;
	case IDM_ABOUT:
		ShowMsgBox(hWnd, TEXT("ÑBÑçÑqÑÇÑpÑ~ ÑÅÑÖÑ~Ñ{ÑÑ 'About'\nAbout: ÑèÑÑÑÄ ÑÅÑÇÑÄÑÉÑÑÑÄ ÑÅÑÇÑÄÑsÑÇÑpÑ}Ñ}Ñp, Ñ{ÑÄÑÑÑÄÑÇÑpÑë ÑtÑuÑ|ÑpÑuÑÑ Ñ~ÑyÑâÑuÑsÑÄ ÑtÑ|Ñë ÑÑÑÄÑsÑÄ, ÑâÑÑÑÄÑqÑç ÑtÑuÑ|ÑpÑÑÑé Ñ~ÑyÑâÑuÑsÑÄ"), TEXT("ÑMÑuÑ~Ñê ÑRÑÅÑÇÑpÑrÑ{Ñp"));
		break;
	default:
		break;
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		CmdProc(hWnd, message, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}