cmake_minimum_required(VERSION 3.0.0)
project(image-to-image-of-characters VERSION 0.1.0)

file(GLOB code_src
    "src/*.c"
)

add_executable(image-to-image-of-characters ${code_src})

target_include_directories(image-to-image-of-characters PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS image-to-image-of-characters DESTINATION bin)
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)