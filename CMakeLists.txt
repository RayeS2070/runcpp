cmake_minimum_required(VERSION 3.31.5)
project(runcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(cmake/sanitize.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(scn CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS locale stacktrace_backtrace)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(ext)

add_subdirectory(src/tasks)

target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    src/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
    ext
    # fibonacci
)

# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fibonacci)

add_subdirectory(tests)
add_subdirectory(benchmarks)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
    fmt::fmt
    scn::scn
    spdlog::spdlog
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    BOOST_STACKTRACE_USE_ADDR2LINE
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Boost::headers
    Boost::locale
    Boost::stacktrace_backtrace
    boost_stacktrace_from_exception
    backtrace
    dl
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC stdc++exp)

sanitize(${CMAKE_PROJECT_NAME} "addr,ub")
