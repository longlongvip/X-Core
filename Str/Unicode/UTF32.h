#pragma once

#include "Unicode.h"

bool is_unicode_bmp(char32 c);
bool is_unicode_high_surrogate(char32 c);
bool is_unicode_low_surrogate(char32 c);
bool is_unicode_surrogate(char32 c);
bool is_unicode_valid(char32 c);

int utf32_to_utf8(char32 utf32, char *utf8);
int utf32_to_utf16(char32 utf32, char16 *utf16);
