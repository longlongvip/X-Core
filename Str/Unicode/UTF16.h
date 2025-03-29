#pragma once

#include "Unicode.h"

bool is_utf16_high_surrogate(char16 c);
bool is_utf16_low_surrogate(char16 c);
bool is_utf16_surrogate(char16 c);

bool is_valid_utf16(const char16 *utf16, int len);

void utf16_to_utf8(const char16 *utf16, char *utf8);
std::string utf16_to_utf8(const char16 *utf16);
