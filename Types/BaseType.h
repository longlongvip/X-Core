#pragma once

#include "Internal/XOS.h"

#include <cstddef> // ptrdiff_t
#include <cstdint> // uint32_t
#include <cstdlib> // size_t

// static_assert(__cplusplus >= CPlusPlus17);

// 类型别名
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
using uint = uint32_t;
using u64 = uint64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using byte = uint8_t;

using f32 = float;
using f64 = double;

#if X_PLATFORM_WINDOWS
    using char32 = uint32_t;
    using char16 = wchar_t;
    using char8 = uint8_t;
    using SysChar = wchar_t;
    #   ifdef _UNICODE
    #        define NEWLINE L"\r\n"
    #   else
    #       define NEWLINE "\r\n"
    #   endif

    /** 这是一个宏 */
    #define WidenStr2(x) L ## x
    /** 这是一个宏 */
    #define WidenStr(x) Widen2(x)
#endif

#ifdef __LINUX__ || __APPLE__
    using char32 = uint32_t;
    using char16 = uint16_t;
    using char8 = uint8_t;
    using SysChar = uint8_t;
#endif


#define Int(v) static_cast<int>(v)
#define Float(v) static_cast<float>(v)
#define Double(v) static_cast<double>(v)

#define S16(v) static_cast<s16>(v)
#define S32(v) static_cast<s32>(v)
#define S64(v) static_cast<s64>(v)

#define U8(v) static_cast<u8>(v)
#define U16(v) static_cast<u16>(v)
#define U32(v) static_cast<u32>(v)
#define U64(v) static_cast<u64>(v)

#define Char16(v) static_cast<char16>(v)

#define SizeT(v) static_cast<size_t>(v)
#define Swap(x, y) std::swap((x), (y))

template <typename T>
constexpr auto& DeConst(T& v)
{
    return const_cast<std::remove_const_t<T>&>(v);
}

template <typename T>
constexpr auto* DeConst(T* v)
{
    return const_cast<std::remove_const_t<T>*>(v);
}

template <typename T>
constexpr const std::remove_reference_t<T>& Const(T& v)
{
    return static_cast<const std::remove_reference_t<T>&>(v);
}

template <typename T>
constexpr const T* Const(T* v)
{
    return static_cast<const T*>(v);
}

// 限制递归算法的深度
#define MAX_RECURSION 100

// 由于一个奇怪的OpenGL API，这是需要指针的奇怪的API
// 输入实际上是偏移的参数
#define CAST_INT_TO_UCHAR_PTR(ptr) ((uint8_t *)(uintptr_t)(ptr))
