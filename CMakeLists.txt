cmake_minimum_required(VERSION 3.23)

include(pico_sdk_import.cmake)

project(test-button-debounce C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -O3)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	pico_stdlib
	pico_time
	hardware_gpio)
pico_add_extra_outputs(${PROJECT_NAME})
