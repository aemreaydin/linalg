include(FetchContent)

if(MIRAGE_BUILD_TESTS)
    enable_testing()

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB TEST_SOURCES *.test.cpp)
    add_executable(mirage_math_tests ${TEST_SOURCES})
    target_link_libraries(
        mirage_math_tests
        PRIVATE mirage_math GTest::gtest GTest::gtest_main
    )
    target_include_directories(
        mirage_math_tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )

    include(GoogleTest)
    gtest_discover_tests(mirage_math_tests)
endif()

if(MIRAGE_BUILD_BENCHMARKS)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.1
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(benchmark)

    file(GLOB BENCH_SOURCES benchmarks/*.bench.cpp)
    if(BENCH_SOURCES)
        add_executable(mirage_math_benchmarks ${BENCH_SOURCES})
        target_link_libraries(
            mirage_math_benchmarks
            PRIVATE mirage_math benchmark::benchmark benchmark::benchmark_main
        )
    endif()
endif()
