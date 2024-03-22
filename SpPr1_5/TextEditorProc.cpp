#include "TextEditorProc.h"

using namespace std;

vector<wchar_t*> savedText;
int savedCount = 0;
const size_t CLIPBOARD_SIZE = 0x200;
wchar_t clipboard[CLIPBOARD_SIZE]{ 0 };

vector<array<wchar_t, CLIPBOARD_SIZE>> textList;

bool AddString(HWND hList, const LPCWSTR string) {
    return SendMessage(hList, LB_ADDSTRING, CLIPBOARD_SIZE, (LPARAM)string);
}

void ShowError(HWND hwnd, LPCWSTR text, LPCWSTR caption) {
    MessageBox(hwnd, text, caption, MB_OK | MB_ICONERROR);
}

bool onEditorInit(HWND hDlg, HWND hWnd, LPARAM lParam) {
    if (savedCount == 0) return 1;
    Button_Enable(GetDlgItem(hDlg, IDC_ADDTEXT), false);
    HWND hList = GetDlgItem(hDlg, IDC_LIST1);
    
    for (const auto& str : textList) {
        LPCWSTR lpcwstr(str.data());
        AddString(hList, lpcwstr);
    }

    return 1;
}

void OnReadClicked(HWND hwnd) {
    HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);
    SendMessage(hEdit, WM_GETTEXT, CLIPBOARD_SIZE, (LPARAM)clipboard);
    Button_Enable(GetDlgItem(hwnd, IDC_ADDTEXT), true);
}

void OnAddClicked(HWND hwnd, HWND hwndCtl) {
    if (AddString(GetDlgItem(hwnd, IDC_LIST1), clipboard)) {
        ShowError(hwnd, _T("ÑSÑuÑ{ÑÉÑÑ Ñ~Ñu ÑtÑÄÑqÑpÑrÑ|ÑuÑ~"), _T("ÑKÑpÑ{ÑpÑë-ÑÑÑÄ Ñ~ÑuÑÅÑÄÑ~ÑëÑÑÑ~ÑpÑë ÑÄÑäÑyÑqÑ{Ñp"));
        return;
    }

    Button_Enable(hwndCtl, false);
}

void OnOk(HWND hwnd) {
    HWND hList = GetDlgItem(hwnd, IDC_LIST1);
    auto count = SendMessage(hList, LB_GETCOUNT, 0, 0);
    if (count == LB_ERR) {
        ShowError(hwnd, _T("ÑNÑu Ñ}ÑÄÑsÑÖ ÑÅÑÄÑ|ÑÖÑâÑyÑÑÑé Ñ{ÑÄÑ|ÑyÑâÑuÑÉÑÑÑrÑÄ ÑèÑ|ÑuÑ}ÑuÑ~ÑÑÑÄÑr Ñr ÑÉÑÅÑyÑÉÑ{Ñu"), _T("ÑOÑäÑyÑqÑ{Ñp"));
        return;
    }

    array<wchar_t, CLIPBOARD_SIZE> buffer;
    for (int i = savedCount; i < count; i++) {
        if (!SendMessage(hList, LB_GETTEXT, i, (LPARAM)buffer.data())) 
            throw new exception("No text for you :<");
        array<wchar_t, CLIPBOARD_SIZE> temp;
        textList.push_back(move(buffer));
    }

    savedCount = count;
    EndDialog(hwnd, 0);
}

void OnCancel(HWND hwnd) {
    EndDialog(hwnd, 0);
}

void OnEditorCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
    switch (id)
    {
    case IDC_READTEXT:  OnReadClicked(hwnd); break;
    case IDC_ADDTEXT:   OnAddClicked(hwnd, hwndCtl); break;
    case IDOK:          OnOk(hwnd); break;
    case IDCANCEL:      OnCancel(hwnd); break;
    default:
        break;
    }
}

INT_PTR CALLBACK TextStrProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, onEditorInit);
        HANDLE_MSG(hDlg, WM_COMMAND, OnEditorCommand);
    }

    return (INT_PTR)FALSE;
}