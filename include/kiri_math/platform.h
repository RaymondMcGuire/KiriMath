#ifndef _KIRI_MATH_MACROS_H_
#define _KIRI_MATH_MACROS_H_

#if defined(_WIN32) || defined(_WIN64)
#define BBR_MATH_WINDOWS
#elif defined(__APPLE__)
#define BBR_MATH_APPLE
#ifndef BBR_MATH_IOS
#define BBR_MATH_MACOSX
#endif
#elif defined(linux) || defined(__linux__)
#define BBR_MATH_LINUX
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define BBR_MATH_DEBUG_MODE
#include <cassert>
#define BBR_MATH_ASSERT(x) assert(x)
#else
#define BBR_MATH_ASSERT(x)
#endif

#ifdef __cplusplus
#define BBR_MATH_NON_COPYABLE(ClassName)   \
    ClassName(const ClassName &) = delete; \
    ClassName &operator=(const ClassName &) = delete;
#endif

#ifdef __cplusplus
#include <stdexcept>
#define BBR_MATH_THROW_INVALID_ARG_IF(expression) \
    if (expression)                               \
    {                                             \
        throw std::invalid_argument(#expression); \
    }
#define BBR_MATH_THROW_INVALID_ARG_WITH_MESSAGE_IF(expression, message) \
    if (expression)                                                     \
    {                                                                   \
        throw std::invalid_argument(message);                           \
    }
#endif

#ifdef BBR_MATH_WINDOWS
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#define BBR_MATH_DIAG_STR(s) #s
#define BBR_DIAG_JOINSTR(x, y) BBR_MATH_DIAG_STR(x##y)
#ifdef _MSC_VER
#define BBR_MATH_DIAG_DO_PRAGMA(x) __pragma(#x)
#define BBR_MATH_DIAG_PRAGMA(compiler, x) BBR_MATH_DIAG_DO_PRAGMA(warning(x))
#else
#define BBR_MATH_DIAG_DO_PRAGMA(x) _Pragma(#x)
#define BBR_MATH_DIAG_PRAGMA(compiler, x) BBR_MATH_DIAG_DO_PRAGMA(compiler diagnostic x)
#endif
#if defined(__clang__)
#define BBR_MATH_DISABLE_CLANG_WARNING(clang_option) \
    BBR_MATH_DIAG_PRAGMA(clang, push)                \
    BBR_MATH_DIAG_PRAGMA(clang, ignored BBR_DIAG_JOINSTR(-W, clang_option))
#define BBR_MATH_ENABLE_CLANG_WARNING(clang_option) BBR_MATH_DIAG_PRAGMA(clang, pop)
#define BBR_MATH_DISABLE_MSVC_WARNING(gcc_option)
#define BBR_MATH_ENABLE_MSVC_WARNING(gcc_option)
#define BBR_MATH_DISABLE_GCC_WARNING(gcc_option)
#define BBR_MATH_ENABLE_GCC_WARNING(gcc_option)
#elif defined(_MSC_VER)
#define BBR_MATH_DISABLE_CLANG_WARNING(gcc_option)
#define BBR_MATH_ENABLE_CLANG_WARNING(gcc_option)
#define BBR_MATH_DISABLE_MSVC_WARNING(msvc_errorcode) \
    BBR_MATH_DIAG_PRAGMA(msvc, push)                  \
    BBR_MATH_DIAG_DO_PRAGMA(warning(disable           \
                                    :##msvc_errorcode))
#define BBR_MATH_ENABLE_MSVC_WARNING(msvc_errorcode) BBR_MATH_DIAG_PRAGMA(msvc, pop)
#define BBR_MATH_DISABLE_GCC_WARNING(gcc_option)
#define BBR_MATH_ENABLE_GCC_WARNING(gcc_option)
#elif defined(__GNUC__)
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#define BBR_MATH_DISABLE_CLANG_WARNING(gcc_option)
#define BBR_MATH_ENABLE_CLANG_WARNING(gcc_option)
#define BBR_MATH_DISABLE_MSVC_WARNING(gcc_option)
#define BBR_MATH_ENABLE_MSVC_WARNING(gcc_option)
#define BBR_MATH_DISABLE_GCC_WARNING(gcc_option) \
    BBR_MATH_DIAG_PRAGMA(GCC, push)              \
    BBR_MATH_DIAG_PRAGMA(GCC, ignored BBR_DIAG_JOINSTR(-W, gcc_option))
#define BBR_MATH_ENABLE_GCC_WARNING(gcc_option) BBR_MATH_DIAG_PRAGMA(GCC, pop)
#else
#define BBR_MATH_DISABLE_CLANG_WARNING(gcc_option)
#define BBR_MATH_ENABLE_CLANG_WARNING(gcc_option)
#define BBR_MATH_DISABLE_MSVC_WARNING(gcc_option)
#define BBR_MATH_ENABLE_MSVC_WARNING(gcc_option)
#define BBR_MATH_DISABLE_GCC_WARNING(gcc_option) \
    BBR_MATH_DIAG_PRAGMA(GCC, ignored BBR_DIAG_JOINSTR(-W, gcc_option))
#define BBR_MATH_ENABLE_GCC_WARNING(gcc_option) \
    BBR_MATH_DIAG_PRAGMA(GCC, warning BBR_DIAG_JOINSTR(-W, gcc_option))
#endif
#endif

#endif // _KIRI_MATH_MACROS_H_
