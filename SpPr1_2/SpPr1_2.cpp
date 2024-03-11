// SpPr1_2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SpPr1_2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

LPCWSTR g_lpszClassName = TEXT("sp_pr1_2_class");
LPCWSTR g_lpszAplicationTitle = TEXT("ÑCÑ|ÑpÑrÑ~ÑÄÑu ÑÄÑ{Ñ~ÑÄ ÑÅÑÇÑyÑ|ÑÄÑwÑuÑ~ÑyÑë. ÑPÑÇÑÄÑsÑÇÑpÑ}ÑyÑÉÑÑ ÑMÑuÑ|ÑéÑ~ÑyÑ{ÑÄÑr ÑQÑÄÑÉÑÑÑyÑÉÑ|ÑpÑr");
LPCWSTR g_lpszDestroyMessage = TEXT("ÑPÑÄÑÉÑÑÑÖÑÅÑyÑ|ÑÄ ÑÉÑÄÑÄÑqÑãÑuÑ~ÑyÑu WM_DESTROY, ÑyÑx ÑÄÑqÑÇÑpÑqÑÄÑÑÑâÑyÑ{Ñp Ñ{ÑÄÑÑÑÄÑÇÑÄÑsÑÄ Ñy"
    "ÑrÑçÑÅÑÄÑ|Ñ~ÑuÑ~ ÑtÑpÑ~Ñ~ÑçÑz ÑrÑçÑrÑÄÑt.ÑRÑÄÑÄÑqÑãÑuÑ~ÑyÑu ÑÅÑÄÑÉÑÑÑÖÑÅÑyÑ|ÑÄ Ñr ÑÉÑrÑëÑxÑy ÑÉ ÑÇÑpÑxÑÇÑÖÑäÑuÑ~ÑyÑuÑ}"
    "ÑÄÑ{Ñ~Ñp ÑÅÑÇÑyÑ|ÑÄÑwÑuÑ~ÑyÑë");

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPPR12));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPPR12));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(127, 0, 127));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPPR12);
    wcex.lpszClassName  = g_lpszClassName;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
