cmake_minimum_required(VERSION 3.25)
project(MOP CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(BINARY MOP)

add_subdirectory(${CMAKE_SOURCE_DIR}/STM32F4_lib SYSTEM)

add_executable(${BINARY}
    ${CMAKE_SOURCE_DIR}/resources/startup.asm
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/sysmem.cpp
    ${CMAKE_SOURCE_DIR}/src/syscalls.cpp)

target_compile_features(${BINARY} PRIVATE cxx_std_20)
target_compile_options(${BINARY} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -g
    -O0
    -Wno-variadic-macros
    -mno-unaligned-access
    -march=armv6-m
    -mthumb
    -mfloat-abi=soft)

target_link_options(${BINARY} PRIVATE
    -T ${CMAKE_SOURCE_DIR}/resources/md407-crt-ram.ld
    -march=armv6-m
    -mthumb
    -nostartfiles
    --specs=nano.specs)

target_link_libraries(${BINARY} PRIVATE gcc c_nano stm32f4xx)

add_custom_command(TARGET ${BINARY} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -S -O srec ${CMAKE_BINARY_DIR}/${BINARY} ${CMAKE_BINARY_DIR}/${BINARY}.s19
    COMMAND ${CMAKE_OBJDUMP} -D -S ${CMAKE_BINARY_DIR}/${BINARY} > ${CMAKE_BINARY_DIR}/${BINARY}.dass
    COMMENT "Disassembling files")
