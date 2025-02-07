#pragma once

#if defined(_WIN32)
#   define WIN32_LEAN_AND_MEAN
#   define _CRT_SECURE_NO_WARNINGS
#   include <windows.h>
#endif

#include <cstdio>  // fprintf() and vsnprintf()
#include <cstring>
#include <cstdarg> // va_start() and va_end()
#include <cstdlib> // abort()

#ifdef _DEBUG
    #define X_ENABLE_ASSERT
#endif

#ifndef X_ASSERT_DEFAULT_LEVEL
#   define X_ASSERT_DEFALUT_LEVEL Debug
#endif

#if (defined(__GNUC__) && ((__GNUC__ * 1000 + __GNUC_MINOR__ * 100) >= 4600)) || defined(__clang__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wvariadic-macros"
#endif

#if defined(__clang__)
#   pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

#ifndef X_ASSERT_H
#   define X_ASSERT_H
#   define X_ASSERT(...)                    X_ASSERT_(x::assert::implementation::AssertLevel::X_ASSERT_DEFAULT_LEVEL, __VA_ARGS__)
#   define X_ASSERT_WARNING(...)            X_ASSERT_(x::assert::implementation::AssertLevel::Warning, __VA_ARGS__)
#   define X_ASSERT_DEBUG(...)              X_ASSERT_(x::assert::implementation::AssertLevel::Debug, __VA_ARGS__)
#   define X_ASSERT_ERROR(...)              X_ASSERT_(x::assert::implementation::AssertLevel::Error, __VA_ARGS__)
#   define X_ASSERT_FATAL(...)              X_ASSERT_(x::assert::implementation::AssertLevel::Fatal, __VA_ARGS__)
#   define X_ASSERT_CUSTOM(level, ...)      X_ASSERT_(level, __VA_ARGS__)

#   define X_ASSERT_USED(...)               X_ASSERT_USED_(__VA_ARGS__)
#   define X_ASSERT_USED_WARNING(...)       X_ASSERT_USED_(x::assert::implementation::AssertLevel::Warning, __VA_ARGS__)
#   define X_ASSERT_USED_DEBUG(...)         X_ASSERT_USED_(x::assert::implementation::AssertLevel::Debug, __VA_ARGS__)
#   define X_ASSERT_USED_ERROR(...)         X_ASSERT_USED_(x::assert::implementation::AssertLevel::Error, __VA_ARGS__)
#   define X_ASSERT_USED_FATAL(...)         X_ASSERT_USED_(x::assert::implementation::AssertLevel::Fatal, __VA_ARGS__)
#   define X_ASSERT_USED_CUSTOM(level, ...) X_ASSERT_USED_(level, __VA_ARGS__)


#   define X_ASSERT_JOIN(lhs, rhs)   X_ASSERT_JOIN_(lhs, rhs)
#   define X_ASSERT_JOIN_(lhs, rhs)  X_ASSERT_JOIN__(lhs, rhs)
#   define X_ASSERT_JOIN__(lhs, rhs) lhs##rhs

#   define X_ASSERT_FILE             __FILE__
#   define X_ASSERT_LINE             __LINE__
#   define X_ASSERT_DATE             __DATE__
#   define X_ASSERT_TIME             __TIME__
#   define X_ASSERT_ASM              __asm
#if defined(__GNUC__) || defined(__clang__)
#   define X_ASSERT_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#   define X_ASSERT_FUNCTION __FUNCSIG__
#elif defined(__SUNPRO_CC)
#   define X_ASSERT_FUNCTION __func__
#else
#   define X_ASSERT_FUNCTION __FUNCTION__
#endif

#if defined(_MSC_VER)
#   define X_ASSERT_ALWAYS_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#   define X_ASSERT_ALWAYS_INLINE inline __attribute__((always_inline))
#else
#   define X_ASSERT_ALWAYS_INLINE inline
#endif

#define X_ASSERT_NO_MACRO

#define X_ASSERT_APPLY_VA_ARGS(M, ...) X_ASSERT_APPLY_VA_ARGS_(M, (__VA_ARGS__))
#define X_ASSERT_APPLY_VA_ARGS_(M, args) M args

#define X_ASSERT_NARG(...) X_ASSERT_APPLY_VA_ARGS(X_ASSERT_NARG_, X_ASSERT_NO_MACRO,##__VA_ARGS__,\
    32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,\
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, X_ASSERT_NO_MACRO)
#define X_ASSERT_NARG_( _0, _1, _2, _3, _4, _5, _6, _7, _8,\
                            _9, _10, _11, _12, _13, _14, _15, _16,\
                            _17, _18, _19, _20, _21, _22, _23, _24,\
                            _25, _26, _27, _28, _29, _30, _31, _32, _33, ...) _33

