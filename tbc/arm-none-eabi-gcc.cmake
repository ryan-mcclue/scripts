set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER    arm-none-eabi-gcc) 
set(CMAKE_CXX_COMPILER  arm-none-eabi-g++)
set(AS                  arm-none-eabi-as)
set(CMAKE_AR            arm-none-eabi-gcc-ar)
set(OBJCOPY             arm-none-eabi-objcopy)
set(OBJDUMP             arm-none-eabi-objdump)
set(SIZE                arm-none-eabi-size)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_FLAGS_INIT
  "${ARCH_CPU_FLAGS}"
	CACHE
	INTERNAL "Default C compiler flags.")
set(CMAKE_CXX_FLAGS_INIT
  "${ARCH_CPU_FLAGS}"
	CACHE
	INTERNAL "Default C++ compiler flags.")
set(CMAKE_ASM_FLAGS_INIT
	"-x assembler-with-cpp"
	CACHE
	INTERNAL "Default ASM compiler flags.")
set(CMAKE_EXE_LINKER_FLAGS_INIT
  "${ARCH_LD_FLAGS}"
	CACHE
	INTERNAL "Default linker flags.")
