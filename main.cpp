#include <cstdio>
#include <windows.h>
#include <tchar.h>

#define DLL_FILENAME TEXT("winkeysdll.dll")
#define KEYBOARD_PROC_NAME "_KeyboardProc@12"
#define SAVE_HOOK_PROC_NAME "_SaveHHOOK@4"

typedef int (CALLBACK *hSaveHook)(HHOOK hook);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HINSTANCE instance = LoadLibrary(DLL_FILENAME);

    if(!instance) {
        _tprintf(TEXT("Unable to load %s"), DLL_FILENAME);
        return 1;
    }
    HOOKPROC KeyboardProc = (HOOKPROC)GetProcAddress(instance, KEYBOARD_PROC_NAME);
    hSaveHook SaveHook = (hSaveHook)GetProcAddress(instance, SAVE_HOOK_PROC_NAME);

    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, instance, 0);

    if(!hHook) {
        _tprintf(TEXT("Unable to set hook"));
        return 1;
    }

    SaveHook(hHook);

    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if(bRet == -1) {
            UnhookWindowsHookEx(hHook);
            _tprintf(TEXT("Unable to get message"));
            return 1;
        }
        if (msg.message == WM_QUIT) {
            UnhookWindowsHookEx(hHook);
            _tprintf(TEXT("EXIT"));
            return 1;
        }
        _tprintf(TEXT("message 0x%h"), msg.message);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };
}
