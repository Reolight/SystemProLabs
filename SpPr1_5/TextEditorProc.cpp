#include "TextEditorProc.h"

using namespace std;

vector<wchar_t*> savedText;
int savedCount = 0;
const size_t CLIPBOARD_SIZE = 0x200;
wchar_t clipboard[CLIPBOARD_SIZE]{ 0 };

struct TextList {
private:
    static const size_t _page_size = 0x200;
    static const int _page_count = 30;
    wchar_t memory[_page_size * _page_count];
    int count_saved = 0;
public:
    TextList() {
        memset(memory, 0, _page_count * _page_size);
    }

    int count() {
        return count_saved;
    }

    void push(const wchar_t str[_page_size]) {
        wcscpy_s(memory, str);
    }

    void at(const int index, wchar_t* result) const {
        const wchar_t* ptr = memory + index * _page_size;
        wcscpy_s(result, _page_size, ptr);
    }

    wchar_t* operator [] (const int index) {
        return memory + index * _page_size;
    }
};

TextList textList{};

bool AddString(HWND hList, LPCWSTR string) {
    return SendMessage(hList, LB_ADDSTRING, CLIPBOARD_SIZE, (LPARAM)string);
}

void ShowError(HWND hwnd, LPCWSTR text, LPCWSTR caption) {
    MessageBox(hwnd, text, caption, MB_OK | MB_ICONERROR);
}

bool onEditorInit(HWND hDlg, HWND hWnd, LPARAM lParam) {
    if (savedCount == 0) return 1;
    Button_Enable(GetDlgItem(hDlg, IDC_ADDTEXT), false);
    HWND hList = GetDlgItem(hDlg, IDC_LIST1);
    
    for (int i = 0; i < savedCount; i++) {
        wchar_t* b = new wchar_t[CLIPBOARD_SIZE];
        textList.at(i, b);
        if (!AddString(hList, b)) throw new exception("Text wasn't inserted");
    }

    return 1;
}

void OnReadClicked(HWND hwnd) {
    HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);
    SendMessage(hEdit, WM_GETTEXT, CLIPBOARD_SIZE, (LPARAM)clipboard);
    // MessageBox(hwnd, clipboard, _T("„R„{„€„„y„‚„€„r„p„~„€"), MB_OK | MB_ICONINFORMATION);
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

    wchar_t buffer[CLIPBOARD_SIZE];
    for (int i = savedCount; i < count; i++) {
        memset(buffer, 0, CLIPBOARD_SIZE);
        if (!SendMessage(hList, LB_GETTEXT, i, (LPARAM)buffer)) 
            throw new exception("No text for you :<");
        wchar_t* line = new wchar_t[CLIPBOARD_SIZE];
        wsprintf(line, _T("%s"), buffer);
        textList.push(line);
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