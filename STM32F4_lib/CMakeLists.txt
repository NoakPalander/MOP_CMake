project(stm32f4xx)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/STM32F4_lib/STM32F4xx_StdPeriph_Driver/src/*.*)

add_library(stm32f4xx STATIC ${SOURCES})

target_compile_features(stm32f4xx PRIVATE c_std_11)
target_compile_options(stm32f4xx PRIVATE
    -w
    -march=armv6-m
    -mthumb
    -mfloat-abi=soft)

target_link_options(stm32f4xx PRIVATE
    -march=armv6-m
    -mthumb
    -nostartfiles
    --specs=nano.specs)

target_include_directories(stm32f4xx PUBLIC
    ${CMAKE_SOURCE_DIR}/STM32F4_lib/STM32F4xx_StdPeriph_Driver/inc
    ${CMAKE_SOURCE_DIR}/STM32F4_lib/CMSIS/Include)