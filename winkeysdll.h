#pragma once

#ifdef WINKEYSDLL_EXPORTS
#define WINKEYSDLL_API __declspec(dllexport)
#else
#define WINKEYSDLL_API __declspec(dllimport)
#endif

#include <windows.h>

extern "C" WINKEYSDLL_API HHOOK CALLBACK GetHHOOK();

extern "C" WINKEYSDLL_API LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

extern "C" WINKEYSDLL_API int CALLBACK SaveHHOOK(HHOOK hhook);


