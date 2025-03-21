#pragma once

#include <cstddef>
#include <cstdint>
#include <climits>
#include <utility>

#include "XInternal.h"

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

using f32 = float;
using f64 = double;

#define Int(v) static_cast<int>(v)
#define Float(v) static_cast<float>(v)
#define Double(v) static_cast<double>(v)
#define U8(v) static_cast<u8>(v)
#define U16(v) static_cast<u16>(v)
#define U32(v) static_cast<u32>(v)
#define U64(v) static_cast<u64>(v)
#define SizeT(v) static_cast<size_t>(v)
#define Swap(x, y) std::swap((x), (y))

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

constexpr size_t SizeOfIntMax = static_cast<size_t>(INT_MAX);

template<typename T>
inline bool IsOverflowInt(T v)
{
    if(Int(v) > INT_MAX)
    {
        return true;
    }
    return false;
}

template<typename T>
inline bool IsNullOrEmpty(T* p)
{
    if(p == nullptr)
    {
        return true;
    }
    if(*p = static_cast<T>('\0'))
    {
        return true;
    }
    return false;
}

inline int SafeSizeToInt(const size_t v)
{
    if(v > SizeOfIntMax)
    {
        return 0;
    }
    return Int(v);
}

// 无论如何都必须内联
#ifndef _MUST_INLINE_
#   if defined(X_COMPILER_GCC)
#       define _MUST_INLINE_ __attribute__((always_inline)) inline
#   elif defined(X_COMPILER_MSVC)
#       define _MUST_INLINE_ __forceinline
#   else
#       define _MUST_INLINE_ inline
#   endif
#endif

// 不太可能
#ifndef unlikely
#   if (defined(__GNUC__) && __GNUC__ >= 3) || defined(__clang__)
#      define unlikely(x) __builtin_expect(!!(x), 0)
#   else
#       define unlikely(x) (x)
#   endif
#endif

// 很有可能
#ifndef likely
#   if (defined(__GNUC__) && __GNUC__ >= 3) || defined(__clang__)
#      define likely(x) __builtin_expect(!!(x), 1)
#   else
#       define likely(x) (x)
#   endif
#endif

// 动态库导出 Api
#if X_SHARED > 0
#   ifdef _WIN32
#       ifdef BUILDING_CO_SHARED
#           define XAPI __declspec(dllexport)
#       else
#           define XAPI __declspec(dllimport)
#       endif
#   else
#       define XAPI __attribute__((visibility("default")))
#   endif
#else
#   define XAPI
#endif

// Debug 宏定义
#ifdef _DEBUG
#   define x_func             __FUNCTION__
#   define x_file             __FILE__
#   define x_line             __LINE__
#   define x_date             __DATE__
#   define x_time             __TIME__
#   define x_asm              __asm
#   define x_inline           __inline
#   define x_inline_force     __forceinline
#   define x_cdecl            __cdecl
#   define x_stdcall          __stdcall
#   define x_fastcall         __fastcall
#   define x_thiscall         __thiscall
#   define x_packed__
#   define x_aligned(a)     __declspec(align(a))
#   define x_debug_decl char const* func_, size_t line_, char const* file_
#   define x_debug_vals x_func, x_line, x_file
#   define x_debug_args func_, line_, file_
#else
#   define x_debug_decl
#   define x_debug_vals
#   define x_debug_args
#endif

// 换行宏定义
#ifdef X_PLATFORM_WINDOWS
#   ifdef _UNICODE
#        define X_NEWLINE L"\r\n"
#   else
#       define X_NEWLINE "\r\n"
#   endif
#else
#   define X_NEWLINE "\n"
#endif

#ifdef __cplusplus
#   define X_EXTERN_C extern "C"
#   define X_EXTERN_C_ENTER extern "C" {
#   define X_EXTERN_C_LEAVE }
#else
#   define X_EXTERN_C
#   define X_EXTERN_C_ENTER
#   define X_EXTERN_C_LEAVE
#endif

#define X_TypeRef(object)                              struct x_##object##_dummy_t{x_int_t dummy;} const* x_##object##_ref_t

 // 宏
#define X_Wrap(x)                                     x
#define X_String(x)                                   #x
#define x_String_Ex(x)                                X_String(x)

