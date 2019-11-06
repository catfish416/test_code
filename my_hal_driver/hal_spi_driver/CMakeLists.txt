cmake_minimum_required (VERSION 3.5)

project (hal_can)

SET(TARGET_TYPE arm)

IF(${TARGET_TYPE} STREQUAL "arm")
MESSAGE(STATUS "===== The target is for arm, so let's cross-compile =====")
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_CROSSCOMPILING TRUE)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# 1. set crosscompile path
SET(TOOLSCHAIN_PATH "/home/hp/toolschain/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/")
SET(TOOLCHAIN_HOST "${TOOLSCHAIN_PATH}bin/aarch64-linux-gnu")
SET(TOOLSCHAIN_INCLUDE_PATH "${TOOLSCHAIN_PATH}/aarch64-linux-gnu/libc/usr/include")
MESSAGE(STATUS "TOOLCHAIN_HOST: ${TOOLCHAIN_HOST}")
SET(CMAKE_SYSROOT "/home/hp/toolschain/sysroot-glibc-linaro-2.25-2019.02-aarch64-linux-gnu")
#SET(CMAKE_SYSROOT "/home/hp/toolschain/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/aarch64-linux-gnu/libc")

#set(CMAKE_FIND_ROOT_PATH "${SYSROOT_PATH}" "${CMAKE_PREFIX_PATH}" "${TOOLSCHAIN_PATH}")
set(CMAKE_FIND_ROOT_PATH  "${CMAKE_PREFIX_PATH}" "${TOOLSCHAIN_PATH}")

#SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_C_COMPILER "${TOOLCHAIN_HOST}-gcc")
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_HOST}-g++")
ELSE()
        MESSAGE(STATUS "This is for X86, use GCC")
ENDIF()

aux_source_directory(. DIR_SRCS)

add_executable(demo ${DIR_SRCS})
