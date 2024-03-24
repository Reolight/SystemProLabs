#pragma once
#define FILEEDITORPROC_H

#include "framework.h"
#include "windowsx.h"
#include "resource.h"
#include "commdlg.h"
#include "fileapi.h"

INT_PTR CALLBACK FileEditorProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);