#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>

class WinHandle
{
public:
    WinHandle() : handle_(INVALID_HANDLE_VALUE) { }
    WinHandle(HANDLE handle) : handle_(handle) { }
    ~WinHandle()
    {
        if (handle_ != INVALID_HANDLE_VALUE)
        {
            ::CloseHandle(handle_);
            handle_ = INVALID_HANDLE_VALUE;
        }
    }

    void swap(WinHandle &&other) noexcept { std::swap(handle_, other.handle_); }

    WinHandle(WinHandle &&moved) noexcept : handle_(INVALID_HANDLE_VALUE) { swap(std::move(moved)); }
    WinHandle(const WinHandle &copied) = delete;

    WinHandle &operator=(WinHandle &&moved)
    {
        swap(std::move(moved));
        return *this;
    }
    WinHandle &operator=(const WinHandle &copied) = delete;

    HANDLE get() const { return handle_; }
    void set(HANDLE handle)
    {
        handle_ = handle;
    }

    bool isValid() const
    {
        return handle_ != INVALID_HANDLE_VALUE;
    }

    HANDLE release()
    {
        HANDLE retHandle = handle_;
        handle_ = INVALID_HANDLE_VALUE;
        return retHandle;
    }

protected:
    HANDLE handle_;
};

void to_utf8(const std::wstring &in, std::string &out)
{
    if (in.empty())
    {
        out.clear();
        return;
    }
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, in.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char *buffer = new char[size_needed];
    WideCharToMultiByte(CP_UTF8, 0, in.c_str(), -1, buffer, size_needed, nullptr, nullptr);
    out = buffer;
    delete[] buffer;
}

void to_ansi(const std::wstring &in, std::string &out)
{
    if (in.empty())
    {
        out.clear();
        return;
    }
    int size_needed = WideCharToMultiByte(CP_ACP, 0, in.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char *buffer = new char[size_needed];
    WideCharToMultiByte(CP_ACP, 0, in.c_str(), -1, buffer, size_needed, nullptr, nullptr);
    out = buffer;
    delete[] buffer;
}

void to_utf16(const std::string &in, std::wstring &out, int mode)
{
    if (in.empty())
    {
        out.clear();
        return;
    }
    int size_needed = MultiByteToWideChar(mode, 0, in.c_str(), in.size(), nullptr, 0);
    wchar_t *buffer = new wchar_t[size_needed];
    MultiByteToWideChar(mode, 0, in.c_str(), in.size(), buffer, size_needed);
    out = buffer;
    delete[] buffer;
}

void to_utf8(const wchar_t* in, char* out)
{
    if (in == nullptr || out == nullptr)
    {
        return;
    }
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, in, -1, nullptr, 0, nullptr, nullptr);
    char *buffer = new char[size_needed];
    WideCharToMultiByte(CP_UTF8, 0, in, -1, buffer, size_needed, nullptr, nullptr);
    out = buffer;
    delete[] buffer;
}

void to_ansi(const wchar_t* in, char* out)
{
    if (in == nullptr || out == nullptr)
    {
        return;
    }
    int size_needed = WideCharToMultiByte(CP_ACP, 0, in, -1, nullptr, 0, nullptr, nullptr);
    WideCharToMultiByte(CP_ACP, 0, in, -1, out, size_needed, nullptr, nullptr);
    return;
}
