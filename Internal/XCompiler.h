#pragma once

constexpr int C89 = 199711;
constexpr int C99 = 199711;
constexpr int C11 = 201103;
constexpr int C17 = 201703;

constexpr int CPlusPlus98Before = 1;
constexpr int CPlusPlus98 = 199711;
constexpr int CPlusPlus11 = 201103;
constexpr int CPlusPlus14 = 201402;
constexpr int CPlusPlus17 = 201703;
constexpr int CPlusPlus20 = 202002;
constexpr int CPlusPlus23 = 202302;

#if defined(_MSC_VER)
#   define X_ASSEMBLER_MASM
#   define X_COMPILER_MSVC (1)
#   define X_COMPILER_VERSION_BT(major, minor)     (_MSC_VER > ((major) * 100 + (minor)))
#   define X_COMPILER_VERSION_BE(major, minor)     (_MSC_VER >= ((major) * 100 + (minor)))
#   define X_COMPILER_VERSION_EQ(major, minor)     (_MSC_VER == ((major) * 100 + (minor)))
#   define X_COMPILER_VERSION_LT(major, minor)     (_MSC_VER < ((major) * 100 + (minor)))
#   define X_COMPILER_VERSION_LE(major, minor)     (_MSC_VER <= ((major) * 100 + (minor)))
#       define X_COMPILER_STRING                   "visual c++"
#   if defined(X_FORCE_MSVC_4_2) && (_MSC_VER == 1020)
#       define X_COMPILER_VERSION_STRING           "visual c++ 4.2"
#   elif (_MSC_VER == 1100)
#       define X_COMPILER_VERSION_STRING           "visual c++ 5.0"
#   elif (_MSC_VER == 1200)
#       define X_COMPILER_VERSION_STRING           "visual c++ 6.0"
#   elif (_MSC_VER == 1300)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net (7.0)"
#   elif (_MSC_VER == 1310)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2003 (7.1)"
#   elif (_MSC_VER == 1400)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2005 (8.0)"
#   elif (_MSC_VER == 1500)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2008 (9.0)"
#   elif (_MSC_VER == 1600)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2010 (10.0)"
#   elif (_MSC_VER == 1700)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2012 (11.0)"
#   elif (_MSC_VER == 1800)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2013 (12.0)"
#   elif (_MSC_VER == 1900)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2015 (14.0)"
#   elif (_MSC_VER == 1910 || _MSC_VER == 1911)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2017 (14.1)"
#   elif (_MSC_VER == 1920)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.0)"
#   elif (_MSC_VER == 1921)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.1)"
#   elif (_MSC_VER == 1922)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.2)"
#   elif (_MSC_VER == 1923)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.3)"
#   elif (_MSC_VER == 1924)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.4)"
#   elif (_MSC_VER == 1925)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.5)"
#   elif (_MSC_VER == 1926)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.6)"
#   elif (_MSC_VER == 1927)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.7)"
#   elif (_MSC_VER == 1928)
#       define X_COMPILER_VERSION_STRING           "visual c++ .net 2019 (16.8)"
#   elif (_MSC_VER == 1929)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2019 (16.10)"
#   elif (_MSC_VER == 1930)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.0)"
#   elif (_MSC_VER == 1931)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.1)"
#   elif (_MSC_VER == 1932)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.2)"
#   elif (_MSC_VER == 1933)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.3)"
#   elif (_MSC_VER == 1934)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.4)"
#   elif (_MSC_VER == 1935)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.5)"
#   elif (_MSC_VER == 1936)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.6)"
#   elif (_MSC_VER == 1937)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.7)"
#   elif (_MSC_VER == 1938)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.8)"
#   elif (_MSC_VER == 1939)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.9)"
#   elif (_MSC_VER == 1940)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.10)"
#   elif (_MSC_VER == 1941)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.22)"
#   elif (_MSC_VER == 1943)
#       define X_COMPILER_VERSION_STRING           "Visual C++ .net 2022 (17.33)"
#   else
#       define X_COMPILER_VERSION_STRING           "unknown visual c++ compiler"
#   endif

// suppress warning
#   pragma warning(disable:4018) // 有符号/无符号不匹配
#   pragma warning(disable:4197) // 忽略强制转换中的顶级 volatile
#   pragma warning(disable:4141) // 使用了多次
#   pragma warning(disable:4996) // 你的代码使用标记为“已弃用”的函数、类成员、变量或 typedef
#   pragma warning(disable:4359) // 为类型指定的对齐小于其数据成员之一的类型的对齐
#   pragma warning(disable:4838) // 
#elif defined(__GNUC__)
#   define X_COMPILER_GCC (1)
#   
#else
#   define X_COMPILER_STRING                       "unknown compiler"
#   define X_COMPILER_VERSION_STRING               "unknown compiler version"
#   define X_COMPILER_IS_UNKNOWN
#endif
