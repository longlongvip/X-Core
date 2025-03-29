#include "UTF32.h"

bool is_unicode_bmp(char32 c)
{
    return c < HIGH_SURROGATE_MIN || (LOW_SURROGATE_MAX < c && c <= BMP_END);
}

bool is_unicode_high_surrogate(char32 c)
{
    return HIGH_SURROGATE_MIN <= c && c <= HIGH_SURROGATE_MAX;
}

bool is_unicode_low_surrogate(char32 c)
{
    return LOW_SURROGATE_MIN <= c && c <= LOW_SURROGATE_MAX;
}

bool is_unicode_surrogate(char32 c)
{
    return HIGH_SURROGATE_MIN <= c && c <= LOW_SURROGATE_MAX;
}

bool is_unicode_valid(char32 c)
{
    return c <= UNICODE_MAX && !is_unicode_surrogate(c);
}

int utf32_to_utf8(char32 utf32, char *utf8)
{
    if (utf32 < 0x80)
    {
        utf8[0] = U8(utf32);
        return 1;
    }
    else if (utf32 < 0x800)
    {
        utf8[0] = U8(0xC0 | (utf32 >> 6));
        utf8[1] = U8(0x80 | (utf32 & 0x3F));
        return 2;
    }
    else if (utf32 < 0x10000)
    {
        utf8[0] = U8(0xE0 | (utf32 >> 12));
        utf8[1] = U8(0x80 | ((utf32 >> 6) & 0x3f));
        utf8[2] = U8(0x80 | (utf32 & 0x3f));
        return 3;
    }
    else if (utf32 < 0x110000)
    {
        utf8[0] = U8(0xF0 | ((utf32 >> 18) & 0x07));
        utf8[1] = U8(0x80 | ((utf32 >> 12) & 0x3F));
        utf8[2] = U8(0x80 | ((utf32 >> 6) & 0x3F));
        utf8[3] = U8(0x80 | (utf32 & 0x3F));
        return 4;
    }
    return 0;
}

int utf32_to_utf16(char32 utf32, char16 *utf16)
{
    if  (utf32 < HIGH_SURROGATE_MIN || (LOW_SURROGATE_MAX < utf32 && utf32 <= BMP_END))
    {
        utf16[0] = U16(utf32);
        return 1;
    }
    else if (utf32 < UNICODE_MAX)
    {
        utf16[0] = U16(LEAD_OFFSET + (utf32 >> SURROGATE_CODEPOINT_BITS));
        utf16[1] = U16(LOW_SURROGATE_MIN + (utf32 & SURROGATE_CODEPOINT_MASK));
        return 2;
    }
    return 0;
}
