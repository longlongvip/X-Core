#pragma once

#include <cstdint>

constexpr uint32_t FirstByteMask = 0xff000000;
constexpr uint32_t SecondByteMask = 0x00ff0000;
constexpr uint32_t ThirdByteMask = 0x0000ff00;
constexpr uint32_t FourthByteMask = 0x000000ff;

inline void bless_no_bugs() { }

template<typename To, typename From>
constexpr To cast(From&& f) 
{
    return (To) std::forward<From>(f);
}

template<typename T>
inline int cast_int(T v)
{
    return cast<int>(v);
}

template<typename T>
inline int64_t cast_i64(T v)
{
    return cast<int64_t>(v);
}

template<typename T>
inline uint8_t cast_u8(T v)
{
    return cast<uint8_t>(v);
}

template<typename T>
inline uint16_t cast_u16(T v)
{
    return cast<uint16_t>(v);
}

template<typename T>
inline uint32_t cast_u32(T v)
{
    return cast<uint32_t>(v);
}

template<typename T>
inline uint64_t cast_u64(T v)
{
    return cast<uint64_t>(v);
}

template<typename T>
inline float cast_float(T v)
{
    return cast<float>(v);
}

template<typename T>
inline double cast_double(T v)
{
    return cast<double>(v);
}

template<typename T>
inline T x_ceil(const T& a, const T& b)
{
    return (a + b - 1) / b;
}

template<typename T, typename From>
inline T get_byte(From f, int n)
{
    uint32_t f_u32 = cast_u32(f);
    if(n == 1)
    {
        return cast<T>(f_u32 & FirstByteMask);
    } else if(n == 2)
    {
        return cast<T>(f_u32 & SecondByteMask);
    }else if(n == 3)
    {
        return cast<T>(f_u32 & ThirdByteMask);
    }else if(n == 4)
    {
        return cast<T>(f_u32 & FourthByteMask);
    }
    return cast<T>(0);
}

#if defined(X_COMPILER_IS_GCC) && X_COMPILER_VERSION_BE(4, 1)
#   define x_offsetof(s, m) (size_t)__builtin_offsetof(s, m)
#else
#   define x_offsetof(s, m) (size_t)&(((s const*)0)->m)
#endif

// align2
#define X_Align2(x) (((x) + 1) >> 1 << 1)

// align4
#define X_Align4(x) (((x) + 3) >> 2 << 2)

// align8
#define X_Align8(x) (((x) + 7) >> 3 << 3)

// align
#define X_Align(x, b) (((size_t)(x) + ((size_t)(b) - 1)) & ~((size_t)(b) - 1))

// align u32
#define X_Align_u32(x, b) (((uint32)(x) + ((uint32)(b) - 1)) & ~((uint32)(b) - 1))

// align u64
#define X_Align_u64(x, b) (((uint64)(x) + ((uint64)(b) - 1)) & ~((uint64)(b) - 1))

#define X_ArraySize(x) ((sizeof(x) / sizeof(x[0])))

/*
// align by pow2
#define x_align_pow2(x) (((x) > 1)? (x_ispow2(x)? (x) : ((size_t)1 << (32 - x_bits_cl0_u32_be((uint32)(x))))) : 1)

// container of
#define x_container_of(s, m, p) ((s*)(((byte*)(p)) - x_offsetof(s, m)))

// memsizeof
#define x_memsizeof(s, m) sizeof(((s const*)0)->m)

// memtailof
#define x_memtailof(s, m) (x_offsetof(s, m) + x_memsizeof(s, m))

// memdiffof: lm - rm
#define x_memdiffof(s, lm, rm) (x_memtailof(s, lm) - x_memtailof(s, rm))

// check the offset and size of member for struct or union
#define x_memberof_eq(ls, lm, rs, rm)  ((x_offsetof(ls, lm) == x_offsetof(rs, rm)) && (x_memsizeof(ls, lm) == x_memsizeof(rs, rm)))
*/