#define X_Concat(a, b)                                a##b
#define X_Concat_Ex(a, b)                             X_Concat(a, b)

#define X_Concat3(a, b, c)                            a##b##c
#define X_Concat3_Ex(a, b, c)                         X_Concat3(a, b, c)

#define X_Concat4(a, b, c, d)                         a##b##c##d
#define X_Concat4_Ex(a, b, c, d)                      X_Concat4(a, b, c, d)

#define X_Concat5(a, b, c, d, e)                      a##b##c##d##e
#define X_Concat5_Ex(a, b, c, d, e)                   X_Concat5(a, b, c, d, e)

#define X_Concat6(a, b, c, d, e, f)                   a##b##c##d##e##f
#define X_Concat6_Ex(a, b, c, d, e, f)                X_Concat6(a, b, c, d, e, f)

#define X_Concat7(a, b, c, d, e, f, g)                a##b##c##d##e##f##g
#define X_Concat7_Ex(a, b, c, d, e, f, g)             X_Concat7(a, b, c, d, e, f, g)

#define X_Concat8(a, b, c, d, e, f, g, h)             a##b##c##d##e##f##g##h
#define X_Concat8_Ex(a, b, c, d, e, f, g, h)          X_Concat8(a, b, c, d, e, f, g, h)

#define X_Concat9(a, b, c, d, e, f, g, h, i)          a##b##c##d##e##f##g##h##i
#define X_Concat9_Ex(a, b, c, d, e, f, g, h, i)       X_Concat9(a, b, c, d, e, f, g, h, i)

#define X_Strcat(a, b)                                a b
#define X_Strcat3(a, b, c)                            a b c
#define X_Strcat4(a, b, c, d)                         a b c d
#define X_Strcat5(a, b, c, d, e)                      a b c d e
#define X_Strcat6(a, b, c, d, e, f)                   a b c d e f
#define X_Strcat7(a, b, c, d, e, f, g)                a b c d e f g
#define X_Strcat8(a, b, c, d, e, f, g, h)             a b c d e f g h
#define X_Strcat9(a, b, c, d, e, f, g, h, i)          a b c d e f g h i

/* small */
#ifdef X_CONFIG_SMALL
#   define x_small
#endif

// has feature
#ifdef has_feature
#   define x_has_feature(x) __has_feature(x)
#else
#   define x_has_feature(x) 0
#endif

// has include
#ifdef has_include
#   define x_has_include(x) __has_include(x)
#else
#   define x_has_include(x) 0
#endif

// has built-in
#ifdef has_builtin
#   define x_has_builtin(x) __has_builtin(x)
#else
#   define x_has_builtin(x) 0
#endif

// no_sanitize_address
#if x_has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#   define x_no_sanitize_address__                       __attribute((no_sanitize_address))
#else
#   define x_no_sanitize_address__
#endif

// thread local
#if x_has_feature(c_thread_local)
#   define x_thread_local__                              _Thread_local
#elif defined(X_CONFIG_KEYWORD_HAVE_Thread_local)
#   define x_thread_local__                              _Thread_local
#elif defined(X_CONFIG_KEYWORD_HAVE__thread)
#   define x_thread_local__                              __thread
#elif defined(X_COMPILER_MSVC) || defined(X_COMPILER_BORLAND)
#   define x_thread_local__                              __declspec(thread)
#endif

/* c function overloadable
 *
 * @code
    static __x_inline__ x_void_t test(x_int_t a) __x_overloadable__
    {
        x_trace_i("test1: %d", a);
    }
    static __x_inline__ x_void_t test(x_int_t a, x_int_t b) __x_overloadable__
    {
        x_trace_i("test2: %d %d", a, b);
    }
 * @endcode
 *
 * If the compiler does not support __x_overloadable__, we can use the following code to implement function overload.
 *
 * @code
    #define test_n(a, b, ...) test_impl(a, b)
    #define test(a, args ...) test_n(a, ##args, 0, 0, 0)
    static __x_inline__ x_void_t test_impl(x_int_t a, x_int_t b)
    {
        x_trace_i("test: %d %d", a, b);
    }

    test(1);
    test(1, 2);
 * @endcode
 */
