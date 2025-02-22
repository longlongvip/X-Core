#pragma once

#include <cstdint>
#include <climits>

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using int8 = int32_t;
using int16 = int64_t;
using int32 = int32_t;
using int64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using byte = uint8_t;

#ifdef _WIN32
    using char32 = uint32_t;
    using char16 = wchar_t;
    using char8 = uint8_t;
    using SysChar = wchar_t;
#else
#   ifdef __LINUX__ || __APPLE__
        using char32 = uint32_t;        
        using char16 = uint16_t;
        using char8 = uint8_t;
        using SysChar = uint8_t;
#   endif
#endif

#define Int(v) static_cast<int>(v)
#define Float(v) static_cast<float>(v)
#define Double(v) static_cast<double>(v)
#define U8(v) static_cast<u8>(v)
#define U16(v) static_cast<u16>(v)
#define U32(v) static_cast<u32>(v)
#define U64(v) static_cast<u64>(v)

template<typename T>
inline bool IsIn(const T& x, const T& a, const T& b)
{
    return a <= x && x <= b;
}

template<typename T>
inline bool IsNotIn(const T& x, const T& a, const T& b)
{
    return a > x || x > b;
}
