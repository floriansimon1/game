cmake_minimum_required(VERSION 3.18)

project(game CXX)

include(cmake/conan.cmake)
include(cmake/locations.cmake)
include(cmake/global-compile-options.cmake)

add_debug_symbols()

enable_namespaced_local_includes_globally()
enable_all_warnings_globally()
enable_cxx_20_globally()

conan_install()
conan_update_module_path_globally()

add_subdirectory(source/game)

define_global_output_directory()
