// SPDX-License-Identifier: zlib-acknowledgement

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define INTERNAL static
#define GLOBAL static
#define LOCAL_PERSIST static

typedef unsigned int uint;
typedef uint8_t u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef int8_t s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef float r32;
typedef double r64;

#if defined(HHF_INTERNAL)
  INTERNAL void __bp_non_debugger(char const *func_name, int line_num)
  { 
    fprintf(stderr, "BREAKPOINT TRIGGERED! (%s:%d)\n", func_name, line_num);
    exit(1);
  }
  INTERNAL void __bp_debugger(char const *func_name, int line_num) { return; }
  GLOBAL void (*__bp)(char const *, int) = __bp_non_debugger;

  INTERNAL void __ebp_non_debugger(char const *func_name, int line_num)
  { 
    fprintf(stderr, "ERRNO BREAKPOINT TRIGGERED! (%s:%d)\n\"%s\"\n", func_name, line_num, strerror(errno));
    exit(1);
  }
  INTERNAL void __ebp_debugger(char const *func_name, int line_num)
  { 
    char *errno_str = strerror(errno);
    return;
  }
  GLOBAL void (*__ebp)(char const *, int) = __ebp_non_debugger;

  #define BP() __bp(__func__, __LINE__)
  #define EBP() __ebp(__func__, __LINE__)
  #define ASSERT(cond) if (!(cond)) {BP();}
#else
  #define BP()
  #define EBP()
  #define ASSERT(cond)
#endif

int
main(int argc, char *argv[])
{
#if defined(HHF_INTERNAL)
  if (argc > 1 && strcmp(argv[1], "-debugger"))
  {
    __bp = __bp_debugger;
    __ebp = __ebp_debugger;
  }
#endif

  BP();

  return 0;
}
