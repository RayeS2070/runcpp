project(cpprun_benchmark)

find_package(benchmark REQUIRED)

SET(BENCH_SOURCES
        main.cpp
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${BENCH_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
