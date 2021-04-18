//
// Created by shewa on 17.01.2021.
//
#include <cstdio>
#include "winkeysdll.h"

TCHAR globalFilename[] = TEXT("WinkeysDllFileMappingObject");
TCHAR globalFilenameDebug[] = TEXT("WinkeysDebug");


HHOOK CALLBACK GetHHOOK() {
    HANDLE hmFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, globalFilename);
    if (!hmFile) {
        auto res = GetLastError();
        return nullptr;
    }
    HHOOK *pHook = (HHOOK *) MapViewOfFile(hmFile, FILE_MAP_READ, 0, 0, sizeof(HHOOK));
    HHOOK hook = *pHook;
    UnmapViewOfFile(pHook);
    CloseHandle(hmFile);
    return hook;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *) lParam;
        if(wParam == WM_KEYDOWN && p->vkCode == VK_CAPITAL) {
            auto hwnd = GetAncestor(GetForegroundWindow(), GA_ROOTOWNER);
            PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 2, 0);
            return 1;
        }
    }
    return CallNextHookEx(GetHHOOK(), nCode, wParam, lParam);
}

int CALLBACK SaveHHOOK(HHOOK hhook) {
    HANDLE hmFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, globalFilename);
    if (!hmFile) {
        hmFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL , PAGE_READWRITE, 0, sizeof(HHOOK), globalFilename);
        if (!hmFile) {
            auto res = GetLastError();
            return 0;
        }
    }
    LPVOID map = MapViewOfFile(hmFile, FILE_MAP_WRITE, 0, 0, sizeof(HHOOK));
    HHOOK tHook = hhook;
    CopyMemory(map, &tHook, sizeof(HHOOK));
    UnmapViewOfFile(map);
    CloseHandle(hmFile);
    return 1;
}

