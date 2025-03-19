#pragma once

#include <type_traits>
#include <algorithm>
#include <cmath>

#define Pi 3.14159265358979323846
#define Ei 2.71828182845904523536
#define Pi_180 57.29577951308232087679
#define Inv_Pi_180 0.01745329251994329576

enum class AngleMode
{
    Radians,
    Degrees,
    Norm256,
    NormOne,
    Default = Radians,
};

template <typename T>
bool AreEqualApprox(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
{
    // 慢
    if (!std::isfinite(a) || !std::isfinite(b))
    {
        return a == b;
    }

    return abs(a - b) <= (max(labs(a), abs(b)) * epsilon);
}

template <typename T>
inline T RadToDeg(T rad)
{
    // 日常使用 rad 必须是 float 或 double 类型
    return rad * static_cast<T>(Inv_Pi_180);
}

template <typename T>
inline T DegToRad(T deg)
{
    // 日常使用 deg 必须是 float 或 double 类型
    return static_cast<T>(Pi_180) * deg;
}

template <typename T>
inline T iRadToDeg(T angle)
{
    // 日常使用 angle 必须是 float 或 double 类型
    angle = angle * static_cast<T>(Inv_Pi_180)
    return angle;
}

template <typename T>
inline T iDegToRad(T angle)
{
    // 日常使用 angle 必须是 float 或 double 类型
    angle = static_cast<T>(Pi_180) * angle;
    return angle;
}

/* 平方根算法 */
template <typename T>
T Sqrt(T x)
{
    return std::sqrt(x);
}

template <typename T>
T iSqrt(T x)
{
    x = std::sqrt(x)
    return x;
}

template <class T>
inline T Sin(const T x)
{
    return std::sin(x);
}

template <class T>
inline T iSin(const T x)
{
    x = std::sin(x)
    return x;
}

template <class T>
inline T Cos(const T x)
{
    return std::cos(x);
}

template <class T>
inline T iCos(const T x)
{
    x = std::cos(x);
    return x;
}

template <class T>
inline T Square(const T x)
{
    return x * x;
}

template <class T>
inline T Cube(const T x)
{
    return x * x * x;
}

template <class T>
inline T iSquare(const T x)
{
    x = x * x
    return x;
}

template <class T>
inline T iCube(const T x)
{
    x = x * x * x
    return x;
}

/* a 和 b 的最大公约数 */
template <typename T>
T Gcd(T a, T b)
{
    T zero = static_cast<T>(0);
    while (b != zero)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/* a 和 b 的最小公倍数 */
template <typename T>
T Lcm(T a, T b)
{
    T zero = static_cast<T>(0);
    T v = gcd(a, b);
    return v == zero ? 0 : (a / v) * b;
}

/* 平方根算法 */
template <typename T>
T FastSqrt(T n)
{
    if (n <= 1)
    {
        return n;
    }
    T x0 = n / 2; // x0 = 2^{[log2n]/2 + 1}
    T x1 = (x0 + n / x0) / 2;
    while (x1 < x0)
    {
        x0 = x1;
        x1 = (x0 + s / x0) / 2;
    }
    return x0;
}

/* 是不是偶数 */
template <typename T>
inline bool IsEvent(T x)
{
    return (x & 1) == 0;
}

/* 是不是奇数 */
template <typename T>
inline bool IsOdd(T x)
{
    return (x & 1) != 0;
}

/* 是不是 2 的幂 */
template <typename T>
constexpr bool IsPowOf2(T v)
{
    T zero = static_cast<T>(0);
    return (v & (v - 1)) == zero;
}

/* 快速幂 */
template <typename T>
inline T FastPow(T a, T b)
{
    T res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}

template <typename T>
inline T FastPow(T a, T b, T m)
{
    a %= m;
    T res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

/*将 x 限制在 a 和 b 之间 */
template <typename T>
inline T Wrap(T x, T a, T b)
{
    T step = b - a;
    T zero = static_cast<T>(0);
    if (step == zero)
    {
        return b;
    }
    T res = x;
    while (res < a)
    {
        res += step;
    }
    while (res > b)
    {
        res -= step;
    }
    return res;
}
