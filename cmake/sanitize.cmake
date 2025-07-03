
function(sanitize TARGET SSTR)
    if(WIN32)
        return()
    endif()

    message(${TARGET} " must be sanitized with " ${SSTR})
    if (${SSTR} MATCHES "addr|address")
        message("enable address sanitize")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(
                ${TARGET}
                PUBLIC
                -fsanitize=address
                -static-libsan
            )
            target_link_options(
                ${TARGET}
                PUBLIC
                -fsanitize=address
            )
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(
                ${TARGET}
                PUBLIC
                -fsanitize=address
            )
            target_link_options(
                ${TARGET}
                PUBLIC
                -fsanitize=address
            )
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
            message("what is it?")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            message("go out!")
        endif()
    endif()

    if (${SSTR} MATCHES "ub|undefined")
        message("enable undefined sanitize")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(
            ${TARGET}
            PUBLIC
            -fsanitize=undefined
            -static-libsan
        )
        target_link_options(
            ${TARGET}
            PUBLIC
            -fsanitize=undefined
        )
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(
                ${TARGET}
                PUBLIC
                -fsanitize=undefined
            )
            target_link_options(
                ${TARGET}
                PUBLIC
                -fsanitize=undefined
            )
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
            message("what is it?")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            message("go out!")
        endif()
    endif()

endfunction()
