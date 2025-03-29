#include "UTF8.h"

#if defined X_PLATFORM_WINDOWS
    #include <stringapiset.h>
#endif

bool start_with_utf8bom(const char *utf8)
{
    if(utf8 == nullptr)
    {
        return false;
    }
    char* p = DeConst(utf8);

    if (*p != UTF8_BOM[0])
    {
        return false;
    }

    p++;
    if (*p != UTF8_BOM[1])
    {
        return false;
    }

    p++;
    if (*p != UTF8_BOM[2])
    {
        return false;
    }
    return true;
}

bool is_utf8_later_byte(char c)
{
    return IsIn(U8(c), UTF8_LATER_BYTE_MIN, UTF8_LATER_BYTE_MAX);
}

bool is_valid_utf8(const char *utf8, int len)
{
    switch (len)
    {
    case 1:
        return true;
    case 2:
        if (is_utf8_later_byte(utf8[1]))
        {
            return true;
        }
        break;
    case 3:
        if (is_utf8_later_byte(utf8[1]) && is_utf8_later_byte(utf8[2]))
        {
            return true;
        }
        break;
    case 4:
        if (is_utf8_later_byte(utf8[1]) && is_utf8_later_byte(utf8[2]) && is_utf8_later_byte(utf8[3]))
        {
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

int is_utf8_str(const char *str)
{
    if (str == nullptr)
    {
        return 0;
    }
    if (start_with_utf8bom(str))
    {
        str += 3;
    }
    int utf8_chars = 0;
    char* p = DeConst(str);
    while (p)
    {
        int len = utf8_size(*p);
        if (is_valid_utf8(p, len))
        {
            utf8_chars += 1;
            p += len;
        }
        else
        {
            return 0;
        }
    }
    return utf8_chars;
}

void utf8_to_utf16(const char *utf8, char16 *utf16)
{
    int utf8_bytes = strlen(utf8);
    #if defined X_PLATFORM_WINDOWS
        int len = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8_bytes, nullptr, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8, utf8_bytes, utf16, len);
    #endif
}

std::wstring utf8_to_utf16(const char *utf8)
{
    int utf8_bytes = strlen(utf8);
    #if defined X_PLATFORM_WINDOWS
        int len = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8_bytes, nullptr, 0);
        std::wstring utf16(len, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8, utf8_bytes, utf16.data(), utf16.size());
    #endif
    return utf16;
}
