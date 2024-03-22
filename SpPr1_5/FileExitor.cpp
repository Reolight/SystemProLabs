#include "FileEditor.h"
#pragma once

using namespace std;

void OnEditorOk(HWND hwnd) {
    EndDialog(hwnd, 0);
}

void OnEditorCancel(HWND hwnd) {
    EndDialog(hwnd, 0);
}

bool OnEditorInit(HWND hdlg, HWND hwnd, LPARAM lp) {
    return 1;
}

void OnFileEditorCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
    switch (id)
    {
    case IDOK:          OnEditorOk(hwnd); break;
    case IDCANCEL:      OnEditorCancel(hwnd); break;
    default:
        break;
    }
}

INT_PTR CALLBACK FileEditorProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, OnEditorInit);
        HANDLE_MSG(hDlg, WM_COMMAND, OnFileEditorCommand);
    }

    return (INT_PTR)FALSE;
}