#define MAYA_IMPLEMENTATION

// Use this to test all modules:
// #define MAYA_MODULES_ALL

// Testing Debugs
#define MAYA_DEBUG

// You can just comment out the ones you don't want to test.
#define MAYA_MODULE_TYPES
#define MAYA_MODULE_BITS
#define MAYA_MODULE_LOGS
#define MAYA_MODULE_ANSI

#include <stdint.h>
#include <stdio.h>
#include "libmaya.h"

#define TEST(expr, msg)\
    do {\
        if (!(expr)) {\
            printf("[FAIL %s:%d] %s\n", __FILE__, __LINE__, msg);\
            failures++;\
        }\
    } while (0);

/*----------------------------------------------------------------------------*/

int main(void)
{
    int failures = 0;
    printf("\n");

/*----------------------------------------------------------------------------*/

// Test Operating System & Compiler define statements:
#ifndef MAYA_OS_UNKNOWN
    printf("MAYA_OS: %s\n", MAYA_OS);
#else
    printf("MAYA_OS: Unknown OS\n");
#endif

#ifndef MAYA_COMPILER_UNKNOWN
    printf("MAYA_COMPILER: %s\n", MAYA_COMPILER);
#endif

    printf("\n");

// Testing Project Macros
#ifdef MAYA_MODULE_LOGS
    printf("[ MAYA_MODULE_LOGS ]\n");

    // `if (1)` is to test if I need do-while loops or not.
    if (1)
        TODO("Testing TODO Macro");
    if (1)
        INFO("Test Info Log");
    if (1)
        WARN("Test Warn Log");
    if (1)
        DEBUG("Test Debug");
    if (1)
        ERROR("Test Error Log");
    if (1)
        ERRORC("Test Error Log", 18);

    printf("\n");

#else
    printf("[TESTS] Ignoring MAYA_MODULE_LOGS\n");
#endif

/*----------------------------------------------------------------------------*/

#ifdef MAYA_MODULE_ANSI
    printf("[ MAYA_MODULE_ANSI ]\n");
    printf("  %sCOLOR_RED%s\n", COLOR_RED, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_RED%s\n", COLOR_BRIGHT_RED, COLOR_RESET);
    printf("  %sCOLOR_GREEN%s\n", COLOR_GREEN, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_GREEN%s\n", COLOR_BRIGHT_GREEN, COLOR_RESET);
    printf("  %sCOLOR_YELLOW%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_YELLOW%s\n", COLOR_BRIGHT_YELLOW, COLOR_RESET);
    printf("  %sCOLOR_BLUE%s\n", COLOR_BLUE, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_BLUE%s\n", COLOR_BRIGHT_BLUE, COLOR_RESET);
    printf("  %sCOLOR_MAGENTA%s\n", COLOR_MAGENTA, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_MAGENTA%s\n", COLOR_BRIGHT_MAGENTA, COLOR_RESET);
    printf("  %sCOLOR_CYAN%s\n", COLOR_CYAN, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_CYAN%s\n", COLOR_BRIGHT_CYAN, COLOR_RESET);
    printf("  %sCOLOR_WHITE%s\n", COLOR_WHITE, COLOR_RESET);
    printf("  %sCOLOR_BRIGHT_WHITE%s\n", COLOR_BRIGHT_WHITE, COLOR_RESET);
    printf("  %sCOLOR_BLACK%s\n", COLOR_BLACK, COLOR_RESET);
    printf("  %sCOLOR_GREY%s\n", COLOR_GREY, COLOR_RESET);
    printf("\n");

    printf("  %sANSI_BOLD%s\n", ANSI_BOLD, ANSI_RESET);
    printf("  %sANSI_DIM%s\n", ANSI_DIM, ANSI_RESET);
    printf("  %sANSI_ITALICS%s\n", ANSI_ITALIC, ANSI_RESET);
    printf("  %sANSI_UNDERLINE%s\n", ANSI_UNDERLINE, ANSI_RESET);
    printf("  %sANSI_INVERT%s\n", ANSI_INVERT, ANSI_RESET);
    printf("\n");

#else
    printf("[TESTS] Ignoring MAYA_MODULE_ANSI\n");
#endif

/*----------------------------------------------------------------------------*/

#ifdef MAYA_MODULE_TYPES
    printf("[ MAYA_MODULE_TYPES ]");
    TEST(sizeof(u8) == 1, "u8 is not 8 bits");
    TEST(sizeof(u16) == 2, "u16 is not 16 bits");
    TEST(sizeof(u32) == 4, "u32 is not 32 bits");
    TEST(sizeof(u64) == 8, "u64 is not 64 bits");

    TEST(sizeof(uptr) == sizeof(void *), "uptr does not match pointer size");
    TEST(sizeof(iptr) == sizeof(void *), "uptr does not match pointer size");

    TEST(( (i32) - 1 ) < 0, "i32 is not signed");
    TEST(( (i64) - 1 ) < 0, "i64 is not signed");
    printf("\n");

#else
    printf("[TESTS] Ignoring MAYA_MODULE_TYPES\n");
#endif // MAYA_MODULE_TYPES

/*----------------------------------------------------------------------------*/

#ifdef MAYA_MODULE_BITS
    printf("[ MAYA_MODULE_BITS ]");
    int bits = 0;

    // BIT_SET
    BIT_SET(bits, 3); // 00001000 - 8
    TEST(bits == 8, "BIT_SET failed to set bit 3");

    BIT_SET(bits, 7); // 10001000 - 136
    TEST(bits == 136, "BIT_SET failed to set bit 7");

    BIT_SET(bits, 1); // 10001010 - 138
    TEST(bits == 138, "BIT_SET failed to set bit 1");

    BIT_SET(bits, 0); // 10001011 - 139
    TEST(bits == 139, "BIT_SET failed to set bit 0");

    // BIT_CLEAR
    BIT_CLEAR(bits, 7); // 00001011 - 11
    TEST(bits == 11, "BIT_CLEAR failed to clear bit 7");

    BIT_CLEAR(bits, 3); // 00000011 - 3
    TEST(bits == 3, "BIT_CLEAR failed to clear bit 3");

    // BIT_TOGGLE
    BIT_TOGGLE(bits, 4); // 00010011 - 19
    TEST(bits == 19, "BIT_TOGGLE failed to toggle bit 4");

    BIT_TOGGLE(bits, 7); // 10010011 - 147
    TEST(bits == 147, "BIT_TOGGLE failed to toggle bit 7");

    // BIT_CHECK
    TEST(BIT_CHECK(bits, 2) == 0, "BIT_CHECK failed checking bit 2");
    TEST(BIT_CHECK(bits, 4) == 1, "BIT_CHECK failed to check bit 4");

    printf("\n");

#else
    printf("[TESTS] Ignoring MAYA_MODULE_BITS\n");
#endif // MAYA_MODULE_BITS

/*----------------------------------------------------------------------------*/

    if (failures > 0) {
        printf("Tests failed: %d\n", failures);
        return 1;
    }

    printf("\nAll test(able)s passed!\n");
    return 0;
}
