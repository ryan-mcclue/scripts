// SPDX-License-Identifier: zlib-acknowledgement
#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>

#if defined(HHF_INTERNAL)
  static void __bp_non_debugger(char const *func_name, int line_num)
  { 
    fprintf(stderr, "BREAKPOINT TRIGGERED! (%s:%d)\n", func_name, line_num);
    exit(1);
  }
  static void __bp_debugger(char const *func_name, int line_num) { return; }
  static void (*__bp)(char const *, int) = __bp_non_debugger;

  static void __ebp_non_debugger(char const *func_name, int line_num)
  { 
    fprintf(stderr, "ERRNO BREAKPOINT TRIGGERED! (%s:%d)\n\"%s\"\n", func_name, line_num, strerror(errno));
    exit(1);
  }
  static void __ebp_debugger(char const *func_name, int line_num)
  { 
    char *errno_str = strerror(errno);
    return;
  }
  static void (*__ebp)(char const *, int) = __ebp_non_debugger;

  #define BP() __bp(__func__, __LINE__)
  #define EBP() __ebp(__func__, __LINE__)
  #define ASSERT(cond) if (!(cond)) {BP();}
#else
  #define BP()
  #define EBP()
  #define ASSERT(cond)
#endif
