#pragma once

#include "core.h"
#include "../XTypeDef.h"

struct OSVersion
{
    u32 major;
    u32 minor;
    u32 build;
};

static OSVersion GetOSVersion()
{
    using WindowsVersion = OSVERSIONINFOEX;
    auto GetWindowsVersion = []() -> WindowsVersion
    {
        HMODULE hModule = GetModuleHandle(L"ntdll.dll");

        using NtStatus = LONG;
        using RtlGetVersionPtr = INT_PTR(FAR WINAPI*)(WindowsVersion*);

        WindowsVersion vi{};

        if(hModule)
        {
            RtlGetVersionPtr fxPtr = reinterpret_cast<RtlGetVersionPtr>(GetProcAddress(hModule, "RtlGetVersion"));
            if(fxPtr)
            {
                vi.dwOSVersionInfoSize = sizeof(vi);
                if(fxPtr(&vi) != 0)
                {
                    
                }
                
            }
        }
        return vi;
    };

    WindowsVersion windows_version = GetWindowsVersion();
    return { windows_version.dwMajorVersion, windows_version.dwMajorVersion, windows_version.dwBuildNumber };
}
