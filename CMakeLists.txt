cmake_minimum_required(VERSION 3.30.0)
project(runcpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(cmake/sanitize.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS stacktrace_backtrace)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic)
target_link_options(${PROJECT_NAME} PUBLIC)

target_compile_definitions(${PROJECT_NAME} PUBLIC BOOST_STACKTRACE_USE_ADDR2LINE)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers boost_stacktrace_from_exception backtrace dl)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

target_link_libraries(${PROJECT_NAME} PUBLIC stdc++exp)

target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address,undefined)
target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address,undefined)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_options(${PROJECT_NAME} PUBLIC -static-libsan)
    target_compile_options(${PROJECT_NAME} PUBLIC -static-libsan)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} PUBLIC asan ubsan)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
endif()

