cmake_minimum_required(VERSION 3.0.0)
project(image-to-image-of-characters VERSION 0.1.0)

add_executable(image-to-image-of-characters src/main.c src/bmp2rgb.c)

target_include_directories(image-to-image-of-characters PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
