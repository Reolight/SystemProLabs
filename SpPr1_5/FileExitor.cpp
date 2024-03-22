#include "FileEditor.h"

using namespace std;

void OnOk(HWND hwnd) {
    EndDialog(hwnd, 0);
}

void OnCancel(HWND hwnd) {
    EndDialog(hwnd, 0);
}

bool OnEditorInit(HWND hdlg, HWND hwnd, LPARAM lp) {
    return 1;
}

void OnEditorCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
    switch (id)
    {
    case IDOK:          OnOk(hwnd); break;
    case IDCANCEL:      OnCancel(hwnd); break;
    default:
        break;
    }
}

INT_PTR CALLBACK FileEditorProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, OnEditorInit);
        HANDLE_MSG(hDlg, WM_COMMAND, OnEditorCommand);
    }

    return (INT_PTR)FALSE;
}