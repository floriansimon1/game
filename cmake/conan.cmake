function(conan_install)
    find_program(CONAN_EXECUTABLE conan)

    if(NOT CONAN_EXECUTABLE)
        message(FATAL_ERROR "Cannot find the conan executable")
    endif()

    execute_process(COMMAND
        ${CONAN_EXECUTABLE}
        install ${CMAKE_SOURCE_DIR}/conanfile.txt
        --build=missing
        -if ${PROJECT_BINARY_DIR}/conan
        --profile=${CMAKE_SOURCE_DIR}/cmake/resources/conan-profile
    )
endfunction()

function(conan_update_module_path_globally)
    list(APPEND CMAKE_MODULE_PATH ${PROJECT_BINARY_DIR}/conan)

    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)
endfunction()
