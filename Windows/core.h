#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace Platform
{
    using WndProc = LRESULT (*)(HWND, UINT, WPARAM, LPARAM);
    using WndHandle = HWND;

    using SysChar = wchar_t;

    struct Window_Init_Info
    {
        WndProc callback{nullptr};
        WndHandle parent{nullptr};
        const SysChar *caption{nullptr};
        int left{0};
        int top{0};
        int width{800};
        int height{450};
    };
}

int AnsiToWide(wchar_t *out, const char *in)
{
    if (out == nullptr)
    {
        return -1;
    }
    if (in == nullptr)
    {
        return 0;
    }
    int wide_len = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, in, -1, nullptr, 0);
    if (wide_len <= 0)
    {
        return 0;
    }
    int res = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, in, -1, out, wide_len);
    if (res <= 0)
    {
        return 0;
    }
    return res;
}

int Utf8ToWide(wchar_t *out, const char *in)
{
    if (out == nullptr)
    {
        return -1;
    }
    if (in == nullptr)
    {
        return 0;
    }
    int wide_len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, in, -1, nullptr, 0);
    if (wide_len <= 0)
    {
        return 0;
    }
    int res = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, in, -1, out, wide_len);
    if (res <= 0)
    {
        return 0;
    }
    return res;
}

int WideToAnsi(char *out, const wchar_t *in)
{
    if (out == nullptr)
    {
        return -1;
    }
    if (in == nullptr)
    {
        return 0;
    }
    int utf8_len = WideCharToMultiByte(
        CP_ACP,  // 代码页：UTF-8
        0,       // 标志(一般填0)
        in,      // 输入的宽字符字符串
        -1,      // 自动计算输入长度(直到NULL终止符)
        nullptr, // 不接收输出(仅计算长度)
        0,       // 输出缓冲区大小(设为0仅计算长度)
        nullptr, // 默认字符(一般填nullptr)
        nullptr  // 是否使用了默认字符(一般填nullptr)
    );
    if (utf8_len <= 0)
    {
        return 0;
    }
    // 执行转换
    int res = WideCharToMultiByte(CP_ACP, 0, in, -1, out, utf8_len, nullptr, nullptr);
    if (res <= 0)
    {
        return 0;
    }

    return res; // 返回字节数(包括NULL终止符)
}

int WideToUtf8(char *out, const wchar_t *in)
{
    if (out == nullptr)
    {
        return -1;
    }
    if (in == nullptr)
    {
        return 0;
    }
    int utf8_len = WideCharToMultiByte(
        CP_UTF8, // 代码页：UTF-8
        0,       // 标志(一般填0)
        in,      // 输入的宽字符字符串
        -1,      // 自动计算输入长度(直到NULL终止符)
        nullptr, // 不接收输出(仅计算长度)
        0,       // 输出缓冲区大小(设为0仅计算长度)
        nullptr, // 默认字符(一般填nullptr)
        nullptr  // 是否使用了默认字符(一般填nullptr)
    );
    if (utf8_len <= 0)
    {
        return 0;
    }
    // 执行转换
    int res = WideCharToMultiByte(CP_UTF8, 0, in, -1, out, utf8_len, nullptr, nullptr);
    if (res <= 0)
    {
        return 0;
    }

    return res; // 返回字节数(包括NULL终止符)
}
