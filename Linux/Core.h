#pragma once

namespace Platform
{
    //using WndProc = LRESULT(*)(fd, UINT, WPARAM, LPARAM);
    using WndHandle = int;
    using SysChar = char;

    struct Window_Init_Info
    {
       // WndProc callback{ nullptr };
        WndHandle parent{ 0 };
        const SysChar* caption { nullptr };
        int left{ 0 };
        int top { 0 };
        int width{ 800 };
        int height { 450 };
    };
}
