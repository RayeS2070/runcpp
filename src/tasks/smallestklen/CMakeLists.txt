project(smallestklen LANGUAGES CXX)

add_library(${PROJECT_NAME} OBJECT)

set(SOURCES
        smallest_k_length.cpp
        smallest_k_length.hpp
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
