#define MAYA_IMPLEMENTATION

// Use this to test all modules:
// #define MAYA_MODULE_ALL

// Testing Debugs
#define MAYA_DEBUG

// You can just comment out the ones you don't want to test.
#define MAYA_MODULE_TYPES
#define MAYA_MODULE_BITS
#define MAYA_MODULE_LOGS
#define MAYA_MODULE_COLORS
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


// Testing Project Macros
#ifdef MAYA_MODULE_LOGS
    printf("[ MAYA_MODULE_LOGS ]\n");
    TODO("Testing TODO Macro");
    INFO("Test Info Log");
    WARN("Test Warn Log");
    DEBUG("Test Debug");
    ERROR("Test Error Log");
    ERRORC("Test Error Log", 18);

    printf("\n");
#else
    printf("[TESTS] Ignoring MAYA_MODULE_LOGS\n");
#endif

/*----------------------------------------------------------------------------*/

#ifdef MAYA_MODULE_COLORS
    printf("[ MAYA_MODULE_COLORS ]\n");

    printf("  %sMAYA_C_RED%s\n", MAYA_C_RED, MAYA_C_RESET);
    printf("  %sMAYA_CB_RED%s\n", MAYA_CB_RED, MAYA_C_RESET);

    printf("  %sMAYA_C_GREEN%s\n", MAYA_C_GREEN, MAYA_C_RESET);
    printf("  %sMAYA_CB_GREEN%s\n", MAYA_CB_GREEN, MAYA_C_RESET);

    printf("  %sMAYA_C_YELLOW%s\n", MAYA_C_YELLOW, MAYA_C_RESET);
    printf("  %sMAYA_CB_YELLOW%s\n", MAYA_CB_YELLOW, MAYA_C_RESET);

    printf("  %sMAYA_C_BLUE%s\n", MAYA_C_BLUE, MAYA_C_RESET);
    printf("  %sMAYA_CB_BLUE%s\n", MAYA_CB_BLUE, MAYA_C_RESET);

    printf("  %sMAYA_C_MAGENTA%s\n", MAYA_C_MAGENTA, MAYA_C_RESET);
    printf("  %sMAYA_CB_MAGENTA%s\n", MAYA_CB_MAGENTA, MAYA_C_RESET);

    printf("  %sMAYA_C_CYAN%s\n", MAYA_C_CYAN, MAYA_C_RESET);
    printf("  %sMAYA_CB_CYAN%s\n", MAYA_CB_CYAN, MAYA_C_RESET);

    printf("  %sMAYA_C_WHITE%s\n", MAYA_C_WHITE, MAYA_C_RESET);
    printf("  %sMAYA_CB_WHITE%s\n", MAYA_CB_WHITE, MAYA_C_RESET);

    printf("  %sMAYA_C_BLACK%s\n", MAYA_C_BLACK, MAYA_C_RESET);
    printf("  %sMAYA_C_GREY%s\n", MAYA_C_GREY, MAYA_C_RESET);

    printf("\n");
#else
    printf("[TESTS] Ignoring MAYA_MODULE_COLORS\n");
#endif // MAYA_MODULE_COLORS

/*----------------------------------------------------------------------------*/

#ifdef MAYA_MODULE_ANSI
    printf("[ MAYA_MODULE_ANSI ]\n");
    printf("  %sBold%s\n", MAYA_ANSI_BOLD, MAYA_ANSI_RESET);
    printf("  %sDim%s\n", MAYA_ANSI_DIM, MAYA_ANSI_RESET);
    printf("  %sItalic%s\n", MAYA_ANSI_ITALIC, MAYA_ANSI_RESET);
    printf("  %sMAYA_ANSI_UNDERLINE%s\n", MAYA_ANSI_UNDERLINE, MAYA_ANSI_RESET);
    printf("  %sMAYA_ANSI_INVERT%s\n", MAYA_ANSI_INVERT, MAYA_ANSI_RESET);

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

    printf("\nAll test(ables) passed!\n");
    return 0;
}
