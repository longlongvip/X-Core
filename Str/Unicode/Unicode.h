#pragma once

#include "XTypeDef.h"
#include <string>
#include <string_view>

#define BMP_END 0xFFFF
#define UNICODE_MAX 0x10FFFF
#define INVALID_CODEPOINT 0xFFFD

// 如果一个字符与 SURROGATE_MASK 匹配该值，那么它就是一个高位代理
#define HIGH_SURROGATE_MIN 0xD800
#define HIGH_SURROGATE_MAX 0xDBFF
// 如果一个字符与 SURROGATE_MASK 匹配该值，那么它就是一个低位代理
#define LOW_SURROGATE_MIN 0xDC00
#define LOW_SURROGATE_MAX 0xDFFF

// 如果一个字符与 GENERIC_SURROGATE_MASK 匹配该值，则它是一个代理字符
#define GENERIC_SURROGATE_VALUE 0xD800
// 在针对generic_surrogate_value测试之前，要应用于角色的面具
#define GENERIC_SURROGATE_MASK 0xF800

// 在对高代理位值或低代理位值进行测试之前，要应用于字符的掩码
#define SURROGATE_MASK 0xFC00

#define SURROGATE_CODEPOINT_OFFSET 0x10000
#define SURROGATE_CODEPOINT_BITS 10 // SURROGATE_CODEPOINT_MASK 的位数
#define LEAD_OFFSET 0xD7C0 // HIGH_SURROGATE_MIN - (SURROGATE_CODEPOINT_OFFSET >> 10)
#define SURROGATE_OFFSET 0xFCA02400 // SURROGATE_CODEPOINT_OFFSET - (HIGH_SURROGATE_MIN << 10) - LOW_SURROGATE_MIN
#define SURROGATE_CODEPOINT_MASK  0x03FF// 一种可应用于代理以提取其中所包含的代码点值的掩码

constexpr int UTF16_CHAR_SIZE_L = 1;
constexpr int UTF16_CHAR_SIZE_H = 2;
constexpr int UTF32_CHAR_SIZE = 1;

/* UTF-8 编码的首字节 */
bool is_utf8_1(char c);
bool is_utf8_2(char c);
bool is_utf8_3(char c);
bool is_utf8_4(char c);
bool is_utf8_5(char c);
bool is_utf8_6(char c);
int utf8_size(char c);
/* UTF-16 编码的首字节 */
bool is_utf16_1(char16 c);
bool is_utf16_2(char16 c);
int utf16_size(char16 c);

int u32tochar8(char* out, u32& in);
int u32tochar8u32(u32* out, u32& in);

u32 utf8_to_utf16(u32 utf8);
u32 utf8_to_utf32(u32 utf8);
u32 utf16_to_utf8(u32 utf16);
u32 utf16_to_utf32(u32 utf16);
u32 utf32_to_utf8(char32 utf32);
u32 utf32_to_utf16(char32 utf32);

enum UnicodeError
{
    Ok = 0,
    BadLeadingByte,
    BadContinuationByte,
    InvalidCodePoint,
    TooLongEnCode,
};
