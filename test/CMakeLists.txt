include(FetchContent)

if(LINALG_BUILD_TESTS)
    enable_testing()

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB TEST_SOURCES *.test.cpp)
    add_executable(linalg_tests ${TEST_SOURCES})
    target_link_libraries(
        linalg_tests
        PRIVATE linalg GTest::gtest GTest::gtest_main
    )
    target_include_directories(
        linalg_tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )

    include(GoogleTest)
    gtest_discover_tests(linalg_tests)
endif()

if(LINALG_BUILD_BENCHMARKS)
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
        add_executable(linalg_benchmarks ${BENCH_SOURCES})
        target_link_libraries(
            linalg_benchmarks
            PRIVATE linalg benchmark::benchmark benchmark::benchmark_main
        )
    endif()
endif()
