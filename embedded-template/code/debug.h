// SPDX-License-Identifier: zlib-acknowledgement
#pragma once

#if defined(RAY_INTERNAL)
  INTERNAL void __bp(char const *file_name, char const *func_name, int line_num,
                     char const *optional_message = "")
  { 
    fprintf(stderr, "BREAKPOINT TRIGGERED! (%s:%s:%d)\n\"%s\"\n", file_name, func_name, 
            line_num, optional_message);
    exit(1);
  }
  INTERNAL void __ebp(char const *file_name, char const *func_name, int line_num)
  { 
    fprintf(stderr, "ERRNO BREAKPOINT TRIGGERED! (%s:%s:%d)\n\"%s\"\n", file_name, 
            func_name, line_num, strerror(errno));
    exit(1);
  }
  #define BP_MSG(msg) __bp(__FILE__, __func__, __LINE__, msg)
  #define BP() __bp(__FILE__, __func__, __LINE__)
  #define EBP() __ebp(__FILE__, __func__, __LINE__)
  #define ASSERT(cond) if (!(cond)) {BP();}
#else
  #define BP_MSG()
  #define BP()
  #define EBP()
  #define ASSERT(cond)
#endif

INTERNAL void 
qemu_arm_exit(void) 
{
  register u32 r0 __asm__("r0");
  r0 = 0x18;
  register u32 r1 __asm__("r1");
  r1 = 0x20026;
  __asm__ volatile("bkpt #0xAB");
}
