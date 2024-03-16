#include "TextEditorProc.h"

#define COMMAND_HANDLE(hwnd, id, fn)    \
    case (id): return fn(hwnd)

using namespace std;

vector<LPCWSTR> savedText;
int savedCount = 0;
wchar_t clipboard[0xFF];

vector<LPCWSTR> GetSavedStringList() {
    return savedText;   
}

bool AddString(HWND hList, LPCWSTR string) {
    return SendMessage(hList, LB_ADDSTRING, 0xFF, (LPARAM)string);
}

void ShowError(HWND hwnd, LPCWSTR text, LPCWSTR caption) {
    MessageBox(hwnd, text, caption, MB_OK | MB_ICONERROR);
}

bool onEditorInit(HWND hDlg, HWND hWnd, LPARAM lParam) {
    if (savedCount == 0) return 1;
    Button_Enable(GetDlgItem(hDlg, IDC_ADDTEXT), false);
    HWND hList = GetDlgItem(hDlg, IDC_LIST1);
    for (int i = 0; i < savedCount; i++) {
        if (!AddString(hList, savedText.at(i))) throw new exception("Text wasn't inserted");
    }

    return 1;
}

void OnReadClicked(HWND hwnd) {
    GetDlgItemText(hwnd, IDC_EDIT1, clipboard, 0xff);
    MessageBox(hwnd, clipboard, _T("„R„{„€„„y„‚„€„r„p„~„€"), MB_OK | MB_ICONINFORMATION);
}

void OnAddClicked(HWND hwnd, HWND hwndCtl) {
    if (AddString(GetDlgItem(hwnd, IDC_LIST1), clipboard)) {
        ShowError(hwnd, _T("„S„u„{„ƒ„„ „~„u „t„€„q„p„r„|„u„~"), _T("„K„p„{„p„‘-„„„€ „~„u„„€„~„‘„„„~„p„‘ „€„Š„y„q„{„p"));
        return;
    }

    // Button_Enable(hwndCtl, false);
}

void OnOk(HWND hwnd) {
    HWND hList = GetDlgItem(hwnd, IDC_LIST1);
    auto count = SendMessage(hList, LB_GETCOUNT, 0, 0);
    if (count == LB_ERR) {
        ShowError(hwnd, _T("„N„u „}„€„s„… „„€„|„…„‰„y„„„Ž „{„€„|„y„‰„u„ƒ„„„r„€ „„|„u„}„u„~„„„€„r „r „ƒ„„y„ƒ„{„u"), _T("„O„Š„y„q„{„p"));
        return;
    }

    wchar_t buffer[0xff];
    for (int i = savedCount; i < count; i++) {
        if (!SendMessage(hList, LB_GETTEXT, i, (LPARAM)buffer)) 
            throw new exception("No text for you :<");
        savedText.push_back(buffer);
    }

    savedCount = count;
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

    return (INT_PTR)TRUE;
}