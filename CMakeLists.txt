cmake_minimum_required(VERSION 3.28)
project(MirageMath VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -Wpedantic"
    )
endif()

# SIMD detection and configuration
include(CheckCXXCompilerFlag)
option(MIRAGE_ENABLE_SIMD "Enable SIMD optimizations" ON)
option(MIRAGE_USE_AVX2 "Enable AVX2 instructions" ON)
option(MIRAGE_USE_SSE4 "Enable SSE4 instructions" ON)

if(MIRAGE_ENABLE_SIMD)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|i686")
        check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)
        check_cxx_compiler_flag("-msse4.1" COMPILER_SUPPORTS_SSE4)
        if(COMPILER_SUPPORTS_AVX2 AND MIRAGE_USE_AVX2)
            add_compile_definitions(MIRAGE_SIMD_AVX2)
            add_compile_options(-mavx2)
        elseif(COMPILER_SUPPORTS_SSE4 AND MIRAGE_USE_SSE4)
            add_compile_definitions(MIRAGE_SIMD_SSE4)
            add_compile_options(-msse4.1)
        endif()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
        add_compile_definitions(MIRAGE_SIMD_NEON)
    endif()
endif()

add_library(mirage_math INTERFACE)
target_compile_features(mirage_math INTERFACE cxx_std_23)
target_include_directories(
    mirage_math
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
option(MIRAGE_BUILD_TESTS "Build tests" ON)
option(MIRAGE_BUILD_BENCHMARKS "Build benchmarks" OFF)

if(MIRAGE_BUILD_TESTS OR MIRAGE_BUILD_BENCHMARKS)
    add_subdirectory(test)
endif()
