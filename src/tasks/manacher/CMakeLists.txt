project(manacher LANGUAGES CXX)

add_library(${PROJECT_NAME} OBJECT)

set(SOURCES
        ${PROJECT_NAME}.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)