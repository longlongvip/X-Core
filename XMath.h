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
	Default	= Radians,
};

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
