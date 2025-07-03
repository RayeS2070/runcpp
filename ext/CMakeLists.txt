project(ext LANGUAGES CXX)

find_package(Boost CONFIG REQUIRED COMPONENTS locale stacktrace_backtrace)

add_library(${PROJECT_NAME} OBJECT)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stackfull_exception.cpp
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
target_link_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)

# target_compile_definitions(
#     ${CMAKE_PROJECT_NAME}
#     PUBLIC
#     BOOST_STACKTRACE_USE_ADDR2LINE
# )

target_link_libraries(${PROJECT_NAME} PRIVATE
    Boost::headers
    Boost::locale
    Boost::stacktrace_backtrace
    backtrace
    dl
)