#if defined(X_COMPILER_GCC) || defined(X_COMPILER_CLANG)
#   define x_overloadable__ __attribute((overloadable))
#else
#   define x_overloadable__
#endif

#if x_has_feature(c_atomic) && !defined(__STDC_NO_ATOMICS__)
#   include <stdatomic.h>
#endif

/*! the type reference keyword for defining x_xxxx_ref_t
 *
 * typedef x_typeref(xxxx);
 *
 *
 * suppress gcc 4.9 on c++ codes warning: 'x_yyyy_t' has a field 'x_yyyy_t::xxxx' whose type uses the anonymous namespace
 *
 * @code
 *
   typedef struct{}*    x_xxxx_ref_t;

   typedef struct x_yyyy_t
   {
       x_xxxx_ref_t    xxxx;

   }x_yyyy_t;

 *
 *
 * @endcode
 *
 */

#define Swap(x, y) std::swap((x), ((y)))

template <typename T>
T Abs(T v)
{
    return std::abs(v);
}

template <typename T>
T& iAbs(T& v)
{
    v = std::abs(v)
    return v;
}

template <typename T>
int Sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
T Min(T a, T b)
{
    return std::min(a, b);
}

template <typename T>
T Max(T a, T b)
{
    return std::max(a, b);
}

template <typename T>
inline T Min3(T a, T b, T c)
{
    return std::min(std::min(a, b), c);
}

template <typename T>
inline int Min3Index(T a, T b, T c)
{
    return (a > b) ? ((a > c) ? 0 : 2) : ((b > c) ? 1 : 2);
}

template <typename T>
inline T Max3(T a, T b, T c)
{
    return std::max(std::max(a, b), c);
}

template <typename T>
inline int Max3Index(T a, T b, T c)
{
    return (a < b) ? ((a < c) ? 0 : 2) : ((b < c) ? 1 : 2);
}

template <typename T>
inline T Min4(T a, T b, T c)
{
    return std::min(std::min(a, b), std::min(c, d));
}

template <typename T>
inline T Max4(T a, T b, T c)
{
    return std::max(std::max(a, b), std::max(c, d));
}

template<typename T>
inline T Ceil(const T& a, const T& b)
{
    return (a + b - 1) / b;
}

template <typename T>
T Clamp(T t, T a, T b)
{
    return std::clamp(t, a, b);
}

template <typename T>
T ClampMin(T t, T m)
{
    return max(t, m);
}

template <typename T>
T ClampMax(T t, T m)
{
    return min(t, m);
}

template <typename T>
T& iClamp(T& t, T a, T b)
{
    t = std::clamp(t, a, b)
    return t;
}

template <typename T>
T& iClampMin(T& t, T m)
{
    t = max(t, m);
    return t;
}

template <typename T>
T& iClamMax(T& t, T m)
{
    t = min(t, m);
    return t;
}

template <typename T>
inline double Ratio(T h, T w)
{
    return h * static_cast<T>(1) / w;
}

/* 处理 2 和 bit 移动的函数*/
template <typename T>
inline bool is_power_of_2(const T x)
{
    // 如果 x 是 2 的幂，则返回真，否则返回假
	return x && ((x & (x - 1)) == 0);
}

static _MUST_INLINE_ u32 next_power_of_2(u32 x)
{
    if(x == 0)
    {
        return 0;
    }
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return ++x;
}

static _MUST_INLINE_ u32 prev_power_of_2(u32 x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x >> 1);
}

static _MUST_INLINE_ u32 closest_power_of_2(u32 x)
{
    u32 nx = next_power_of_2(x);
    u32 px = prev_power_of_2(x);
    return (nx - x) > (x - px) ? px : nx;
}

