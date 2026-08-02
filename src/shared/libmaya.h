/* libmaya v0.1.1 (started on 29-Jul-26)
 *
 * General-purpose library for many use-cases.
 *
 * The usage case differs depending on if you are using this library as a
 * single-header library or as a shared-object file. To use it as single-header:
 *
 *     #define MAYA_IMPLEMENTATION
 *     #define MAYA_MODULE_(module or "all")
 *     #include "libmaya.h"
 *
 * To use it as shared object:
 *
 *     #include "libmaya.h"
 *
 * If you are using it as shared-object file, you do not want to define
 * MAYA_IMPLEMENTATION. It duplicates the code.
 *
 * CHANGELOG:
 *   v0.1.1: typos and fixes, remove cpp extern- will be implemented if I want
 *   v0.1.0: basic modules- logging, ANSI, types, and bits
 *
**/

#ifndef MAYA_H
#define MAYA_H

/*----------------------------------------------------------------------------*/

// Get Version

#define MAYA_C89 199409L
#define MAYA_C99 199901L
#define MAYA_C11 201112L
#define MAYA_C17 201710L
#define MAYA_C23 202311L

// Require C99+
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < MAYA_C89
    #error "LIBMAYA: Requires C99 or newer."
#endif

#define MAYA_C_VERSION __STDC_VERSION__

/*----------------------------------------------------------------------------*/

// Sources:
// https://stackoverflow.com/questions/4605842/how-to-identify-platform-compiler-from-preprocessor-macros

// Get Platform
//
// The order matters here, since Linux systems tend to also expose unix-globals,
// Linux needs to be checked first. This applies for both FreeBSD and OpenBSD
// as well.

#if defined(__linux__)
    #define MAYA_PLATFORM "LINUX"
    #define MAYA_OS_LINUX 1

#elif defined(__FreeBSD__)
    #define MAYA_PLATFORM "FREEBSD"
    #define MAYA_OS_FREEBSD 1

#elif defined(__OpenBSD__)
    #define MAYA_PLATFORM "OPENBSD"
    #define MAYA_OS_OPENBSD 1

#elif defined(__APPLE__) || defined(__MACH__)
    #define MAYA_PLATFORM "MACOS"
    #define MAYA_OS_MACOS 1

#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define MAYA_PLATFORM "UNIX"
    #define MAYA_OS_UNIX 1

#elif defined(_WIN64)
    #define MAYA_PLATFORM "WIN64"
    #define MAYA_OS_WIN 1
    #define MAYA_OS_WIN64 1

#elif defined(_WIN32) // _WIN32 is also for _WIN64 so it's after it.
    #define MAYA_PLATFORM "WIN32"
    #define MAYA_OS_WIN 1
    #define MAYA_OS_WIN32 1

#else
    #define MAYA_OS_UNKNOWN 1
#endif

/*----------------------------------------------------------------------------*/

// Compiler Agnostic Macros

#if defined(__clang__)
    #define MAYA_COMPILER_CLANG 1

#elif defined(__GNUC__)
    #define MAYA_COMPILER_GCC 1

#elif defined(_MSC_VER_)
    #define MAYA_COMPILER_MSVC 1

#else
    #define MAYA_COMPILER_UNKNOWN 1
#endif

/*----------------------------------------------------------------------------*/

// Project Macros

// Add Color depending on if color is supported by terminal.
#ifdef MAYA_MODULE_COLORS

#define TODO(msg) printf("[%sTODO%s] (%s - %s:%d) %s\n",\
    MAYA_CB_CYAN, MAYA_C_RESET, __FILE__, __func__, __LINE__, (msg));

#else

#define TODO(msg) printf("[TODO] (%s - %s:%d) %s\n",\
    __FILE__, __func__, __LINE__, (msg));

#endif

/*----------------------------------------------------------------------------*/

// Does this make sense to put here?
#ifdef MAYA_IMPLEMENTATION

/*----------------------------------------------------------------------------*/

#if defined(MAYA_MODULE_LOGS) || defined(MAYA_MODULES_ALL)

#include <stdio.h>

// Colors the text if COLORS module is also defined.
#ifdef MAYA_MODULE_COLORS

#define INFO(msg) printf("[%sINFO%s] (%s - %s:%d) %s\n",\
    MAYA_CB_BLUE, MAYA_C_RESET, __FILE__, __func__, __LINE__, (msg));
#define WARN(msg) printf("[%sWARN%s] (%s - %s:%d) %s\n",\
    MAYA_CB_YELLOW, MAYA_C_RESET, __FILE__, __func__, __LINE__, (msg));
#define ERROR(msg) fprintf(stderr, "[%sERR %s] (%s - %s:%d) %s\n",\
    MAYA_CB_RED, MAYA_C_RESET, __FILE__, __func__, __LINE__, (msg));
#define ERRORC(msg, code) fprintf(stderr, "[%sERRC%s] (%s - %s:%d) %d: %s\n",\
    MAYA_CB_RED, MAYA_C_RESET, __FILE__, __func__, __LINE__, (code), (msg));

