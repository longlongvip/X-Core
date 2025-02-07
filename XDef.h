#pragma once

#ifndef unlikely
#   if (defined(__GNUC__) && __GNUC__ >= 3) || defined(__clang__)
#      define unlikely(x) __builtin_expect(!!(x), 0)
#   else
#       define unlikely(x) (x)
#   endif
#endif

#ifndef likely
#   if (defined(__GNUC__) && __GNUC__ >= 3) || defined(__clang__)
#      define likely(x) __builtin_expect(!!(x), 1)
#   else
#       define likely(x) (x)
#   endif
#endif

#if X_SHARED > 0
#   ifdef _WIN32
#       ifdef BUILDING_CO_SHARED
#           define XAPI __declspec(dllexport)
#       else
#           define XAPI __declspec(dllimport)
#       endif
#   else
#       define XAPI __attribute__((visibility("default")))
#   endif
#else
#   define XAPI
#endif

#ifdef _DEBUG
#   define X_DEBUG_DECL, char const* func
#   define x_func             __FUNCTION__
#   define x_file             __FILE__
#   define x_line             __LINE__
#   define x_date             __DATE__
#   define x_time             __TIME__
#   define x_asm              __asm
#   define x_inline           __inline
#   define x_inline_force     __forceinline
#   define x_cdecl            __cdecl
#   define x_stdcall          __stdcall
#   define x_fastcall         __fastcall
#   define x_thiscall         __thiscall
#   define x_packed__
#   define x_aligned(a)     __declspec(align(a))
#   define x_debug_decl  , char const* func_, size_t line_, char const* file_
#   define x_debug_vals  , x_func, x_line, x_file
#   define x_debug_args  , func_, line_, file_
#else
#   define x_debug_decl
#   define x_debug_vals
#   define x_debug_args
#endif

#ifdef _WIN32
#   ifdef _UNICODE
#        define X_NEWLINE L"\r\n"
#   else
#       define X_NEWLINE "\r\n"
#   endif
#else
#   define X_NEWLINE "\n"
#endif

#ifdef __cplusplus
#   define X_EXTERN_C extern "C"
#   define X_EXTERN_C_ENTER extern "C" {
#   define X_EXTERN_C_LEAVE }
#else
#   define X_EXTERN_C
#   define X_EXTERN_C_ENTER
#   define X_EXTERN_C_LEAVE
#endif

#define X_TypeRef(object)                              struct x_##object##_dummy_t{x_int_t dummy;} const* x_##object##_ref_t

 // 宏
#define X_Wrap(x)                                     x
#define X_String(x)                                   #x
#define x_String_Ex(x)                                X_String(x)

#define X_Concat(a, b)                                a##b
#define X_Concat_Ex(a, b)                             X_Concat(a, b)

#define X_Concat3(a, b, c)                            a##b##c
#define X_Concat3_Ex(a, b, c)                         X_Concat3(a, b, c)

#define X_Concat4(a, b, c, d)                         a##b##c##d
#define X_Concat4_Ex(a, b, c, d)                      X_Concat4(a, b, c, d)

#define X_Concat5(a, b, c, d, e)                      a##b##c##d##e
#define X_Concat5_Ex(a, b, c, d, e)                   X_Concat5(a, b, c, d, e)

#define X_Concat6(a, b, c, d, e, f)                   a##b##c##d##e##f
#define X_Concat6_Ex(a, b, c, d, e, f)                X_Concat6(a, b, c, d, e, f)

#define X_Concat7(a, b, c, d, e, f, g)                a##b##c##d##e##f##g
#define X_Concat7_Ex(a, b, c, d, e, f, g)             X_Concat7(a, b, c, d, e, f, g)

#define X_Concat8(a, b, c, d, e, f, g, h)             a##b##c##d##e##f##g##h
#define X_Concat8_Ex(a, b, c, d, e, f, g, h)          X_Concat8(a, b, c, d, e, f, g, h)

#define X_Concat9(a, b, c, d, e, f, g, h, i)          a##b##c##d##e##f##g##h##i
#define X_Concat9_Ex(a, b, c, d, e, f, g, h, i)       X_Concat9(a, b, c, d, e, f, g, h, i)

#define X_Strcat(a, b)                                a b
#define X_Strcat3(a, b, c)                            a b c
#define X_Strcat4(a, b, c, d)                         a b c d
#define X_Strcat5(a, b, c, d, e)                      a b c d e
#define X_Strcat6(a, b, c, d, e, f)                   a b c d e f
#define X_Strcat7(a, b, c, d, e, f, g)                a b c d e f g
#define X_Strcat8(a, b, c, d, e, f, g, h)             a b c d e f g h
#define X_Strcat9(a, b, c, d, e, f, g, h, i)          a b c d e f g h i

/* small */
#ifdef X_CONFIG_SMALL
#   define x_small
#endif

// has feature
#ifdef has_feature
#   define x_has_feature(x) __has_feature(x)
#else
#   define x_has_feature(x) 0
#endif

// has include
#ifdef has_include
#   define x_has_include(x) __has_include(x)
#else
#   define x_has_include(x) 0
#endif

// has built-in
#ifdef has_builtin
#   define x_has_builtin(x) __has_builtin(x)
#else
#   define x_has_builtin(x) 0
#endif

// no_sanitize_address
#if x_has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#   define x_no_sanitize_address__                       __attribute((no_sanitize_address))
#else
#   define x_no_sanitize_address__
#endif

// thread local
#if x_has_feature(c_thread_local)
#   define x_thread_local__                              _Thread_local
#elif defined(X_CONFIG_KEYWORD_HAVE_Thread_local)
#   define x_thread_local__                              _Thread_local
#elif defined(X_CONFIG_KEYWORD_HAVE__thread)
#   define x_thread_local__                              __thread
#elif defined(X_COMPILER_IS_MSVC) || defined(X_COMPILER_IS_BORLAND)
#   define x_thread_local__                              __declspec(thread)
#endif

/* c function overloadable
 *
 * @code
    static __x_inline__ x_void_t test(x_int_t a) __x_overloadable__
    {
        x_trace_i("test1: %d", a);
    }
    static __x_inline__ x_void_t test(x_int_t a, x_int_t b) __x_overloadable__
    {
        x_trace_i("test2: %d %d", a, b);
    }
 * @endcode
 *
 * If the compiler does not support __x_overloadable__, we can use the following code to implement function overload.
 *
 * @code
    #define test_n(a, b, ...) test_impl(a, b)
    #define test(a, args ...) test_n(a, ##args, 0, 0, 0)
    static __x_inline__ x_void_t test_impl(x_int_t a, x_int_t b)
    {
        x_trace_i("test: %d %d", a, b);
    }

    test(1);
    test(1, 2);
 * @endcode
 */
#if defined(X_COMPILER_IS_GCC) || defined(X_COMPILER_IS_CLANG)
#   define x_overloadable__                              __attribute((overloadable))
#else
#   define x_overloadable__
#endif

#if x_has_feature(c_atomic) && !defined(__STDC_NO_ATOMICS__)
#   include <stdatomic.h>
#endif

/*! the type reference keyword for defining x_xxxx_ref_t
 *
 * typedef x_typeref(xxxx);
 *
 *
 * suppress gcc 4.9 on c++ codes warning: 'x_yyyy_t' has a field 'x_yyyy_t::xxxx' whose type uses the anonymous namespace
 *
 * @code
 *
   typedef struct{}*    x_xxxx_ref_t;

   typedef struct x_yyyy_t
   {
       x_xxxx_ref_t    xxxx;

   }x_yyyy_t;

 *
 *
 * @endcode
 *
 */
