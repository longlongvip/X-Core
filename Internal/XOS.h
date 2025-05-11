#pragma once

#if (defined(_M_AMD64) || defined(_M_IX86) || defined(_WIN32) || defined(_WIN64))
#   define X_PLATFORM_WINDOWS 1
#   undef ERROR // override (really stupid) wingdi.h standard definition
#   undef DELETE // override (another really stupid) winnt.h standard definition
#   undef MessageBox // override winuser.h standard definition
#   undef Error
#   undef OK
#   undef CONNECT_DEFERRED // override from Windows SDK, clashes with Object enum
#   undef MemoryBarrier
#   undef MONO_FONT
#elif defined(__linux__)
#   define X_PLATFORM_LINUX 1
#endif

// 定义大小端
#if (defined(X_PLATFORM_WINDOWS) || defined(X_PLATFORM_LINUX) || defined(X_PLATFORM_MACOS) || defined(X_PLATFORM_ANDROID) || defined(X_PLATFORM_IOS))
#   define ENDIAN_LITTLE 1
#else
#   define ENDIAN_BIG 1
#endif
