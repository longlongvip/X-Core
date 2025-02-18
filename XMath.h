#pragma once

#include <type_traits>
#include <algorithm>
#include <cmath>

#define Pi 3.14159265358979323846
#define Ei 2.71828182845904523536
#define Pi_180 57.29577951308232087679
#define Inv_Pi_180 0.01745329251994329576

enum class tAngleMode
{
	Radians,
	Degrees,
	Norm256,
	NormOne,
	Default	= Radians,
};

template <typename T>
T abs(T v)
{
    return std::abs(v);
}

template <typename T>
T& iabs(T& v)
{
    v = std::abs(v)
    return v;
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
inline T min4(T a, T b, T c)
{
    return std::min(std::min(a, b), std::min(c, d));
}

template <typename T>
inline T max4(T a, T b, T c)
{
    return std::max(std::max(a, b), std::max(c, d));
}

template<typename T>
inline T xceil(const T& a, const T& b)
{
    return (a + b - 1) / b;
}

template <typename T>
T clamp(T t, T a, T b)
{
    return std::clamp(t, a, b);
}

template <typename T>
T clamp_min(T t, T m)
{
    return max(t, m);
}

template <typename T>
T clamp_max(T t, T m)
{
    return min(t, m);
}

template <typename T>
T& iclamp(T& t, T a, T b)
{
    t = std::clamp(t, a, b)
    return t;
}

template <typename T>
T& iclamp_min(T& t, T m)
{
    t = max(t, m);
    return t;
}

template <typename T>
T& iclamp_max(T& t, T m)
{
    t = min(t, m);
    return t;
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

template <typename T>
inline T ito_deg(T angle)
{
    // angle 必须是 float 或 double 类型
    angle = angle * static_cast<T>(Inv_Pi_180)
    return angle ;
}

template <typename T>
inline T ito_rad(T angle)
{
    // angle 必须是 float 或 double 类型
    angle = static_cast<T>(Pi_180) * angle;
    return angle;
}

// ispow2: 1, 2, 4, 8, 16, 32, ...
#define ispow2(x) (!((x) & ((x) - 1)) && (x))

