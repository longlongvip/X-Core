#include "Unicode.h"

bool is_utf8_1(char c)
{
    return U8(c) < 0x80;
}

bool is_utf8_2(char c)
{
    // 1100000x	C0, C1过长编码：双字节序列的头字节，但码点 <= 127
    return 0xC2 <= U8(c) && U8(c) <= 0xDF;
}

bool is_utf8_3(char c)
{
    return 0xE0 <= U8(c) && U8(c) <= 0xEF;
}

bool is_utf8_4(char c)
{
    return 0xF0 <= U8(c) && U8(c) <= 0xF7;
}

bool is_utf8_5(char c)
{
    return 0xF8 <= U8(c) && U8(c) <= 0xFB;
}

bool is_utf8_6(char c)
{
    return 0xFC <= U8(c) && U8(c) <= 0xFD;
}

int utf8_size(char c)
{
    // c 是 单个 UTF-8 字符的第一个码位
    if (c < 0x80)
    {
        return 1;
    }
    if (0xC2 <= U8(c) && U8(c) <= 0xDF)
    {
        // 1100000x	C0, C1	过长编码：双字节序列的头字节，但码点 <= 127
        return 2;
    }
    if (0xE0 <= U8(c) && U8(c) <= 0xEF)
    {
        return 3;
    }
    if (0xF0 <= U8(c) && U8(c) <= 0xF7)
    {
        return 4;
    }
    if (0xF8 <= U8(c) && U8(c) <= 0xFB)
    {
        return 5;
    }
    if (0xFC <= U8(c) && U8(c) <= 0xFD)
    {
        return 6;
    }
    return 0;
}

bool is_utf16_1(char16 c)
{
    return c <= BMP_END;
}

bool is_utf16_2(char16 c)
{
    return IsIn(c, Char16(HIGH_SURROGATE_MIN), Char16(HIGH_SURROGATE_MAX));
}

int utf16_size(char16 c)
{
    if (is_utf16_1(c))
    {
        return UTF16_CHAR_SIZE_L;
    }
    if (is_utf16_2(c))
    {
        return UTF16_CHAR_SIZE_H;
    }
    return 0;
}

int u32tochar8(char* out, u32& in)
{
    int size = BytesOf32(in);
    #if defined ENDIAN_LITTLE
        for(int i = 0; i < size; i++)
        {
            int offset = 8 * (size - i - 1);
            out[i] = (in << offset) & 0xFF;
        }
    #endif
    return size;
}

u32 utf8_to_utf16(u32 utf8)
{
    return utf32_to_utf16(utf8_to_utf32(utf8));
}

u32 utf8_to_utf32(u32 utf8)
{
    u32 tmp[4]= { 0 };
    u32 tmp = BSwap32(utf8);
    int len = utf8_size(tmp[0]);

    u32 res = 0;
    switch (len)
    {
    case 1:
        return tmp[0];

    case 2:
        tmp[0] &= 0x1F; tmp[0] <<= 6;
        tmp[1] &= 0x3F;
        return tmp[0] | tmp[1];

    case 3:
        tmp[0] &= 0x0F; tmp[0] <<= 12;
        tmp[1] &= 0x3F; tmp[1] <<= 6;
        tmp[2] &= 0x3F;
        return tmp[0] | tmp[1] | tmp[2];
    case 4:
        tmp[0] &= 0x07; tmp[0] <<= 18;
        tmp[1] &= 0x3F; tmp[1] <<= 12;
        tmp[2] &= 0x3F; tmp[2] <<= 6;
        tmp[3] &= 0x3F;
        return tmp[0] | tmp[1] | tmp[2] | tmp[3];

    default:
        break;
    }
    return res;
}

u32 utf16_to_utf8(u32 utf16)
{
    return utf32_to_utf8(utf16_to_utf32(utf16));
}

u32 utf16_to_utf32(u32 utf16)
{
    if (utf16 < HIGH_SURROGATE_MIN || (LOW_SURROGATE_MAX < utf16 && utf16 <= BMP_END))
    {
        return utf16;
    }

    u32 utf16_1 = (utf16 >> 16) & 0xFFFF;
    if(HIGH_SURROGATE_MIN <= utf16_1 && utf16_1 <= HIGH_SURROGATE_MAX)
    {
        u32 utf16_2 = utf16 & 0xFFFF;
        if(LOW_SURROGATE_MIN <= utf16_1 && utf16_1 <= LOW_SURROGATE_MAX)
        {
            utf16_1 -= HIGH_SURROGATE_MIN;
            utf16_1 <<= SURROGATE_CODEPOINT_BITS;
            utf16_2 -= LOW_SURROGATE_MIN;
            return utf16_1 + utf16_2 + SURROGATE_CODEPOINT_OFFSET;
        }
        return 0;
    }
    return 0;
}

u32 utf32_to_utf8(char32 utf32)
{
    if (utf32 < 0x80)
    {
        return utf32;
    }
    else if (utf32 < 0x800)
    {
        u32 utf8_1 = 0xC0 | (utf32 >> 6);
        u32 utf8_2 = 0x80 | (utf32 & 0x3F);
        return (utf8_1 << 8) | utf8_2;
    }
    else if (utf32 < 0x10000)
    {
        u32 utf8_1 = 0xE0 | (utf32 >> 12);
        u32 utf8_2 = 0x80 | ((utf32 >> 6) & 0x3F);
        u32 utf8_3 = 0x80 | (utf32 & 0x3F);
        return (utf8_1 << 16) | (utf8_2 << 8) | utf8_3;
    }
    else if (utf32 < 0x110000)
    {
        u32 utf8_1 = 0xF0 | ((utf32 >> 18) & 0x07);
        u32 utf8_2 = 0x80 | ((utf32 >> 12) & 0x3F);
        u32 utf8_3 = 0x80 | ((utf32 >> 6) & 0x3F);
        u32 utf8_4 = 0x80 | (utf32 & 0x3F);
        return (utf8_1 << 24) | (utf8_2 << 16) | (utf8_3 << 8) | utf8_4;
    }
    return 0;
}

u32 utf32_to_utf16(char32 utf32)
{
    if (utf32 < HIGH_SURROGATE_MIN || (LOW_SURROGATE_MAX < utf32 && utf32 <= BMP_END))
    {
        return utf32;
    }
    u32 utf16_1 = LEAD_OFFSET + (utf32 >> SURROGATE_CODEPOINT_BITS);
    u32 utf16_2 = LOW_SURROGATE_MIN + (utf32 & SURROGATE_CODEPOINT_MASK);
    return (utf16_1 << 16) | utf16_2;
}
