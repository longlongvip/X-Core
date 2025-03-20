#pragma once

#include "Core.h"
#include <type_traits>

class WinHandle
{
public:
    WinHandle() : handle_(INVALID_HANDLE_VALUE) {}
    WinHandle(HANDLE handle) : handle_(handle) {}
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
