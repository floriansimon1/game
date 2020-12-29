include_guard()

function(define_global_output_directory)
    set(OUTPUT_ROOT_DIRECTORY "${CMAKE_BINARY_DIR}/output/" PARENT_SCOPE)
endfunction()

function(target_set_runtime_shader_location_define TARGET)
    target_compile_definitions(${TARGET} PRIVATE -DSHADERS_RELATIVE_DIRECTORY_MACRO="shaders/glsl/")
endfunction()
