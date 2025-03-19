#pragma once

#include <cctype>

#include "XTypeDef.h"

inline bool is_ascii(unsigned char c)
{
    return c < 0x80;
}

inline bool is_exascii(unsigned char c)
{
    return 0x7F < c && c <= 0xFF;
}

inline bool is_hex(char c)
{
    return isxdigit(c);
}

inline bool is_hex_digit(char c)
{
    return isxdigit(c) && isdigit(c);
}

inline bool is_hex_letter(char c)
{
    return isxdigit(c) && isalpha(c);
}

inline bool is_hex_lower(char c)
{
    return islower(c) && isxdigit(c);
}

inline bool is_hex_upper(char c)
{
    return isupper(c) && isxdigit(c);
}

inline bool is_separator(char c)
{

}

inline bool is_symbol(char c)
{

}

// wide char
inline bool is_ascii(char16 c)
{
    return c < 0x0100;
}

inline bool to_ascii(char16 c, char *o)
{
    if (is_ascii(c))
    {
        *o = c & 0x00FF;
        return true;
    }
    return false;
}

inline bool is_hex(char16 c)
{
    return iswxdigit(c);
}

inline bool is_hex_digit(char16 c)
{
    return iswxdigit(c) && iswdigit(c);
}

inline bool is_hex_letter(char16 c)
{
    return iswxdigit(c) && iswalpha(c);
}

inline bool is_hex_lower(char16 c)
{
    return iswlower(c) && iswxdigit(c);
}

inline bool is_hex_upper(char16 c)
{
    return iswupper(c) && iswxdigit(c);
}

// 如果一个字符与 SURROGATE_MASK 匹配该值，那么它就是一个高位代理
constexpr char16 H_SURROGATE_MIN = 0xd800;
constexpr char16 H_SURROGATE_MAX = 0xdbff;
// 如果一个字符与 SURROGATE_MASK 匹配该值，那么它就是一个低位代理
constexpr char16 L_SURROGATE_MIN = 0xdc00;
constexpr char16 L_SURROGATE_MAX = 0xdfff;

inline bool is_high_surrogate(char16 c)
{
    return H_SURROGATE_MIN <= c && c <= H_SURROGATE_MAX;
}

inline bool is_lower_surrogate(char16 c)
{
    return L_SURROGATE_MIN <= c && c <= L_SURROGATE_MAX;
}

inline bool is_separator(char16 c)
{
}

inline bool is_symbol(char16 c)
{
    
}


inline int digit2num(char c)
{
    if(isdigit(c))
    {
        return c - '0';
    }
    return -1;
}

inline char num2digit(int c)
{
    if(IsIn(c, 0, 9))
    {
        return '0' + c;
    }
    return '\0';
}

inline char num2hex(int c, bool upper_case=true)
{
    if(IsIn(c, 0, 9))
    {
        return '0' + c;
    }
    if(IsIn(c, 10, 15))
    {
        if(upper_case)
        {
            return 'A' + c - 10;
        }
        else
        {
            return 'a' + c - 10;
        }
    }
    return '\0';
}

inline int hex2num(char c)
{
    if(IsIn(c, '0', '9'))
    {
        return c - '0';
    }
    if(IsIn(c, 'a', 'f'))
    {
        return c - 'a' + 10;
    }
    if(IsIn(c, 'A', 'F'))
    {
        return c - 'A' + 10;
    }
    return -1;
}
