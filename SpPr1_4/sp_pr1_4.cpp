#include "framework.h"
#include "resource1.h"
#include "windowsx.h"

HINSTANCE hInst;
HWND hWnd;
LPCWSTR g_lpszClassName = TEXT("sp_pr1_4_class");
LPCWSTR g_lpszAplicationTitle = TEXT("Sp lab 1.4");

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
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));


	while (GetMessage( & msg, nullptr, 0, 0))
	{
		if (TranslateAccelerator(hWnd, hAccel, &msg))
			continue;
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

	hWnd = CreateWindowW(g_lpszClassName, g_lpszAplicationTitle, WS_OVERLAPPEDWINDOW,
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
HMENU GetMenuByID(HMENU menu, UINT_PTR id);
HMENU GetMenuByID(HMENU menu, UINT_PTR id) {
	int menuCount = GetMenuItemCount(menu);
	for (int i = 0; i < menuCount; i++) {
		if (GetMenuItemID(menu, i) == id) return menu;
		auto submenu = GetSubMenu(menu, i);
		if (submenu != NULL) return GetMenuByID(submenu, id);
	}

	return NULL;
}

HMENU GetMenuByID(HWND hWnd, UINT_PTR id) {
	auto menu = GetMenu(hWnd);
	return GetMenuByID(menu, id);
}

LRESULT CALLBACK CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int id = LOWORD(wParam);
	auto mainMenu = GetMenu(hWnd);
	switch (id)
	{
	case IDM_NEWFILE:
		ShowMsgBox(hWnd, TEXT("„B„„q„‚„p„~ „„…„~„{„„ 'New'"), TEXT("„M„u„~„ „U„p„z„|"));
		EnableMenuItem(mainMenu, IDM_HIGHLIGHT, MF_ENABLED);
		break;
	case IDM_OPENFILE:
		ShowMsgBox(hWnd, TEXT("„B„„q„‚„p„~ „„…„~„{„„ 'Open'"), TEXT("„M„u„~„ „U„p„z„|"));
		break;
	case IDM_EXIT:
		ShowMsgBox(hWnd, TEXT("„B„„q„‚„p„~ „„…„~„{„„ 'Exit'"), TEXT("„M„u„~„ „U„p„z„|"));
		PostQuitMessage(0);
		break;

	case IDM_HIGHLIGHT:
		EnableMenuItem(mainMenu, IDM_COPY, MF_ENABLED);
		EnableMenuItem(mainMenu, IDM_CUT, MF_ENABLED);
		break;
	case IDM_CUT:
		EnableMenuItem(mainMenu, IDM_PASTE, MF_ENABLED);
		break;
	case IDM_COPY:
		EnableMenuItem(mainMenu, IDM_PASTE, MF_ENABLED);
		break;
	case IDM_PASTE:
		break;
	case 666: /// „H„p„{„‚„„„„Ž „t„€„{„…„}„u„~„„
		EnableMenuItem(mainMenu, IDM_HIGHLIGHT, MF_DISABLED);
		EnableMenuItem(mainMenu, IDM_COPY, MF_DISABLED);
		EnableMenuItem(mainMenu, IDM_PASTE, MF_DISABLED);
		EnableMenuItem(mainMenu, IDM_CUT, MF_DISABLED);
		break;
	case IDM_HELP:
		ShowMsgBox(hWnd, TEXT("„B„„q„‚„p„~ „„…„~„{„„ 'Help'\n\nCopilot „r „„€„}„€„‹„Ž"), TEXT("„M„u„~„ „R„„‚„p„r„{„p"));
		break;
	case IDM_ABOUT:
		ShowMsgBox(hWnd, TEXT("„B„„q„‚„p„~ „„…„~„{„„ 'About'\nAbout: „„„„€ „„‚„€„ƒ„„„€ „„‚„€„s„‚„p„}„}„p, „{„€„„„€„‚„p„‘ „t„u„|„p„u„„ „~„y„‰„u„s„€ „t„|„‘ „„„€„s„€, „‰„„„€„q„ „t„u„|„p„„„Ž „~„y„‰„u„s„€"), TEXT("„M„u„~„ „R„„‚„p„r„{„p"));
		break;
	default:
		break;
	}

	return 0;
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lParam) {
	HMENU hFileMenu = GetSubMenu(GetMenu(hWnd), 0);
	AppendMenu(hFileMenu, MF_ENABLED, 666, TEXT("„H„p„{„‚„„„„Ž „t„€„{„…„}„u„~„„"));
	return 1;
}

void OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos) {
	TrackPopupMenu(GetSubMenu(GetMenu(hWnd), 1),
		TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON | TPM_VERPOSANIMATION,
		xPos, yPos, 0, hWnd, NULL);
}


void OnMenuItemHover(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags) {
	TCHAR buf[300];
	int size;
	size = LoadString(hInst, item, buf, 300);
	HDC hdc1 = GetDC(hWnd);
	RECT rc; GetClientRect(hWnd, &rc);
	FillRect(hdc1, &rc, CreateSolidBrush(RGB(0, 0, 0)));
	TextOut(hdc1, rc.left + 25, rc.bottom - 30, buf, lstrlen(buf));
	ReleaseDC(hWnd, hdc1);
}

void OnDestroy(HWND hd) {
	PostQuitMessage(0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_CONTEXTMENU, OnContextMenu);
		HANDLE_MSG(hWnd, WM_MENUSELECT, OnMenuItemHover);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		
	case WM_COMMAND:
		CmdProc(hWnd, message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}