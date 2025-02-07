#pragma once

#if defined(__LP64__) \
    || defined(__64BIT__) \
    || defined(_LP64) \
    || defined(__x86_64) \
    || defined(__x86_64__) \
    || defined(__amd64) \
    || defined(__amd64__) \
    || defined(__arm64) \
    || defined(__arm64__) \
    || defined(__sparc64__) \
    || defined(__PPC64__) \
    || defined(__ppc64__) \
    || defined(__powerpc64__) \
    || defined(__sw_64) \
    || defined(__loongarch64) \
    || defined(_M_X64) \
    || defined(_M_AMD64) \
    || defined(_M_ARM64) \
    || defined(_M_IA64) || defined(__ia64__) || defined(__ia64) \
    || (defined(__WORDSIZE) && (__WORDSIZE == 64)) \
    || defined(TCC_TARGET_X86_64) \
    || defined(__wasm64) || defined(__wasm64__)

#   define X_CPU_BIT_SIZE    64
#   define X_CPU_BIT_BYTE    8
#   define X_CPU_BIT_ALIGN   7
#   define X_CPU_BIT32       0
#   define X_CPU_BIT64       1
#   define X_CPU_SHIFT       6
#   else
#   define X_CPU_BIT_SIZE    32
#   define X_CPU_BIT_BYTE    4
#   define X_CPU_BIT_ALIGN   3
#   define X_CPU_BIT32       1
#   define X_CPU_BIT64       0
#   define X_CPU_SHIFT       5
#   endif

#if (X_CPU_BIT_BYTE == 8)
#   define x_cpu_aligned   x_aligned(8)
#elif (X_CPU_BIT_BYTE == 4)
#   define x_cpu_aligned   x_aligned(4)
#elif (X_CPU_BIT_BYTE == 2)
#   define x_cpu_aligned   x_aligned(2)
#else
#   error unknown cpu bytes
#endif
