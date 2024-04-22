cmake_minimum_required(VERSION 3.29.2)

project(gc
    VERSION 1.0
    DESCRIPTION "Garbage Collector"
    LANGUAGES C)

file(GLOB_RECURSE SOURCES "src/*.c")


add_executable(gc ${SOURCES})

target_include_directories(gc PRIVATE include)

target_compile_features(gc PRIVATE c_std_17)