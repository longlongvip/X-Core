#pragma once

#include "XMacros.h"

// 主版本
#define X_VERSION_MAJOR 1

// 次版本
#define X_VERSION_MINOR 0

// 改版
#define X_VERSION_ALTER 0

// Build 版本
#ifndef X_CONFIG_VERSION_BUILD
#   define X_CONFIG_VERSION_BUILD  0
#endif
#define X_VERSION_BUILD X_CONFIG_VERSION_BUILD

// Build 版本字符串
#define X_VERSION_BUILD_STRING X_String_Ex(X_CONFIG_VERSION_BUILD)

// 版本字符串
#define X_VERSION_STRING X_Strcat6("X_Common_", X_String_Ex(X_Concat8_Ex(v, X_VERSION_MAJOR, _, X_VERSION_MINOR, _, X_VERSION_ALTER, _, X_CONFIG_VERSION_BUILD)), "_", X_ARCH_VERSION_STRING, " by ", X_COMPILER_VERSION_STRING)

// the short version string
#define X_VERSION_SHORT_STRING X_Strcat("X_Common_", X_String_Ex(X_Concat8_Ex(v, X_VERSION_MAJOR, _, X_VERSION_MINOR, _, X_VERSION_ALTER, _, X_CONFIG_VERSION_BUILD)))
