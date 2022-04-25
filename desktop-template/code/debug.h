// SPDX-License-Identifier: zlib-acknowledgement
#pragma once

#if defined(RAY_INTERNAL)
  INTERNAL void __bp(char const *file_name, char const *func_name, int line_num)
  { 
    fprintf(stderr, "BREAKPOINT TRIGGERED! (%s:%s:%d)\n", file_name, func_name, line_num);
    exit(1);
  }
  INTERNAL void __ebp(char const *file_name, char const *func_name, int line_num)
  { 
    fprintf(stderr, "ERRNO BREAKPOINT TRIGGERED! (%s:%s:%d)\n\"%s\"\n", file_name, 
            func_name, line_num, strerror(errno));
    exit(1);
  }
  #define BP() __bp(__FILE__, __func__, __LINE__)
  #define EBP() __ebp(__FILE__, __func__, __LINE__)
  #define ASSERT(cond) if (!(cond)) {BP();}
#else
  #define BP()
  #define EBP()
  #define ASSERT(cond)
#endif
