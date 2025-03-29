#pragma once

#include "Unicode.h"

constexpr u32 UTF8_1_MIN = 0x0;
constexpr u32 UTF8_1_MAX = 0x7F;
constexpr u32 UTF8_2_MIN = 0xC280;
constexpr u32 UTF8_2_MAX = 0xDFBF;
constexpr u32 UTF8_3_MIN = 0xE08080;
constexpr u32 UTF8_3_MAX = 0xEFBFBF;
constexpr u32 UTF8_4_MIN = 0xF0808080;
constexpr u32 UTF8_4_MAX = 0xF7BFBFBF;

constexpr char8 UTF8_LATER_BYTE_MIN = 0x80;
constexpr char8 UTF8_LATER_BYTE_MAX = 0xBF;
// UTF-8 延续字节中包含的代码点的位数
constexpr int UTF8_CONTINUATION_CODEPOINT_BITS = 6;

constexpr char UTF8_BOM[] = {0xEF, 0xBB, 0xBF};

bool start_with_utf8bom(const char *utf8);
bool is_utf8_later_byte(char c);

/* 单个 UTF-8 编码 */
bool is_valid_utf8(const char *utf8, int len);
/* 返回 UTF-8 字符长度 */
int is_utf8_str(const char *str);

void utf8_to_utf16(const char *utf8, char16 *utf16);
std::wstring utf8_to_utf16(const char *utf8);