#ifdef MAYA_DEBUG
    #define DEBUG(msg) printf("[%sDEBU%s] (%s - %s:%d) %s\n",\
        MAYA_CB_MAGENTA, MAYA_C_RESET, __FILE__, __func__, __LINE__, (msg));
#endif

#else

#define INFO(msg) printf("[INFO] (%s - %s:%d) %s\n",\
    __FILE__, __func__, __LINE__, (msg));
#define WARN(msg) printf("[WARN] (%s - %s:%d) %s\n",\
    __FILE__, __func__, __LINE__, (msg));
#define ERROR(msg) fprintf(stderr, "[ERR ] (%s - %s:%d) %s\n",\
    __FILE__, __func__, __LINE__, (msg));
#define ERRORC(msg, code) fprintf(stderr, "[ERRC] (%s - %s:%d) %d: %s\n",\
    __FILE__, __func__, __LINE__, (code), (msg));

#ifdef MAYA_DEBUG
    #define DEBUG(msg) printf("[DEBU] (%s - %s:%d) %s\n",\
        __FILE__, __func__, __LINE__, (msg));
#endif

#endif
#endif // MAYA_MODULE_LOGS

/*----------------------------------------------------------------------------*/

#if defined(MAYA_MODULE_COLORS) || defined(MAYA_MODULES_ALL)

// Sources:
// https://en.wikipedia.org/wiki/ANSI_escape_code

// MAYA_MODULE_COLORS
//
// These do not work for for every termianl. Find if they are compatible for
// your terminal/use-case.
//
// Terminals that typically support all of these are: Kitty, iTerm2, mintty,
// Windows Terminal, and Konsole. The wikipedia page has some description of
// supported terminals for each escape code.

#define MAYA_C_RESET "\033[39;49m"

#define MAYA_C_RED "\033[31m"
#define MAYA_CB_RED "\033[91m"

#define MAYA_C_GREEN "\033[32m"
#define MAYA_CB_GREEN "\033[92m"

#define MAYA_C_YELLOW "\033[33m"
#define MAYA_CB_YELLOW "\033[93m"

#define MAYA_C_BLUE "\033[34m"
#define MAYA_CB_BLUE "\033[94m"

#define MAYA_C_MAGENTA "\033[35m"
#define MAYA_CB_MAGENTA "\033[95m"

#define MAYA_C_CYAN "\033[36m"
#define MAYA_CB_CYAN "\033[96m"

#define MAYA_C_WHITE "\033[37m"
#define MAYA_CB_WHITE "\033[97m"

#define MAYA_C_BLACK "\033[30m"
#define MAYA_C_GREY "\033[90m"

#endif // MAYA_MODULE_COLORS

/*----------------------------------------------------------------------------*/

#if defined(MAYA_MODULE_ANSI) || defined(MAYA_MODULES_ALL)

// Sources:
// https://en.wikipedia.org/wiki/ANSI_escape_code

// MAYA_MODULE_ANSI
//
// These do not work for for every termianl. Find if they are compatible for
// your terminal/use-case.
//
// Terminals that typically support all of these are: Kitty, iTerm2, mintty,
// Windows Terminal, and Konsole. The wikipedia page has some description of
// supported terminals for each escape code.

// TODO: Add the reverse cases for each. (Not blinking, Not underlined, etc..)
#define MAYA_ANSI_RESET "\033[0m"
#define MAYA_ANSI_BOLD "\033[1m"
#define MAYA_ANSI_DIM "\033[2m"
#define MAYA_ANSI_ITALIC "\033[3m"
#define MAYA_ANSI_UNDERLINE "\033[4m"
#define MAYA_ANSI_INVERT "\033[7m"

#endif // MAYA_MODULES_ANSI

/*----------------------------------------------------------------------------*/

#if defined(MAYA_MODULE_TYPES) || defined(MAYA_MODULES_ALL)

// MAYA_MODULES_TYPES

#include <stdint.h>
#include <stddef.h>

typedef float     f32;
typedef double    f64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef size_t    usize;
typedef ptrdiff_t isize;
typedef uintptr_t uptr;
typedef intptr_t  iptr;

typedef uintmax_t umax;
typedef intmax_t  imax;

#endif // MAYA_MODULE_TYPES

/*----------------------------------------------------------------------------*/

#if defined(MAYA_MODULE_BITS) || defined(MAYA_MODULE_ALL)

// MAYA_MODULE_BITS

#include <stdint.h>

#define BIT_SET(reg, bit)    ((reg) |= (1U << (bit)))
#define BIT_CLEAR(reg, bit)  ((reg) &= ~(1U << (bit)))
#define BIT_TOGGLE(reg, bit) ((reg) ^= (1U << (bit)))
#define BIT_CHECK(reg, bit)  (((reg) >> (bit)) & 1U)

#endif // MAYA_MODULE_BITS

/*----------------------------------------------------------------------------*/

#endif // MAYA_IMPLEMENTATION
#endif // MAYA_H