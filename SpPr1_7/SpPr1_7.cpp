// SpPr1_7.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SpPr1_7.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TaskFig(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    TaskImg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPPR17, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPPR17));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPPR17));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPPR17);
    wcex.lpszClassName  = szWindowClass;
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void PrintMyName(HWND hwnd, HDC hdc) {
    HFONT hfont = CreateFont(36, 0, 0, 0, FW_BOLD, TRUE, FALSE, FALSE, RUSSIAN_CHARSET,
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, _T("Arial"));
    SelectObject(hdc, hfont);
    SetTextColor(hdc, (RGB(0, 0, 0x7f)));
    LPCWSTR namesurname = _T("ÑMÑuÑ|ÑéÑ~ÑyÑ{ÑÄÑr ÑQÑÄÑÉÑÑÑyÑÉÑ|ÑpÑr Ñ@Ñ|ÑuÑ{ÑÉÑpÑ~ÑtÑÇÑÄÑrÑyÑâ");
    TextOut(hdc, 0, 50, namesurname, wcslen(namesurname));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_TASKFIG:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIAL1B), hWnd, TaskFig);
                break;
            case IDM_TASKIMG:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALIMG), hWnd, TaskImg);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            PrintMyName(hWnd, hdc);
            EndPaint(hWnd, &ps);
        }
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

INT_PTR CALLBACK TaskFig(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_PAINT:
    {
        HDC hdc = GetDC(hDlg);
        HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0xaf));
        COLORREF fillclr = RGB(0, 0xaf, 0);
        
        HBRUSH hbrush = CreateSolidBrush(fillclr);              // Ñ~ÑuÑÑ ÑÉÑÑÑyÑ|Ñë ÑÉ ÑÑÑÄÑâÑ{ÑpÑ}Ñy
        SelectObject(hdc, hpen);

        HBRUSH hcirc1 = CreateHatchBrush(HS_CROSS, fillclr);
        SelectObject(hdc, hcirc1);
        Ellipse(hdc, 20, 20, 60, 60);

        HBRUSH hcirc2 = CreateHatchBrush(HS_DIAGCROSS, fillclr);
        SelectObject(hdc, hcirc2);
        Ellipse(hdc, 120, 60, 80, 20);
        
        SelectObject(hdc, hbrush);
        Rectangle(hdc, 40, 20, 100, 60);

        // Arc(hdc, 20, 20, 60, 60, 40, 20, 40, 60);
        // Arc(hdc, 120, 60, 80, 20, 100, 60, 100, 20);

        DeleteObject(hpen);
        DeleteObject(hbrush);
        DeleteObject(hcirc1);
        DeleteObject(hcirc2);

        ReleaseDC(hDlg, hdc);
    }
    break;
    case WM_INITDIALOG: return (INT_PTR)TRUE;

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

INT_PTR CALLBACK TaskImg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_PAINT:
    {
        // ÑXÑÑÑÄ Ñë ÑtÑuÑ|ÑpÑê Ñ~Ñu ÑÑÑpÑ{?
        BITMAP bmp;
        HDC hdc = GetDC(hDlg);
        auto hdcMem = CreateCompatibleDC(hdc);

        auto hbmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_PNG2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
        auto h_old = SelectObject(hdcMem, hbmp);

        GetObject(hbmp, sizeof(BITMAP), &bmp);
        BitBlt(hdc, 0, 0, 128, 128, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, h_old);
        DeleteDC(hdcMem);
        ReleaseDC(hDlg, hdc);
    }
        break;
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