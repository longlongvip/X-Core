#pragma once

#include "XType.h"

enum class Endianness
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

inline constexpr u16 swap_endian16(u16 val)
{
	u16 u0 = val & 0x00FF;
	u16 u1 = (val >> 8) & 0x00FF;
	return (u16(u1) | (u16(u0) << 8));
}

inline constexpr u32 swap_endian32(u32 val)
{
	u32 u0 = val & 0x000000FF;
	u32 u1 = (val >> 8) & 0x000000FF;
	u32 u2 = (val >> 16) & 0x000000FF;
	u32 u3 = (val >> 24) & 0x000000FF;
	return (u32(u3) | (u32(u2) << 8) | (u32(u1) << 16) | (u32(u0) << 24));
}

inline constexpr u64 swap_endian64(u64 val)
{
	u64 u0 = val & 0x000000FF;
	u64 u1 = (val >> 8) & 0x000000FF;
	u64 u2 = (val >> 16) & 0x000000FF;
	u64 u3 = (val >> 24) & 0x000000FF;
    u64 u4 = (val >> 32) & 0x000000FF;
    u64 u5 = (val >> 40) & 0x000000FF;
    u64 u6 = (val >> 48) & 0x000000FF;
    u64 u7 = (val >> 56) & 0x000000FF;

	return (
        u64(u7) | (u64(u6) << 8) | (u64(u5) << 16) | (u64(u4) << 24) | 
        u64(u3 << 32) | (u64(u2) << 40) | (u64(u1) << 48) | (u64(u0) << 56)
    );
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
