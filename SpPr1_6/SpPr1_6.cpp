// SpPr1_6.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SpPr1_6.h"

#define MAX_LOADSTRING 100

#ifdef UNICODE
#define sstring std::wstringstream;
#else 
#define sstring std::stringstream;
#endif

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
POINT lastPoint;
PAINTSTRUCT paintStruct;
int g_pressedCount = 0;

enum ShiftDirection
{
    Up,
    Down,
    Left,
    Right
};

bool TraceMode = 0;
const int ShiftValuePx = 8;
const HBRUSH HBrush = CreateSolidBrush(RGB(0x7f, 0, 0xff));

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

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPPR16, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPPR16));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPPR16));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPPR16);
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

bool OnCreate(HWND hwnd, LPCREATESTRUCT createStruct) {
    paintStruct.rcPaint.left = 80;
    paintStruct.rcPaint.right = 280;
    paintStruct.rcPaint.top = 80;
    paintStruct.rcPaint.bottom = 280;
    return TRUE;
}

bool isLastPointResetted() {
    return lastPoint.x == 0 && lastPoint.y == 0;
}

void ResetLastPoint() {
    lastPoint.x = 0;
    lastPoint.y = 0;
}

void SetLastPoint(int x, int y) {
    lastPoint.x = x;
    lastPoint.y = y;
}

void TooLongToDrawTriangle(HDC hdc) {
    LPCWSTR lpcwWontRotateTriangle = _T("Not a math lesson to rotate triangle");
    std::wostringstream wsstr;
    wsstr << _T("Dec num: ") << g_pressedCount / 10 << _T(". Triangle example:");
    std::wstring wstr = wsstr.str();
    TextOut(hdc, 5, 80, lpcwWontRotateTriangle, wcslen(lpcwWontRotateTriangle));
    TextOut(hdc, 5, 100, wstr.c_str(), wstr.length());
    POINT triangleVertices[3]{ {4, 150}, {16, 200}, {28, 155} };
    Polygon(hdc, triangleVertices, 3);
}

bool PaintStructContains(int x, int y) {
    return (x >= paintStruct.rcPaint.left &&
        x <= paintStruct.rcPaint.right &&
        y >= paintStruct.rcPaint.top &&
        y <= paintStruct.rcPaint.bottom);
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags) {
    if ((keyFlags != MK_LBUTTON || !PaintStructContains(x,y)) && !isLastPointResetted()) 
        return ResetLastPoint();
    if (!TraceMode) return;

    if (keyFlags != MK_LBUTTON || !PaintStructContains(x, y))
        return;
    HDC hdc = GetDC(hwnd);
    LOGBRUSH lgbrush;
    lgbrush.lbStyle = BS_SOLID; lgbrush.lbColor = RGB(0x7f, 0, 0xff);
    HPEN hpen = ExtCreatePen(PS_SOLID, 2, &lgbrush, 0, NULL);
    SelectPen(hdc, hpen);
    POINT p; GetCursorPos(&p);
    if (isLastPointResetted()) {
        g_pressedCount++;
        return SetLastPoint(x, y);
    }

    MoveToEx(hdc, lastPoint.x, lastPoint.y, &p);
    LineTo(hdc, x, y);

    if (g_pressedCount % 10 == 0) TooLongToDrawTriangle(hdc);
    SetLastPoint(x, y);


    ReleaseDC(hwnd, hdc);
}

void TraceOn() { TraceMode = true; }
void TraceOff() { TraceMode = false; }

void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
    if (vk == VK_F2) TraceOn();
    if (vk == VK_F3) TraceOff();

    std::wstringstream wsstr;
    wsstr << _T("Toggled: ");
    if (TraceMode) wsstr << "true";
    else wsstr << "false";

    std::wstring wstr = wsstr.str();
    HDC hdc = GetDC(hwnd);
    TextOut(hdc, 5, 50, wstr.c_str(), wstr.length());
    ReleaseDC(hwnd, hdc);
}

void ShiftPx(HWND hwnd, ShiftDirection direction) {
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    switch (direction)
    {
    case Up:
        if (paintStruct.rcPaint.top - ShiftValuePx < 0) break;
        paintStruct.rcPaint.bottom -= ShiftValuePx;
        paintStruct.rcPaint.top -= ShiftValuePx;
        break;
    case Down:
        if (paintStruct.rcPaint.bottom + ShiftValuePx > clientRect.bottom) break;
        paintStruct.rcPaint.bottom += ShiftValuePx;
        paintStruct.rcPaint.top += ShiftValuePx;
        break;
    case Left:
        if (paintStruct.rcPaint.left - ShiftValuePx < 0) break;
        paintStruct.rcPaint.left -= ShiftValuePx;
        paintStruct.rcPaint.right-= ShiftValuePx;
        break;
    case Right:
        if (paintStruct.rcPaint.right + ShiftValuePx > clientRect.right) break;
        paintStruct.rcPaint.left += ShiftValuePx;
        paintStruct.rcPaint.right += ShiftValuePx;
        break;
    default:
        break;
    }
}

void Denied(HWND hwnd, LPCWSTR str) {
    MessageBox(hwnd, str, _T("Denied"), MB_OK);
}

void OnChar(HWND hwnd, TCHAR ch, int cRepeat) {
    switch (ch)
    {
    case 'z': ShiftPx(hwnd, Left); break;
    case 'x': ShiftPx(hwnd, Right); break;
    case 'c': ShiftPx(hwnd, Up); break;
    case 'v': ShiftPx(hwnd, Down); break;
    default: return;
    }

    HDC hdc = GetDC(hwnd);
    RECT clr; GetClientRect(hwnd, &clr);
    std::wstringstream sstr;
    sstr << _T("X: ") << paintStruct.rcPaint.left << _T(", Y: ") << paintStruct.rcPaint.top;
    std::wstring str(sstr.str());
    FillRect(hdc, &clr, (HBRUSH)(COLOR_WINDOW + 1));
    FillRect(hdc, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));
    TextOut(hdc, 6, 20, str.c_str(), str.length());
    ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
        HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyDown);
        HANDLE_MSG(hWnd, WM_CHAR, OnChar);
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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
        }
        break;
    case WM_PAINT:
        {
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
