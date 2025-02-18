#pragma once

#if (!defined(X_X_PLATFORM_WINDOWS) && !defined(X_PLATFORM_LINUX) && !defined(X_PLATFORM_MACOS) && !defined(X_PLATFORM_ANDROID) && !defined(X_PLATFORM_IOS))
#   if (defined(_M_AMD64) || defined(_M_IX86) || defined(_WIN32) || defined(_WIN64))
#       define X_PLATFORM_WINDOWS
#   elif defined(__linux__)
#       define X_PLATFORM_LINUX
#   endif
#endif

#include "XArch.h"

// Define the endianness.
#if (defined(X_PLATFORM_WINDOWS) || defined(X_PLATFORM_LINUX) || defined(X_PLATFORM_MACOS) || defined(X_PLATFORM_ANDROID) || defined(X_PLATFORM_IOS))
#   define ENDIAN_LITTLE
#else
#   define ENDIAN_BIG
#endif

enum class Platform
{
    InValid = -1,
    First,
    Windows = First,
    Linux,
    MacOS,
    Android,
    iOS,
    All,
    NumPlatforms = All,
};

inline Platform get_platform()
{
#   if defined(X_PLATFORM_WINDOWS)
	    return Platform::Windows;
#   elif defined(X_PLATFORM_LINUX)
	    return Platform::Linux;
#   elif defined(X_PLATFORM_MACOS)
	    return Platform::MacOS;
#   elif defined(X_PLATFORM_ANDROID)
	    return Platform::Android;
#   elif defined(X_PLATFORM_IOS)
	    return Platform::iOS;
#   else
	    return Platform::InValid;
#   endif
}