#pragma once

#include "Internal/XOS.h"

// 动态库导出 Api
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

#ifdef __cplusplus
#   define EXTERN_C_ENTER extern "C" {
#   define EXTERN_C_LEAVE }
#else
#   define EXTERN_C_ENTER
#   define EXTERN_C_LEAVE
#endif

// Debug 宏定义
#ifdef _DEBUG
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
#   define x_debug_decl char const* func_, size_t line_, char const* file_
#   define x_debug_vals x_func, x_line, x_file
#   define x_debug_args func_, line_, file_
#else
#   define x_debug_decl
#   define x_debug_vals
#   define x_debug_args
#endif

#define X_TypeRef(object)                              struct x_##object##_dummy_t{x_int_t dummy;} const* x_##object##_ref_t

// 宏
#define X_ArraySize(a)                                (sizeof(a) / /sizeof(a[0]))

#define X_Wrap(x)                                     x
#define X_String(x)                                   #x
#define X_String_Ex(x)                                X_String(x)

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

#define X_If(OneOrZero, Token1, Token0) X_Concat_Ex(X_Private_If, OneOrZero)(Token1, Token0)
#define X_Private_If_1(Token1, Token0) Token1
#define X_Private_If_0(Token1, Token0) Token0

/* small */
#ifdef X_CONFIG_SMALL
#   define X_Small
#endif

// has feature
#ifdef has_feature
#   define X_HAS_FEATURE(x) __has_feature(x)
#else
#   define X_HAS_FEATURE(x) 0
#endif

// has include
#ifdef has_include
#   define X_Has_Include(x) __has_include(x)
#else
#   define X_Has_Include(x) 0
#endif

// has built-in
#ifdef has_builtin
#   define X_Has_Builtin(x) __has_builtin(x)
#else
#   define X_Has_Builtin(x) 0
#endif

#ifdef has_extension
#	define X_HAS_EXTENSION(_x) __has_extension(_x)
#else
#	define X_HAS_EXTENSION(_x) 0
#endif // defined(__has_extension)

// no_sanitize_address
#if X_HAS_Feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#   define x_no_sanitize_address__                       __attribute((no_sanitize_address))
#else
#   define x_no_sanitize_address__
#endif

// thread local
#if X_HAS_Feature(c_thread_local)
#   define x_thread_local__                              _Thread_local
#elif defined(X_CONFIG_KEYWORD_HAVE_Thread_local)
#   define x_thread_local__                              _Thread_local
#elif defined(X_CONFIG_KEYWORD_HAVE__thread)
#   define x_thread_local__                              __thread
#elif defined(X_COMPILER_MSVC) || defined(X_COMPILER_BORLAND)
#   define x_thread_local__                              __declspec(thread)
#endif

#if defined(X_COMPILER_GCC) || defined(X_COMPILER_CLANG)
#   define x_overloadable__ __attribute((overloadable))
#else
#   define x_overloadable__
#endif

#if X_Has_Feature(c_atomic) && !defined(__STDC_NO_ATOMICS__)
#   include <stdatomic.h>
#endif

#define X_CountOf(x) sizeof(CountOfRequireArrayArgumentT(x))
template<typename T, size_t NumT>
char (&CountOfRequireArrayArgumentT(const T (&)[NumT]) )[NumT];

#define X_OffsetOf(_type, _member) (reinterpret_cast<ptrdiff_t>(&(reinterpret_cast<_type *>(16)->_member)) - ptrdiff_t(16))

#define STUBBED(x)	\
	do																								\
	{																								\
		static bool AlreadySeenThisStubbedSection = false;											\
		if (!AlreadySeenThisStubbedSection)															\
		{																							\
			AlreadySeenThisStubbedSection = true;													\
			fprintf(stderr, "STUBBED: %s at %s:%d (%s)\n", x, __FILE__, __LINE__, __FUNCTION__);	\
		}																							\
	} while (0)

// 简单的 Debug 宏

#ifdef _DEBUG
#   define SAssert(x) \
    if(!(x)) \
    {\
    	printf(__FILE__ "@%d: `" #x "` - Failed | Compilation: " __DATE__ " " __TIME__ "\n", __LINE__); \
    	return(-1); \
	}
#endif

#define ForceExit exit(0)