#define X_ASSERT_HAS_ONE_ARG(...) X_ASSERT_APPLY_VA_ARGS(X_ASSERT_NARG_, X_ASSERT_NO_MACRO,##__VA_ARGS__,\
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, X_ASSERT_NO_MACRO)

#if defined(__GNUC__) || defined(__clang__)
#   define X_ASSERT_LIKELY(arg) __builtin_expect(!!(arg), !0)
#   define X_ASSERT_UNLIKELY(arg) __builtin_expect(!!(arg), 0)
#else
#   define X_ASSERT_LIKELY(arg) (arg)
#   define X_ASSERT_UNLIKELY(arg) (arg)
#endif

#define X_ASSERT_UNUSED(expression) (void)(true ? (void)0 : ((void)(expression)))


#if !defined(X_ASSERT_DEBUG_BREAK)
#   if defined(_WIN32)
        extern void __cdecl __debugbreak(void);
#       define X_ASSERT_DEBUG_BREAK() __debugbreak()
#   else
#       if defined(__APPLE__)
#           include <TargetConditionals.h>
#       endif
#       if defined(__clang__) && !TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#           define X_ASSERT_DEBUG_BREAK() __builtin_debugtrap()
#       elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__)
#           include <signal.h>
#           define X_ASSERT_DEBUG_BREAK() raise(SIGTRAP)
#       elif defined(__GNUC__)
#           define X_ASSERT_DEBUG_BREAK() __builtin_trap()
#       else
#           define X_ASSERT_DEBUG_BREAK() ((void)0)
#       endif
#    endif
#endif

#if (defined (__cplusplus) && (__cplusplus > 199711L)) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 150020706))
#   define X_ASSERT_CXX11
#endif

#if defined(X_ASSERT_CXX11)
#   define X_ASSERT_NULLPTR nullptr
#else
#   define X_ASSERT_NULLPTR 0
#endif

#define X_ASSERT_(level, ...)          X_ASSERT_JOIN(X_ASSERT_, X_ASSERT_HAS_ONE_ARG(__VA_ARGS__))(level, __VA_ARGS__)
#define X_ASSERT_0(level, ...)         X_ASSERT_APPLY_VA_ARGS(X_ASSERT_2, level, __VA_ARGS__)
#define X_ASSERT_1(level, expression)  X_ASSERT_2(level, expression, X_ASSERT_NULLPTR)


