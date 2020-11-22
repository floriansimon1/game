cmake_minimum_required(VERSION 3.18)

project(game CXX)

include(cmake/conan.cmake)
include(cmake/locations.cmake)
include(cmake/global-compile-options.cmake)

enable_namespaced_local_includes_globally()
enable_all_warnings_globally()
enable_cxx_17_globally()

conan_install()
conan_update_module_path_globally()

add_subdirectory(source/game)

define_global_output_directory()

install(DIRECTORY assets/ DESTINATION "${OUTPUT_ROOT_DIRECTORY}")
