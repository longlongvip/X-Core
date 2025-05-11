#pragma once

#include <cstdint>
#include <type_traits>

inline void bless_no_bugs() {}

template <typename To, typename From>
constexpr To Cast(From &&f)
{
    return (To)std::forward<From>(f);
}

template <typename T>
inline int CastInt(T v)
{
    return Cast<int>(v);
}

template <typename T>
inline int64_t CastI64(T v)
{
    return Cast<int64_t>(v);
}

template <typename T>
inline uint8_t CastU8(T v)
{
    return Cast<uint8_t>(v);
}

template <typename T>
inline uint16_t CastU16(T v)
{
    return Cast<uint16_t>(v);
}

template <typename T>
inline uint32_t CastU32(T v)
{
    return Cast<uint32_t>(v);
}

template <typename T>
inline uint64_t CastU64(T v)
{
    return Cast<uint64_t>(v);
}

template <typename T>
inline float CastFloat(T v)
{
    return Cast<float>(v);
}

template <typename T>
inline double CastDouble(T v)
{
    return Cast<double>(v);
}

template <typename T, typename From>
inline constexpr T bitCast(const From &_from)
{
    static_assert(sizeof(T) == sizeof(From), "bx::bitCast failed! T and From must be the same size.");
    static_assert(isTriviallyCopyable<From>(), "bx::bitCast failed! From must be trivially copyable.");
    static_assert(isTriviallyCopyable<T>(), "bx::bitCast failed! T must be trivially copyable.");
    static_assert(isTriviallyConstructible<T>(), "bx::bitCast failed! T must be trivially constructible.");

    return __builtin_bit_cast(T, _from);
}

template <typename T, typename From>
inline T narrowCast(const From &_from /*, Location _location*/)
{
    T to = static_cast<T>(_from);
    //X_ASSERT_LOC(_location, static_cast<From>(to) == _from, "bx::narrowCast failed! Value is truncated!");
    return to;
}

#if defined(X_COMPILER_IS_GCC) && X_COMPILER_VERSION_BE(4, 1)
#define x_offsetof(s, m) (size_t)__builtin_offsetof(s, m)
#else
#define x_offsetof(s, m) (size_t)&(((s const *)0)->m)
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
#define X_AlignU32(x, b) (((uint32)(x) + ((uint32)(b) - 1)) & ~((uint32)(b) - 1))

// align u64
#define X_AlignU64(x, b) (((uint64)(x) + ((uint64)(b) - 1)) & ~((uint64)(b) - 1))

#define X_ArraySize(x) ((sizeof(x) / sizeof(x[0])))

/*
// align by pow2
#define x_align_pow2(x) (((x) > 1)? (x_ispow2(x)? (x) : ((size_t)1 << (32 - x_bits_cl0U32_be((uint32)(x))))) : 1)

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
