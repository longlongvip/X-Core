#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace Platform
{
    using WndProc = LRESULT(*)(HWND, UINT, WPARAM, LPARAM);
    using WndHandle = HWND;

    using SysChar = wchar_t;

    struct Window_Init_Info
    {
        WndProc callback{ nullptr };
        WndHandle parent{ nullptr };
        const SysChar* caption { nullptr };
        int left{ 0 };
        int top { 0 };
        int width{ 800 };
        int height { 450 };
    };
}
