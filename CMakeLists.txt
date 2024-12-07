cmake_minimum_required(VERSION 3.30.0)
project(runcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(cmake/sanitize.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS locale stacktrace_backtrace)

file(GLOB_RECURSE SOURCES RELATIVE
    ${CMAKE_SOURCE_DIR}
    src/*.hpp
    src/*.cpp
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
target_link_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)

target_compile_definitions(${PROJECT_NAME} PUBLIC BOOST_STACKTRACE_USE_ADDR2LINE)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers Boost::locale boost_stacktrace_from_exception backtrace dl)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

target_link_libraries(${PROJECT_NAME} PUBLIC stdc++exp)

sanitize(${PROJECT_NAME} "addr,ub")
