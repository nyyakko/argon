function(enable_tests)

    message(STATUS "[${PROJECT_NAME}] project will be building the test suit.")

    if (NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
        message(STATUS "[${PROJECT_NAME}] running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are enabled.")
        set(libc_TestsLinkerOptions ${libc_TestsLinkerOptions} -fsanitize=undefined,leak,address)
    else()
        message(STATUS "[${PROJECT_NAME}] running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are disabled.")
    endif()

    set(libc_TestsCompilerOptions ${libc_TestsCompilerOptions} ${libc_CompilerOptions})

    include(GoogleTest)
    find_package(GTest CONFIG REQUIRED)

    enable_testing()
    add_subdirectory(tests)

endfunction()