constexpr auto IDC_SAVE_BUTTON = 150;
constexpr auto IDC_ADD_BUTTON = 151;
constexpr auto IDC_EXIT_BUTTON = 152;
constexpr auto IDC_EDIT = 153;
constexpr auto IDC_LISTBOX = 154;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hExitButton;
    static HWND hSaveButton;
    static HWND hAddButton;
    static HWND hEdit;
    static HWND hListBox;

    switch (message)
    {
    case WM_COMMAND: {
        auto wmId = LOWORD(wParam);
        auto wmEvent = HIWORD(wParam);
        static WCHAR textBuffer[500];

        switch (wmId)
        {
        case IDC_EXIT_BUTTON:{
            MessageBox(hWnd, TEXT("ÑNÑpÑwÑpÑÑÑp Ñ{Ñ~ÑÄÑÅÑ{Ñp ÑrÑçÑáÑÄÑtÑp"), TEXT("ÑBÑçÑáÑÄÑt"), MB_OK | MB_ICONINFORMATION);
            PostQuitMessage(0);
        }
        break;
        case IDC_SAVE_BUTTON: {
            int cch = SendMessage(hEdit, WM_GETTEXT, (WPARAM)500, (LPARAM)textBuffer);
            if (!cch) {
                MessageBox(hWnd, TEXT("SendMessage ÑrÑuÑÇÑ~ÑÖÑ| 0"), TEXT("SendMessage"), MB_OK | MB_ICONWARNING);
                return 0;
            }

            wchar_t bf[500] = { 0 };
            SYSTEMTIME st; GetLocalTime(&st);
            swprintf_s(bf, TEXT("(ÑBÑÇÑuÑ}Ñë: %d:%d:%d)"), st.wHour, st.wMinute, st.wSecond);
            lstrcat(textBuffer, _T(" ")); lstrcat(textBuffer, bf);
            MessageBox(hWnd, textBuffer, _T("ÑRÑÄÑtÑuÑÇÑwÑyÑ}ÑÄÑu ÑqÑÖÑÜÑuÑÇÑp"), MB_OK | MB_ICONINFORMATION);
        }
        break;

        case IDC_ADD_BUTTON: {
            int index = SendMessage(hListBox, LB_ADDSTRING, (WPARAM)0, (LPARAM)textBuffer);
            if (index == LB_ERR) MessageBox(hWnd, _T("ÑBÑÄÑxÑ~ÑyÑ{Ñ|Ñp ÑÄÑäÑyÑqÑ{Ñp ÑÅÑÇÑy ÑtÑÄÑqÑpÑrÑ|ÑuÑ~ÑyÑy ÑÉÑÑÑÇÑÄÑ{Ñy Ñr ÑÉÑÅÑyÑÉÑÄÑ{"), _T("ÑOÑäÑyÑqÑ{Ñp"), MB_OK | MB_ICONERROR);
        }
        break;

        default:
            DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }
    }
    break;

    case WM_CREATE: {
            MessageBox(hWnd, TEXT("ÑOÑqÑÇÑpÑqÑÄÑÑÑ{Ñp Ñ{ÑÄÑ}ÑpÑ~ÑtÑç WM_CREATE"), TEXT("WM_CREATE"), MB_OK);

            RECT wRect; GetClientRect(hWnd, &wRect);
            int w = wRect.right - wRect.left, h = wRect.bottom - wRect.top;
            hEdit = CreateWindowEx(0L, TEXT("EDIT"), TEXT("ÑQÑuÑtÑpÑ{ÑÑÑÄÑÇ"), WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE,
                20, 100, 400, 40, hWnd, (HMENU)IDC_EDIT, hInst, NULL);
            hListBox = CreateWindowEx(0L, TEXT("Listbox"), TEXT("ÑRÑÅÑyÑÉÑÄÑ{"), WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE,
                440, 100, 450, 400, hWnd, (HMENU)IDC_LISTBOX, hInst, NULL);
            hSaveButton = CreateWindowEx(0, TEXT("button"), TEXT("ÑB ÑqÑÖÑÜÑuÑÇ"), WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE,
                140, 160, 160, 40, hWnd, (HMENU)IDC_SAVE_BUTTON, hInst, NULL);
            hAddButton = CreateWindowEx(0, TEXT("button"), TEXT("ÑB ÑÉÑÅÑyÑÉÑÄÑ{"), WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE,
                140, 220, 160, 40, hWnd, (HMENU)IDC_ADD_BUTTON, hInst, NULL);
            hExitButton = CreateWindowEx(0, TEXT("button"), TEXT("ÑBÑçÑzÑÑÑy"), WS_TABSTOP | WS_VISIBLE | WS_CHILD,
                140, 280, 160, 40, hWnd, (HMENU)IDC_EXIT_BUTTON, hInst, NULL); 
            return (hEdit && hListBox && hSaveButton && hAddButton && hExitButton);
        }
        break;
    case WM_LBUTTONDOWN: {
            HDC hdc = GetDC(hWnd);
            int x = LOWORD(lParam), y = HIWORD(lParam);
            // TextOut(hdc, x, y, str, lstrlen(str));
            RECT rect;
            GetClientRect(hWnd, &rect);
            wchar_t buf[40];
            int cCount = swprintf_s(buf, L"ÑNÑpÑwÑpÑÑÑp ÑLÑKÑM: %d:%d", x, y);
            DrawText(hdc, buf, cCount, &rect, DT_BOTTOM);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            wchar_t buffer[50];
            int charCount = swprintf_s(buffer, L"(%d:%d), (%d:%d)", clientRect.left, clientRect.top, clientRect.right, clientRect.bottom);
            DrawText(hdc, buffer, charCount, &clientRect, DT_CENTER | DT_LEFT);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        MessageBox(hWnd, g_lpszDestroyMessage, TEXT("ÑBÑçÑáÑÄÑt ÑyÑx ÑÅÑÇÑyÑ|ÑÄÑwÑuÑ~ÑyÑë"), MB_OK);
        PostQuitMessage(5);
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
