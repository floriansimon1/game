function(enable_all_warnings_globally)
    add_compile_options(-Wall -Wextra -pedantic -std=c++17)
endfunction()

function(enable_cxx_17_globally)
    set_property(GLOBAL
        PROPERTY
            CXX_STANDARD                17
            CMAKE_CXX_STANDARD_REQUIRED ON)
endfunction()

function(enable_namespaced_local_includes_globally)
    include_directories(source)
endfunction()