#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140050215)

    #if defined(X_ASSERT_DISABLE_IGNORE_LINE)

      #define X_ASSERT_3(level, expression, ...)\
        __pragma(warning(push))\
        __pragma(warning(disable: 4127))\
        do\
        {\
          if (X_ASSERT_LIKELY(expression) || x::assert::implementation::ignoreAllAsserts());\
          else\
          {\
            if (x::assert::implementation::handleAssert(X_ASSERT_FILE, X_ASSERT_LINE, X_ASSERT_FUNCTION, #expression, level, X_ASSERT_NULLPTR, __VA_ARGS__) == x::assert::implementation::AssertAction::Break)\
              X_ASSERT_DEBUG_BREAK();\
          }\
        }\
        while (false)\
        __pragma(warning(pop))

    #else

      #define X_ASSERT_3(level, expression, ...)\
        __pragma(warning(push))\
        __pragma(warning(disable: 4127))\
        do\
        {\
          static bool _ignore = false;\
          if (X_ASSERT_LIKELY(expression) || _ignore || x::assert::implementation::ignoreAllAsserts());\
          else\
          {\
            if (x::assert::implementation::handleAssert(X_ASSERT_FILE, X_ASSERT_LINE, X_ASSERT_FUNCTION, #expression, level, &_ignore, __VA_ARGS__) == x::assert::implementation::AssertAction::Break)\
              X_ASSERT_DEBUG_BREAK();\
          }\
        }\
        while (false)\
        __pragma(warning(pop))

    #endif

  #else

    #if (defined(__GNUC__) && ((__GNUC__ * 1000 + __GNUC_MINOR__ * 100) >= 4600)) || defined(__clang__)
      #define _pragma(x) _Pragma(#x)
      #define _X_ASSERT_WFORMAT_AS_ERROR_BEGIN\
        _pragma(GCC diagnostic push)\
        _pragma(GCC diagnostic error "-Wformat")
      #define _X_ASSERT_WFORMAT_AS_ERROR_END\
        _pragma(GCC diagnostic pop)
    #else
      #define _X_ASSERT_WFORMAT_AS_ERROR_BEGIN
      #define _X_ASSERT_WFORMAT_AS_ERROR_END
    #endif

    #if defined(X_ASSERT_DISABLE_IGNORE_LINE)

      #define X_ASSERT_3(level, expression, ...)\
        do\
        {\
          if (X_ASSERT_LIKELY(expression) || x::assert::implementation::ignoreAllAsserts());\
          else\
          {\
            _X_ASSERT_WFORMAT_AS_ERROR_BEGIN\
            if (x::assert::implementation::handleAssert(X_ASSERT_FILE, X_ASSERT_LINE, X_ASSERT_FUNCTION, #expression, level, X_ASSERT_NULLPTR, __VA_ARGS__) == x::assert::implementation::AssertAction::Break)\
              X_ASSERT_DEBUG_BREAK();\
            _X_ASSERT_WFORMAT_AS_ERROR_END\
          }\
        }\
        while (false)

    #else

      #define X_ASSERT_3(level, expression, ...)\
        do\
        {\
          static bool _ignore = false;\
          if (X_ASSERT_LIKELY(expression) || _ignore || x::assert::implementation::ignoreAllAsserts());\
          else\
          {\
            _X_ASSERT_WFORMAT_AS_ERROR_BEGIN\
            if (x::assert::implementation::handleAssert(X_ASSERT_FILE, X_ASSERT_LINE, X_ASSERT_FUNCTION, #expression, level, &_ignore, __VA_ARGS__) == x::assert::implementation::AssertAction::Break)\
              X_ASSERT_DEBUG_BREAK();\
            _X_ASSERT_WFORMAT_AS_ERROR_END\
          }\
        }\
        while (false)

    #endif

  #endif

#define X_ASSERT_USED_(...)            X_ASSERT_USED_0(X_ASSERT_NARG(__VA_ARGS__), __VA_ARGS__)
#define X_ASSERT_USED_0(N, ...)        X_ASSERT_JOIN(X_ASSERT_USED_, N)(__VA_ARGS__)

#define X_STATIC_ASSERT(...)           X_ASSERT_APPLY_VA_ARGS(X_ASSERT_JOIN(X_STATIC_ASSERT_, X_ASSERT_HAS_ONE_ARG(__VA_ARGS__)), __VA_ARGS__)
#if defined(X_ASSERT_CXX11)
#   define X_STATIC_ASSERT_0(expression, message) static_assert(expression, message)
#else
#   define X_STATIC_ASSERT_0(expression, message)\
    struct X_ASSERT_JOIN(_x_static_assertion_at_line_, X_ASSERT_LINE)\
    {\
        x::assert::implementation::StaticAssertion<static_cast<bool>((expression))> X_ASSERT_JOIN(STATIC_ASSERTION_FAILED_AT_LINE_, X_ASSERT_LINE);\
    };\
    typedef x::assert::implementation::StaticAssertionTest<sizeof(X_ASSERT_JOIN(_x_static_assertion_at_line_, X_ASSERT_LINE))> X_ASSERT_JOIN(_x_static_assertion_test_at_line_, X_ASSERT_LINE)
    // note that we wrap the non existing type inside a struct to avoid warning
    // messages about unused variables when static assertions are used at function
    // scope
    // the use of sizeof makes sure the assertion error is not ignored by SFINAE
#endif

#define X_STATIC_ASSERT_1(expression)  X_STATIC_ASSERT_0(expression, #expression)


#if !defined (X_ASSERT_CXX11)
    namespace x 
    {
        namespace assert
        {
            namespace implementation
            {
                template <bool>
                struct StaticAssertion;

                template <>
                struct StaticAssertion<true>
                {
                }; // StaticAssertion<true>

                template<int i>
                struct StaticAssertionTest
                {
                }; // StaticAssertionTest<int>

            } // namespace implementation
        } // namespace assert
    } // namespace x
#endif

#if !defined(X_ASSERT_DISABLE_STL)
#   if defined(_MSC_VER)
#       pragma warning(push)
#       pragma warning(disable: 4548)
#       pragma warning(disable: 4710)
#   endif
#include <stdexcept>
#   if defined(_MSC_VER)
#       pragma warning(pop)
#   endif
#endif

#if !defined(X_ASSERT_EXCEPTION_MESSAGE_BUFFER_SIZE)
#   define X_ASSERT_EXCEPTION_MESSAGE_BUFFER_SIZE 1024
#endif

#if defined(X_ASSERT_CXX11) && !defined(_MSC_VER)
#   define X_ASSERT_EXCEPTION_NO_THROW noexcept(true)
#else
#   define X_ASSERT_EXCEPTION_NO_THROW throw()
#endif

#if defined(X_ASSERT_CXX11)
#   include <utility>
#endif

namespace x 
{
    namespace assert
    {
#   if !defined(X_ASSERT_DISABLE_STL)
        class AssertionException: public std::exception
#   else
        class AssertionException
#   endif
        {
        public:
            explicit AssertionException(const char* file, int line, const char* function, const char* expression, const char* message);
            AssertionException(const AssertionException& rhs);
            virtual ~AssertionException() X_ASSERT_EXCEPTION_NO_THROW;
            AssertionException& operator = (const AssertionException& rhs);

            virtual const char* what() const X_ASSERT_EXCEPTION_NO_THROW;
            const char* file() const;
            int line() const;
            const char* function() const;
            const char* expression() const;

        private:
            const char* _file;
            int _line;
            const char* _function;
            const char* _expression;

            enum
            {
                request = X_ASSERT_EXCEPTION_MESSAGE_BUFFER_SIZE,
                size = request > sizeof(char*) ? request : sizeof(char*) + 1
            };

            union
            {
                char  _stack[size];
                char* _heap;
            };

            X_STATIC_ASSERT(size > sizeof(char*), "invalid_size");
        }; // AssertionException

        X_ASSERT_ALWAYS_INLINE const char* AssertionException::file() const
        {
            return _file;
        }

        X_ASSERT_ALWAYS_INLINE int AssertionException::line() const
        {
            return _line;
        }

        X_ASSERT_ALWAYS_INLINE const char* AssertionException::function() const
        {
            return _function;
        }

        X_ASSERT_ALWAYS_INLINE const char* AssertionException::expression() const
        {
            return _expression;
        }

        namespace implementation
        {

#           if defined(_MSC_VER) && !defined(_CPPUNWIND)
#               if !defined(X_ASSERT_DISABLE_EXCEPTIONS)
#                   define X_ASSERT_DISABLE_EXCEPTIONS
#               endif
#           endif

#           if !defined(X_ASSERT_DISABLE_EXCEPTIONS)
                template<typename E>
                inline void throwException(const E& e)
                {
                    throw e;
                }
#           else
                // user defined, the behavior is undefined if the function returns
                void throwException(const x::assert::AssertionException& e);
#           endif

            namespace AssertLevel
            {
                enum AssertLevel
                {
                    Warning = 32,
                    Debug   = 64,
                    Error   = 128,
                    Fatal   = 256
                }; // AssertLevel
            } // AssertLevel

            namespace AssertAction 
            {
                enum AssertAction
                {
                    None,
                    Abort,
                    Break,
                    Ignore,
#               if !defined(X_ASSERT_DISABLE_IGNORE_LINE)
                    IgnoreLine,
#               endif
                    IgnoreAll,
                    Throw
                }; // AssertAction

            } // AssertAction

#           if !defined(X_ASSERT_CALL)
#               define X_ASSERT_CALL
#           endif

            typedef AssertAction::AssertAction (X_ASSERT_CALL *AssertHandler)(const char* file, int line, const char* function, const char* expression, int level, const char* message);
    
#           if defined(__GNUC__) || defined(__clang__)
#               define X_ASSERT_HANDLE_ASSERT_FORMAT __attribute__((format (printf, 7, 8)))
#           else
#               define X_ASSERT_HANDLE_ASSERT_FORMAT
#           endif

#           if !defined(X_ASSERT_FUNCSPEC)
#               define X_ASSERT_FUNCSPEC
#           endif

            X_ASSERT_FUNCSPEC AssertAction::AssertAction X_ASSERT_CALL handleAssert(const char* file, int line, const char* function, const char* expression, int level, bool* ignoreLine, const char* message, ...) X_ASSERT_HANDLE_ASSERT_FORMAT;
            X_ASSERT_FUNCSPEC AssertHandler X_ASSERT_CALL setAssertHandler(AssertHandler handler);
            X_ASSERT_FUNCSPEC void X_ASSERT_CALL ignoreAllAsserts(bool value);
            X_ASSERT_FUNCSPEC bool X_ASSERT_CALL ignoreAllAsserts();


#           if defined(X_ASSERT_CXX11)
                template<int level, typename T>
                class AssertUsedWrapper
                {
                public:
                    AssertUsedWrapper(T&& t);
                    ~AssertUsedWrapper() X_ASSERT_EXCEPTION_NO_THROW;

                    operator T();

                private:
                    const AssertUsedWrapper& operator = (const AssertUsedWrapper&); // not implemented on purpose (and only VS2013 supports deleted functions)

                    T t;
                    mutable bool used;

                }; // AssertUsedWrapper<int, T>

                template<int level, typename T>
                inline AssertUsedWrapper<level, T>::AssertUsedWrapper(T&& _t)
                : t(std::forward<T>(_t)), used(false)
                {}

                template<int level, typename T>
                inline AssertUsedWrapper<level, T>::operator T()
                {
                used = true;
                return std::move(t);
                }

                template<int level, typename T>
                inline AssertUsedWrapper<level, T>::~AssertUsedWrapper() X_ASSERT_EXCEPTION_NO_THROW
                {
                X_ASSERT_3(level, used, "unused value");
                }

#           else
                template<int level, typename T>
                class AssertUsedWrapper
                {
                public:
                AssertUsedWrapper(const T& t);
                AssertUsedWrapper(const AssertUsedWrapper& rhs);
                ~AssertUsedWrapper() X_ASSERT_EXCEPTION_NO_THROW;

                operator T() const;

                private:
                const AssertUsedWrapper& operator = (const AssertUsedWrapper&); // not implemented on purpose

                T t;
                mutable bool used;

                }; // AssertUsedWrapper<int, T>

                template<int level, typename T>
                X_ASSERT_ALWAYS_INLINE AssertUsedWrapper<level, T>::AssertUsedWrapper(const T& _t)
                : t(_t), used(false)
                {}

                template<int level, typename T>
                X_ASSERT_ALWAYS_INLINE AssertUsedWrapper<level, T>::AssertUsedWrapper(const AssertUsedWrapper& rhs)
                : t(rhs.t), used(rhs.used)
                {}

                // /!\ GCC is not so happy if we inline that destructor
                template<int level, typename T>
                AssertUsedWrapper<level, T>::~AssertUsedWrapper() X_ASSERT_EXCEPTION_NO_THROW
                {
                X_ASSERT_3(level, used, "unused value");
                }

                template<int level, typename T>
                X_ASSERT_ALWAYS_INLINE AssertUsedWrapper<level, T>::operator T() const
                {
                used = true;
                return t;
                }

#           endif
        } // namespace implementation
#   endif
    } // namespace assert
} // namespace x


#undef X_ASSERT_2
#undef X_ASSERT_USED_1
#undef X_ASSERT_USED_2

#if defined(_MSC_VER) && defined(_PREFAST_)
#   define X_ASSERT_2(level, expression, ...) __analysis_assume(!!(expression))
#   define X_ASSERT_USED_1(type)              type
#   define X_ASSERT_USED_2(level, type)       type
#elif defined(__clang__) && defined(__clang_analyzer__)
    void its_going_to_be_ok(bool expression) __attribute__((analyzer_noreturn));
#   define X_ASSERT_2(level, expression, ...) its_going_to_be_ok(!!(expression))
#   define X_ASSERT_USED_1(type)              type
#   define X_ASSERT_USED_2(level, type)       type
#else
#   if X_ASSERT_ENABLED
#   define X_ASSERT_2(level, expression, ...) X_ASSERT_3(level, expression, __VA_ARGS__)
#   define X_ASSERT_USED_1(type)              x::assert::implementation::AssertUsedWrapper<x::assert::implementation::AssertLevel::X_ASSERT_DEFAULT_LEVEL, type>
#   define X_ASSERT_USED_2(level, type)       x::assert::implementation::AssertUsedWrapper<level, type>
#else
#   define X_ASSERT_2(level, expression, ...) X_ASSERT_UNUSED(expression)
#   define X_ASSERT_USED_1(type)              type
#   define X_ASSERT_USED_2(level, type)       type
#endif

#endif

#if (defined(__GNUC__) && ((__GNUC__ * 1000 + __GNUC_MINOR__ * 100) >= 4600)) || defined(__clang__)
  #pragma GCC diagnostic pop
#endif

/*实现*/

#if defined(__APPLE__)
#   include <TargetConditionals.h>
#endif

#if defined(__ANDROID__) || defined(ANDROID)
#   include <android/log.h>
#   if !defined(X_ASSERT_LOG_TAG)
#       define X_ASSERT_LOG_TAG "X_ASSERT"
#   endif
#endif

//#define X_ASSERT_LOG_FILE "/tmp/assert.txt"
//#define X_ASSERT_LOG_FILE_TRUNCATE

// malloc and free are only used by AssertionException implemented in terms of
// short string optimization.
// However, no memory allocation happens if
// X_ASSERT_EXCEPTION_MESSAGE_BUFFER_SIZE == X_ASSERT_MESSAGE_BUFFER_SIZE
// which is the default.
#if !defined(X_ASSERT_MALLOC)
#   define X_ASSERT_MALLOC(size) malloc(size)
#endif

#if !defined(X_ASSERT_FREE)
#   define X_ASSERT_FREE(p) free(p)
#endif

#if !defined(X_ASSERT_MESSAGE_BUFFER_SIZE)
#   define X_ASSERT_MESSAGE_BUFFER_SIZE X_ASSERT_EXCEPTION_MESSAGE_BUFFER_SIZE
#endif

#if !defined(X_ASSERT_ABORT)
#   define X_ASSERT_ABORT abort
#endif

namespace
{
    namespace AssertLevel = x::assert::implementation::AssertLevel;
    namespace AssertAction = x::assert::implementation::AssertAction;
    typedef int (*printHandler)(FILE* out, int, const char* format, ...);

#if defined(X_ASSERT_LOG_FILE) && defined(X_ASSERT_LOG_FILE_TRUNCATE)
    struct LogFileTruncate
    {
        LogFileTruncate()
        {
            if (FILE* f = fopen(X_ASSERT_LOG_FILE, "w"))
            {
                fclose(f);
            }
        }
    };
    static LogFileTruncate truncate;
#endif

    int print(FILE* out, int level, const char* format, ...)
    {
        va_list args;
        int count;

        va_start(args, format);
        count = vfprintf(out, format, args);
        fflush(out);
        va_end(args);

    #if defined(X_ASSERT_LOG_FILE)
        struct Local
        {
            static void log(const char* _format, va_list _args)
            {
                if (FILE* f = fopen(X_ASSERT_LOG_FILE, "a"))
                {
                    vfprintf(f, _format, _args);
                    fclose(f);
                }
            }
        };

        va_start(args, format);
        Local::log(format, args);
        va_end(args);
    #endif

    #if defined(_WIN32)
        char buffer[X_ASSERT_MESSAGE_BUFFER_SIZE];
        va_start(args, format);
        vsnprintf(buffer, X_ASSERT_MESSAGE_BUFFER_SIZE, format, args);
        ::OutputDebugStringA(buffer);
        va_end(args);
    #endif

    #if defined(__ANDROID__) || defined(ANDROID)
        int priority = ANDROID_LOG_VERBOSE;

        if (level >= AssertLevel::Debug)
            priority = ANDROID_LOG_DEBUG;
        else if (level >= AssertLevel::Warning)
            priority = ANDROID_LOG_WARN;
        else if (level >= AssertLevel::Error)
            priority = ANDROID_LOG_ERROR;
        else if (level >= AssertLevel::Fatal)
            priority = ANDROID_LOG_FATAL;

        va_start(args, format);
        __android_log_vprint(priority, X_ASSERT_LOG_TAG, format, args);
        va_start(args, format);
    #else
        X_ASSERT_UNUSED(level);
    #endif

        return count;
    }

    int formatLevel(int level, const char* expression, FILE* out, printHandler print)
    {
        const char* levelstr = 0;

        switch (level)
        {
            case AssertLevel::Debug:
                levelstr = "DEBUG";
                break;
            case AssertLevel::Warning:
                levelstr = "WARNING";
                break;
            case AssertLevel::Error:
                levelstr = "ERROR";
                break;
            case AssertLevel::Fatal:
                levelstr = "FATAL";
                break;

            default:
                break;
        }

        if (levelstr)
        {
            return print(out, level, "Assertion '%s' failed (%s)\n", expression, levelstr);
        } 
        else
        {
            return print(out, level, "Assertion '%s' failed (level = %d)\n", expression, level);
        }    
    }

    AssertAction::AssertAction X_ASSERT_CALL _defaultHandler( const char* file, int line, const char* function, const char* expression, int level, const char* message)
    {
#   if defined(_WIN32)
        if (::GetConsoleWindow() == NULL)
        {
        if (::AllocConsole())
        {
                (void)freopen("CONIN$", "r", stdin);
                (void)freopen("CONOUT$", "w", stdout);
                (void)freopen("CONOUT$", "w", stderr);

                SetFocus(::GetConsoleWindow());
        }
        }
    #endif

        formatLevel(level, expression, stderr, reinterpret_cast<printHandler>(print));
        print(stderr, level, "  in file %s, line %d\n  function: %s\n", file, line, function);

        if (message)
        {
            print(stderr, level, "  with message: %s\n\n", message);
        }
        
        if (level < AssertLevel::Debug)
        {
            return AssertAction::None;
        }
        else if (AssertLevel::Debug <= level && level < AssertLevel::Error)
        {
#       if (!TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR) && (!defined(__ANDROID__) && !defined(ANDROID)) || defined(X_ASSERT_DEFAULT_HANDLER_STDIN)
            for (;;)
            {
#               if defined(X_ASSERT_DISABLE_IGNORE_LINE)
                    fprintf(stderr, "Press (I)gnore / Ignore (A)ll / (D)ebug / A(b)ort: ");
#               else
                    fprintf(stderr, "Press (I)gnore / Ignore (F)orever / Ignore (A)ll / (D)ebug / A(b)ort: ");
#               endif
                fflush(stderr);

                char buffer[256];
                if (!fgets(buffer, sizeof(buffer), stdin))
                {
                    clearerr(stdin);
                    fprintf(stderr, "\n");
                    fflush(stderr);
                    continue;
                }

                // we eventually skip the leading spaces but that's it
                char input[2] = {'b', 0};
                if (sscanf(buffer, " %1[a-zA-Z] ", input) != 1)
                {
                    continue;
                }
            

                switch (*input)
                {
                    case 'b':
                    case 'B':
                        return AssertAction::Abort;

                    case 'd':
                    case 'D':
                        return AssertAction::Break;

                    case 'i':
                    case 'I':
                        return AssertAction::Ignore;

#               if !defined(X_ASSERT_DISABLE_IGNORE_LINE)
                    case 'f':
                    case 'F':
                        return AssertAction::IgnoreLine;
#               endif

                    case 'a':
                    case 'A':
                        return AssertAction::IgnoreAll;

                    default:
                        break;
                }
            }
#       else
            return AssertAction::Break;
#       endif
        }
        else if (AssertLevel::Error <= level && level < AssertLevel::Fatal)
        {
            return AssertAction::Throw;
        }
        return AssertAction::Abort;
    }

    void _throw(const char* file, int line, const char* function, const char* expression, const char* message)
    {
        using x::assert::implementation::throwException;
        throwException(x::assert::AssertionException(file, line, function, expression, message));
    }
}

namespace x 
{
    namespace assert
    {
        AssertionException::AssertionException(const char* file, int line, const char* function, const char* expression, const char* message)
        : _file(file), _line(line), _function(function), _expression(expression), _heap(X_ASSERT_NULLPTR)
        {
            if (!message)
            {
                memset(_stack, 0, sizeof(char) * size);
                return;
            }

            size_t length = strlen(message);

            if (length < size) // message is short enough for the stack buffer
            {
                memcpy(_stack, message, sizeof(char) * length);
                memset(_stack + length, 0, sizeof(char) * (size - length)); // pad with 0
            }
            else // allocate storage on the heap
            {
                _heap = static_cast<char*>(X_ASSERT_MALLOC(sizeof(char) * (length + 1)));

                if (!_heap) // allocation failed
                {
                    memcpy(_stack, message, sizeof(char) * (size - 1)); // stack fallback, truncate :/
                    _stack[size - 1] = 0;
                }
                else
                {
                    memcpy(_heap, message, sizeof(char) * length); // copy the message
                    _heap[length] = 0;
                    _stack[size - 1] = 1; // mark the stack
                }
            }
        }

        AssertionException::AssertionException(const AssertionException& rhs)
        : _file(rhs._file), _line(rhs._line), _function(rhs._function), _expression(rhs._expression)
        {
            const char* message = rhs.what();
            size_t length = strlen(message);

            if (length < size) // message is short enough for the stack buffer
            {
                memcpy(_stack, message, sizeof(char) * size); // pad with 0
            }
            else // allocate storage on the heap
            {
                _heap = static_cast<char*>(X_ASSERT_MALLOC(sizeof(char) * (length + 1)));

                if (!_heap) // allocation failed
                {
                    memcpy(_stack, message, sizeof(char) * (size - 1)); // stack fallback, truncate :/
                    _stack[size - 1] = 0;
                }
                else
                {
                    memcpy(_heap, message, sizeof(char) * length); // copy the message
                    _heap[length] = 0;
                    _stack[size - 1] = 1; // mark the stack
                }
            }
        }

        AssertionException::~AssertionException() X_ASSERT_EXCEPTION_NO_THROW
        {
            if (_stack[size - 1])
            {
                X_ASSERT_FREE(_heap);
            }
            _heap = X_ASSERT_NULLPTR; // in case the exception object is destroyed twice
            _stack[size - 1] = 0;
        }

        AssertionException& AssertionException::operator = (const AssertionException& rhs)
        {
            if (&rhs == this)
            {
                return *this;
            }

            const char* message = rhs.what();
            size_t length = strlen(message);

            if (length < size) // message is short enough for the stack buffer
            {
                if (_stack[size - 1])
                {
                    X_ASSERT_FREE(_heap);
                }
                memcpy(_stack, message, sizeof(char) * size);
            }
            else // allocate storage on the heap
            {
                if (_stack[size - 1])
                {
                    size_t _length = strlen(_heap);

                    if (length <= _length)
                    {
                        memcpy(_heap, message, sizeof(char) * _length); // copy the message, pad with 0
                        return *this;
                    }
                    else
                    {
                        X_ASSERT_FREE(_heap);
                    }
                }

                _heap = static_cast<char*>(X_ASSERT_MALLOC(sizeof(char) * (length + 1)));

                if (!_heap) // allocation failed
                {
                    memcpy(_stack, message, sizeof(char) * (size - 1)); // stack fallback, truncate :/
                    _stack[size - 1] = 0;
                }
                else
                {
                    memcpy(_heap, message, sizeof(char) * length); // copy the message
                    _heap[length] = 0;
                    _stack[size - 1] = 1; // mark the stack
                }
            }

            _file = rhs._file;
            _line = rhs._line;
            _function = rhs._function;
            _expression = rhs._expression;

            return *this;
        }

        const char* AssertionException::what() const X_ASSERT_EXCEPTION_NO_THROW
        {
            return _stack[size - 1] ? _heap : _stack;
        }

        namespace implementation 
        {
            namespace 
            {
                bool _ignoreAll = false;
            }

            void X_ASSERT_CALL ignoreAllAsserts(bool value)
            {
                _ignoreAll = value;
            }

            bool X_ASSERT_CALL ignoreAllAsserts()
            {
                return _ignoreAll;
            }

            namespace
            {
                AssertHandler _handler = _defaultHandler;
            }

            AssertHandler X_ASSERT_CALL setAssertHandler(AssertHandler handler)
            {
                AssertHandler previous = _handler;

                _handler = handler ? handler : _defaultHandler;

                return previous;
            }

            AssertAction::AssertAction X_ASSERT_CALL handleAssert(const char* file,int line, const char* function, const char* expression, int level, bool* ignoreLine, const char* message, ...)
            {
                char message_[X_ASSERT_MESSAGE_BUFFER_SIZE] = {0};
                const char* file_;

                if (message)
                {
                    va_list args;
                    va_start(args, message);
                    vsnprintf(message_, X_ASSERT_MESSAGE_BUFFER_SIZE, message, args);
                    va_end(args);

                    message = message_;
                }

#           if defined(_WIN32)
                file_ = strrchr(file, '\\');
#           else
                file_ = strrchr(file, '/');
#           endif // #if defined(_WIN32)

                file = file_ ? file_ + 1 : file;
                AssertAction::AssertAction action = _handler(file, line, function, expression, level, message);

                switch (action)
                {
                    case AssertAction::Abort:
                        X_ASSERT_ABORT();

#               if !defined(X_ASSERT_DISABLE_IGNORE_LINE)
                    case AssertAction::IgnoreLine:
                        *ignoreLine = true;
                        break;
#               else
                        X_ASSERT_UNUSED(ignoreLine);
#               endif

                    case AssertAction::IgnoreAll:
                        ignoreAllAsserts(true);
                        break;

                    case AssertAction::Throw:
                        _throw(file, line, function, expression, message);
                        break;

                    case AssertAction::Ignore:
                    case AssertAction::Break:
                    case AssertAction::None:
                    default:
                        return action;
                }
                return AssertAction::None;
            }

        } // namespace implementation
    } // namespace assert
} // namespace x
