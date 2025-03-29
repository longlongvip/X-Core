#include "UTF16.h"

#if defined X_PLATFORM_WINDOWS
    #include <stringapiset.h>
#endif

bool is_utf16_high_surrogate(char16 c)
{
    return HIGH_SURROGATE_MIN <= c && c <= HIGH_SURROGATE_MAX;
}

bool is_utf16_low_surrogate(char16 c)
{
    return LOW_SURROGATE_MIN <= c && c <= LOW_SURROGATE_MAX;
}

bool is_utf16_surrogate(char16 c)
{
    return HIGH_SURROGATE_MIN <= c && c <= LOW_SURROGATE_MAX;
}

bool is_valid_utf16(const char16 *utf16, int len)
{
    switch (len)
    {
    case 1:
        return true;
    case 2:
        if (!is_utf16_high_surrogate(utf16[0]) && !is_utf16_low_surrogate(utf16[1]))
        {
            return false;
        }
        break;
    default:
        return false;
    }
    return true;
}

void utf16_to_utf8(const char16 *utf16, char *utf8)
{
    int uft16_len = wcslen(utf16);
    #if defined X_PLATFORM_WINDOWS
        int len = WideCharToMultiByte(CP_UTF8, 0, utf16, uft16_len, nullptr, 0, nullptr, nullptr);
        WideCharToMultiByte(CP_UTF8, 0, utf16, uft16_len, utf8, len, nullptr, nullptr);
    #endif
}

std::string utf16_to_utf8(const char16 *utf16)
{
    int uft16_len = wcslen(utf16);
    #if defined X_PLATFORM_WINDOWS
        int len = WideCharToMultiByte(CP_UTF8, 0, utf16, uft16_len, nullptr, 0, nullptr, nullptr);
        std::string utf8(len, 0);
        WideCharToMultiByte(CP_UTF8, 0, utf16, uft16_len, utf8.data(), utf8.size(), nullptr, nullptr);
    #endif
    return utf8;
}
