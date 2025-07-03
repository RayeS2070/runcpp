project(cpprun_tests)

add_executable(${PROJECT_NAME}
        main.cpp
        max_subsequence/max_subsequence.cpp
        fibonacci/fibonacci.cpp
        manacher/manacher.cpp
        smallestklen/smallestklen.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gmock)

target_link_libraries(${PROJECT_NAME} PRIVATE max_subsequence)
target_link_libraries(${PROJECT_NAME} PRIVATE fibonacci)
target_link_libraries(${PROJECT_NAME} PRIVATE manacher)
target_link_libraries(${PROJECT_NAME} PRIVATE smallestklen)

add_test(NAME ctests COMMAND ${PROJECT_NAME})

sanitize(${PROJECT_NAME} "addr,ub")
