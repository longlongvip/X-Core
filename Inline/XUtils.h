#pragma once

#include <climits>

/** 是否 在 [a, b] 区间 */
template <typename T>
inline bool IsIn(const T &x, const T &a, const T &b)
{
    return a <= x && x <= b;
}

/** 是否 不在 [a, b] 区间 */
template <typename T>
inline bool IsNotIn(const T &x, const T &a, const T &b)
{
    return a > x || x > b;
}

constexpr size_t SizeOfIntMax = static_cast<size_t>(INT_MAX);

/** 是否溢出 */
template <typename T>
inline bool IsOverflowInt(T v)
{
    if (Int(v) > INT_MAX)
    {
        return true;
    }
    return false;
}

/** 返回 是否是 空指针或者空内容 */
template <typename T>
inline bool IsNullOrEmpty(T *p)
{
    if (p == nullptr)
    {
        return true;
    }
    if (*p = static_cast<T>('\0'))
    {
        return true;
    }
    return false;
}

/** 安全地将 size_t 转 int, 如果 大于 IntMax 将返回 0 */
inline int SafeSizeToInt(const size_t v)
{
    if (v > SizeOfIntMax)
    {
        return 0;
    }
    return static_cast<int>(v);
}

/** 通用的 Abs */
template <typename T>
T Abs(T v)
{
    return std::abs(v);
}

/** 通用的原地 Abs */
template <typename T>
T &iAbs(T &v)
{
    v = std::abs(v) return v;
}

/** 通用的 Sign */
template <typename T>
int Sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

/** 通用的 Min */
template <typename T>
T Min(T a, T b)
{
    return std::min(a, b);
}

/** 通用的 Max */
template <typename T>
T Max(T a, T b)
{
    return std::max(a, b);
}

/** 通用的 Min3 */
template <typename T>
inline T Min3(T a, T b, T c)
{
    return std::min(std::min(a, b), c);
}

/** 通用的 Min3 索引 */
template <typename T>
inline int Min3Index(T a, T b, T c)
{
    return (a > b) ? ((a > c) ? 0 : 2) : ((b > c) ? 1 : 2);
}

/** 通用的 Max3 */
template <typename T>
inline T Max3(T a, T b, T c)
{
    return std::max(std::max(a, b), c);
}

/** 通用的 Max3 索引 */
template <typename T>
inline int Max3Index(T a, T b, T c)
{
    return (a < b) ? ((a < c) ? 0 : 2) : ((b < c) ? 1 : 2);
}

/** 通用的 Min4 */
template <typename T>
inline T Min4(T a, T b, T c, T d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

/** 通用的 Max4 */
template <typename T>
inline T Max4(T a, T b, T c, T d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

template <typename T>
inline T Ceil(const T &a, const T &b)
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
T &iClamp(T &t, T a, T b)
{
    t = std::clamp(t, a, b) return t;
}

template <typename T>
T &iClampMin(T &t, T m)
{
    t = max(t, m);
    return t;
}

template <typename T>
T &iClamMax(T &t, T m)
{
    t = min(t, m);
    return t;
}

/* n-分子 d-分母 */
template <typename T>
T MulDiv(T v, T n, T d)
{
    T q = v / d; // 商
    T r = v % d; // 余数
    return q * n + r * n / d;
}

template <typename T>
inline double Ratio(T h, T w)
{
    return h * 1.0 / w;
}

/* 处理 2 和 bit 移动的函数*/
template <typename T>
inline bool isPowerOf2(const T x)
{
    // 如果 x 是 2 的幂，则返回真，否则返回假
    return x && ((x & (x - 1)) == 0);
}

static inline u32 nextPowerOf2(u32 x)
{
    if (x == 0)
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

inline u32 prevPowerOf2(u32 x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x >> 1);
}

inline u32 closestPowerOf2(u32 x)
{
    u32 nx = nextPowerOf2(x);
    u32 px = prevPowerOf2(x);
    return (nx - x) > (x - px) ? px : nx;
}

inline int get_shitf_fromPowerOf2(u32 p_bits)
{
    for (int i = 0; i < 32; i++)
    {
        if (p_bits == U32(1 << i))
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
inline T nearestPowerOf2_templated(T x)
{
    --x;
    // The number of operations on x is the base two logarithm
    // of the number of bits in the type. Add three to account
    // for sizeof(T) being in bytes.
    size_t num = get_shift_fromPowerOf2(sizeof(T)) + 3;
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

template <typename T>
constexpr T floor_log2(T x)
{
    return x < 2 ? x : 1 + floor_log2(x >> 1);
}

template <typename T>
constexpr T get_num_bits(T x)
{
    return floor_log2(x);
}

// 字节相关
int BytesOf16(u16 x)
{
    if (x < 0x100)
    {
        return 1;
    }
    else if (x <= 0xFFFF)
    {
        return 2;
    }
    return -1;
}

int BytesOf32(u32 x)
{
    if (x < 0x100)
    {
        return 1;
    }
    else if (x <= 0x10000)
    {
        return 2;
    }
    else if (x <= 0x1000000)
    {
        return 3;
    }
    else if (x <= 0xFFFFFFFF)
    {
        return 4;
    }
    return -1;
}

int BytesOf64(u64 x)
{
    if (x < 0x100)
    {
        return 1;
    }
    else if (x <= 0x10000)
    {
        return 2;
    }
    else if (x <= 0x1000000)
    {
        return 3;
    }
    else if (x < 0x100000000)
    {
        return 4;
    }
    else if (x < 0x10000000000)
    {
        return 5;
    }
    else if (x < 0x1000000000000)
    {
        return 6;
    }
    else if (x < 0x100000000000000)
    {
        return 7;
    }
    else if (x < 0xFFFFFFFFFFFFFFFF)
    {
        return 8;
    }
    return -1;
}

// Home-made index sequence trick, so it can be used everywhere without the costly include of std::tuple.
// https://stackoverflow.com/questions/15014096/c-index-of-type-during-variadic-template-expansion

// C++ 魔法技巧
template <size_t... Indexes>
struct IndexSequence
{
};

template <size_t N, size_t... Indexes>
struct MakeIndexSequence : MakeIndexSequence<N - 1, N - 1, Indexes...>
{
};

template <size_t... Indexes>
struct MakeIndexSequence<0, Indexes...> : IndexSequence<Indexes...>
{
};
