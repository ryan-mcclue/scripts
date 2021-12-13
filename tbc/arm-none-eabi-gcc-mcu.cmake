set(CMAKE_SYSTEM_NAME Generic)
#set(CMAKE_CROSSCOMPILING_EMULATOR qemu-arm)
set(CPU_NAME cortex-m4)
set(ARCH_CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(ARCH_LD_FLAGS "-T${CMAKE_SOURCE_DIR}/BSP/tra/STM32F429ZITx_FLASH.ld ${ARCH_CPU_FLAGS}")

include(${CMAKE_CURRENT_LIST_DIR}/arm-none-eabi-gcc.cmake)
