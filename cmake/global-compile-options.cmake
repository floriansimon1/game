function(enable_all_warnings_globally)
    add_compile_options(-Wall -Wextra -pedantic)
endfunction()

function(enable_cxx_20_globally)
    add_compile_options(-stdlib=libc++ -std=c++20)

    set_property(GLOBAL
        PROPERTY
            CXX_STANDARD                20
            CMAKE_CXX_STANDARD_REQUIRED ON)
endfunction()

function(enable_namespaced_local_includes_globally)
    include_directories(source)
endfunction()

function(add_debug_symbols)
    add_compile_options(-g)
endfunction()
