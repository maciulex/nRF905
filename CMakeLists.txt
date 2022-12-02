cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(pico_examples C CXX ASM)

pico_sdk_init()

add_subdirectory(reciver)
add_subdirectory(transmiter)

