#pragma once

#include "../Internal/XCompiler.h"
#include "../Types/BaseType.h"

// 字节序
#if defined(X_COMPILER_GCC)
    #define BSwap16(x) __builtin_bswap16(x)
    #define BSwap32(x) __builtin_bswap32(x)
    #define BSwap64(x) __builtin_bswap64(x)
    inline s16 BSwap(s16 x)
    {
        return S16(BSwap16(U16(x)));
    }

    inline s32 BSwap(s32 x)
    {
        return S32(BSwap32(U32(x)));
    }

    inline s64 BSwap(s64 x)
    {
        return S64(BSwap64(U64(x)));
    }

    inline u16 BSwap(u16 x)
    {
        return BSwap16(x);
    }

    inline u32 BSwap(u32 x)
    {
        return BSwap32(x);
    }

    inline u64 BSwap(u64 x)
    {
        return BSwap64(x);
    }

#elif defined(X_COMPILER_MSVC)
    #define BSwap16(x) _byteswap_ushort(x)
    #define BSwap32(x) _byteswap_ulong(x)
    #define BSwap64(x) _byteswap_uint64(x)

    inline s16 BSwap(s16 x)
    {
        return S16(BSwap16(U16(x)));
    }

    inline s32 BSwap(s32 x)
    {
        return S32(BSwap32(U32(x)));
    }

    inline s64 BSwap(s64 x)
    {
        return S64(BSwap64(U64(x)));
    }

    inline u16 BSwap(u16 x)
    {
        return BSwap16(x);
    }

    inline u32 BSwap(u32 x)
    {
        return BSwap32(x);
    }

    inline u64 BSwap(u64 x)
    {
        return BSwap64(x);
    }

#else
    inline s16 BSwap(s16 x)
    {
        return S16(BSwap(U16(x)));
    }

    inline s32 BSwap(s32 x)
    {
        return S32(BSwap(U32(x)));
    }

    inline s64 BSwap(s64 x)
    {
        return S64(BSwap(U64(x)));
    }
    inline u16 BSwap(u16 x)
    {
        return (x >> 8) | (x << 8);
    }

    inline u32 BSwap(u32 x)
    {
        return (x >> 24) | (x << 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8);
    }

    inline u64 BSwap(u64 x)
    {
        return ((x & 0x00000000000000FF) << 56) | ((x & 0x000000000000FF00) << 40) |
            ((x & 0x0000000000FF0000) << 24) | ((x & 0x00000000FF000000) << 8) |
            ((x & 0x000000FF00000000) >> 8) | ((x & 0x0000FF0000000000) >> 24) |
            ((x & 0x00FF000000000000) >> 40) | ((x & 0xFF00000000000000) >> 56);
    }
#endif

template <typename T>
inline T toLittleEndian(T in)
{
    #if ENDIAN_BIG
		return BSwap(in);
    #else
		return in;
    #endif
}

template <typename T>
inline T toBigEndian(T in)
{
    #if ENDIAN_LITTLE
        return BSwap(in);
    #else
        return in;
    #endif
}

template <typename T>
inline T toHostEndian(T in, bool fromLittleEndian)
{
    #if ENDIAN_LITTLE
        return fromLittleEndian ? in : BSwap(in);
    #else
        return fromLittleEndian ? BSwap(in) : in;
    #endif 
}

enum Endian
{
    Little = 0,
    Big
};

Endian getEndian()
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
        return Endian::Little;
    }
	return Endian::Big;
}

template<typename T>
inline T getSwapEndian(const T& val)
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
inline void swapEndian(const T& val)
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
inline void swapEndian(T *a, int numItems)
{
	for (int i = 0; i < numItems; i++)
    {
        swapEndian(a[i]);
    }
}

template <typename T>
inline T ntoh(T val)
{
	if (getEndian() == Endian::Big)
    {
        return val;
    }
	return getSwapEndian(val);
}

template <typename T>
inline T hton(T val)
{
	return ntoh(val);
}
