#include "FileEditor.h"

using namespace std;

const int fclpsize = 0x10000;
wchar_t fileClipboard[fclpsize];

void OnEditorOk(HWND hwnd) {
    EndDialog(hwnd, 0);
}

void OnEditorCancel(HWND hwnd) {
    EndDialog(hwnd, 0);
}

bool OnEditorInit(HWND hdlg, HWND hwnd, LPARAM lp) {
    EnableWindow(GetDlgItem(hdlg, IDC_LOAD_BUTTON), false);
    EnableWindow(GetDlgItem(hdlg, IDC_SAVE_BUTTON), false);
    return 1;
}

void Denied(HWND hwnd, LPCWSTR text) {
    MessageBox(hwnd, text, _T("Denied"), MB_OK);
}

void OnBrowseButton(HWND hwnd) {
    OPENFILENAME fileName = { sizeof(fileName), };
    wchar_t fnameBuffer[0x0400];
    fnameBuffer[0] = 0;
    fileName.lpstrFile = fnameBuffer;
    fileName.nMaxFile = 0x03ff;
    fileName.lpstrTitle = _T("ÑBÑçÑqÑuÑÇÑyÑÑÑu ÑÑÑuÑ{ÑÉÑÑÑÄÑrÑçÑz ÑÜÑpÑzÑ|");
    fileName.lpstrDefExt = _T("txt");
    fileName.hwndOwner = hwnd;
    fileName.lpstrInitialDir = NULL;
    fileName.lpstrFilter = _T("Text files\0*.txt\0\0");
    if (!GetOpenFileName(&fileName))
        return Denied(hwnd, _T("ÑUÑpÑzÑ| Ñ~Ñu ÑrÑçÑqÑÇÑpÑ~"));
    DWORD fileAttr = GetFileAttributes(fileName.lpstrFile);
    if (fileAttr == INVALID_FILE_ATTRIBUTES || fileAttr & FILE_ATTRIBUTE_DIRECTORY)
        return Denied(hwnd, _T("ÑBÑçÑqÑÇÑpÑ~ Ñ~Ñu ÑÜÑpÑzÑ|"));
    HWND browseEdit = GetDlgItem(hwnd, IDC_EDIT_BROWSE);
    SendMessage(browseEdit, WM_SETTEXT, 0, (LPARAM)fileName.lpstrFile);
    EnableWindow(GetDlgItem(hwnd, IDC_LOAD_BUTTON), true);
}

void OnLoadButton(HWND hwnd) {
    wchar_t b[0x400];
    SendDlgItemMessage(hwnd, IDC_EDIT_BROWSE, WM_GETTEXT, 0x400, (LPARAM)b);
    HANDLE hFile = CreateFile(b, GENERIC_READ, 0, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (!ReadFile(hFile, fileClipboard, fclpsize, NULL, NULL)) {
        CloseHandle(hFile);
        return Denied(hwnd, _T("ÑUÑpÑzÑ| Ñ~Ñu ÑÅÑÇÑÄÑâÑyÑÑÑpÑ~"));
    }
     
    SendDlgItemMessage(hwnd, IDC_FILE_TEXTEDIT, WM_SETTEXT, 0, (LPARAM)fileClipboard);
    EnableWindow(GetDlgItem(hwnd, IDC_SAVE_FILE), true);
    CloseHandle(hFile);
}

void OnSaveButton(HWND hwnd) {
    wchar_t b[0x400];
    SendDlgItemMessage(hwnd, IDC_EDIT_BROWSE, WM_GETTEXT, 0, (LPARAM)b);
    SendDlgItemMessage(hwnd, IDC_FILE_TEXTEDIT, WM_GETTEXT, fclpsize, (LPARAM)fileClipboard);
    HANDLE hfile = CreateFile(b, GENERIC_WRITE, 0, NULL, CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD writtenBytes;
    WriteFile(hfile, fileClipboard, fclpsize, &writtenBytes, NULL);
    CloseHandle(hfile);
}

void OnFileEditorCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
    switch (id)
    {
    case IDOK:              OnEditorOk(hwnd);       break;
    case IDCANCEL:          OnEditorCancel(hwnd);   break;
    case IDC_BROWSE_BUTTON: OnBrowseButton(hwnd);   break;
    case IDC_LOAD_BUTTON:   OnLoadButton(hwnd);     break;
    case IDC_SAVE_BUTTON:   OnSaveButton(hwnd);     break;
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