// SPDX-License-Identifier: zlib-acknowledgement

#include "breakpoints.h"

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
