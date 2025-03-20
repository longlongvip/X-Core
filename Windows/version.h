#pragma once

#include "Core.h"

struct OSVersion
{
    char name[16];
    unsigned int major;
    unsigned int minor;
    unsigned int build;
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
    OSVersion res;
    strncpy(res.name, "Windows", 16);
    res.major = windows_version.dwMajorVersion;
    res.minor = windows_version.dwMajorVersion;
    res.build = windows_version.dwBuildNumber;
    return res;
}
