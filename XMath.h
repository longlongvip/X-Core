#pragma once

#include <type_traits>
#include <algorithm>
#include <cmath>

#define Pi 3.14159265358979323846
#define Ei 2.71828182845904523536
#define Pi_180 57.29577951308232087679
#define Inv_Pi_180 0.01745329251994329576

template <typename T>
T abs(T v)
{
    return std::abs(v);
}

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
bool are_approximately_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
{
    if (!std::isfinite(a) || !std::isfinite(b))
    {
        return a == b;
    }
    
    return abs(a - b) <= (max(labs(a), abs(b)) * epsilon);
}

template <typename T>
T min(T a, T b)
{
    return std::min(a, b);
}

template <typename T>
T max(T a, T b)
{
    return std::max(a, b);
}

template <typename T>
inline T min3(T a, T b, T c)
{
    return std::min(std::min(a, b), c);
}

template <typename T>
inline T max3(T a, T b, T c)
{
    return std::max(std::max(a, b), c);
}

template <typename T>
T clamp(T t, T a, T b)
{
    return std::clamp(t, a, b);
}

template <typename T>
inline double hw_ratio(T h, T w)
{
    return h * 1.0 / w;
}

template <typename T>
inline T to_deg(T rad)
{
    // rad 必须是 float 或 double 类型
    return rad * static_cast<T>(Inv_Pi_180);
}

template <typename T>
inline T to_rad(T deg)
{
    // deg 必须是 float 或 double 类型
    return static_cast<T>(Pi_180) * deg;
}

// ispow2: 1, 2, 4, 8, 16, 32, ...
#define ispow2(x) (!((x) & ((x) - 1)) && (x))