static _MUST_INLINE_ int get_shitf_from_power_of_2(u32 p_bits)
{
    for(int i = 0; i < 32; i++)
    {
        if(p_bits == U32(1 << i))
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
static _MUST_INLINE_ T nearest_power_of_2_templated(T x)
{
	--x;
	// The number of operations on x is the base two logarithm
	// of the number of bits in the type. Add three to account
	// for sizeof(T) being in bytes.
	size_t num = get_shift_from_power_of_2(sizeof(T)) + 3;
	// If the compiler is smart, it unrolls this loop.
	// If it's dumb, this is a bit slow.
	for (size_t i = 0; i < num; i++)
    {
		x |= x >> (1 << i);
	}
	return ++x;
}

// Function to find the nearest (bigger) power of 2 to an integer.
static inline unsigned int nearest_shift(unsigned int p_number)
{
	for (int i = 30; i >= 0; i--)
    {
		if (p_number & (1 << i)) 
        {
			return i + 1;
		}
	}
	return 0;
}

template<typename T>
constexpr T floor_log2(T x)
{
    return x < 2 ? x : 1 + floor_log2(x >> 1);
}

template <typename T>
constexpr T get_num_bits(T x)
{
	return floor_log2(x);
}

// 字节序
#if defined(__GNUC__)
#   define BSwap16(x) __builtin_bswap16(x)
#   define BSwap32(x) __builtin_bswap32(x)
#   define BSwap64(x) __builtin_bswap64(x)
#elif defined(_MSC_VER)
#   define BSwap16(x) _byteswap_ushort(x)
#   define BSwap32(x) _byteswap_ulong(x)
#   define BSwap64(x) _byteswap_uint64(x)
#else
static inline u16 BSwap16(u16 x)
{
	return (x >> 8) | (x << 8);
}

static inline u32 BSwap32(u32 x)
 {
	return ((x << 24) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | (x >> 24));
}

static inline u64 BSwap64(u64 x)
{
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
	return x;
}
#endif

enum Endianness
{
    InValid = -1,
    Little,
    Big
};

Endianness get_endianness()
{
    union
	{
		u8 c[2];
		u16 u;
	} a;

	a.c[1] = 0;
	a.c[0] = 1;

	if (a.u == 1)
    {
        return Endianness::Little;
    }
	return Endianness::Big;
}

template<typename T>
inline T get_swap_endian(const T& val)
{
    union endian
    {
        T data;
        u8 bytes[sizeof(T)];
    };

    endian& src = static_cast<endian&> val;
    endian dst;
    int t_size = static_cast<int>(sizeof(T));
    for(int i = 0; i < t_size; i++)
    {
        dst.bytes[i] = src.bytes[t_size - i - 1];
    }
    return dst.data;
}

template<typename T>
inline void swap_endian(const T& val)
{
    union endian
    {
        T data;
        u8 bytes[sizeof(T)];
    };

    endian& src = static_cast<endian&> val;
    int t_size = static_cast<int>(sizeof(T));
    for(int i = 0; i < t_size / 2; i++)
    {
        u8 &a = src.bytes[i];
        u8 &b = src.bytes[t_size - i - 1];

        u8 t = a;
        a = b;
        b = t;
    }
}

template <typename T>
inline void swap_endian(T *a, int numItems)
{
	for (int i = 0; i < numItems; i++)
    {
        swap_endian(a[i]);
    }
}

template <typename T>
inline T ntoh(T val)
{
	if (get_endianness() == Endianness::Big)
    {
        return val;
    }
	return get_swap_endian(val);
}

template <typename T>
inline T hton(T val)
{
	return ntoh(val);
}

// 全局锁
// Global lock macro, relies on the static Mutex::_global_mutex.
void _global_lock();
void _global_unlock();

struct _GlobalLock {
	_GlobalLock() { _global_lock(); }
	~_GlobalLock() { _global_unlock(); }
};

#define GLOBAL_LOCK_FUNCTION _GlobalLock _global_lock_;

// This is needed due to a strange OpenGL API that expects a pointer
// type for an argument that is actually an offset.
#define CAST_INT_TO_UCHAR_PTR(ptr) ((uint8_t *)(uintptr_t)(ptr))

// Home-made index sequence trick, so it can be used everywhere without the costly include of std::tuple.
// https://stackoverflow.com/questions/15014096/c-index-of-type-during-variadic-template-expansion
template <size_t... Is>
struct IndexSequence {};

template <size_t N, size_t... Is>
struct BuildIndexSequence : BuildIndexSequence<N - 1, N - 1, Is...> {};

template <size_t... Is>
struct BuildIndexSequence<0, Is...> : IndexSequence<Is...> {};

// Limit the depth of recursive algorithms when dealing with Array/Dictionary
#define MAX_RECURSION 100
