cmake_minimum_required(VERSION 2.8)

project(IS220)

enable_testing()

add_subdirectory(ext)
add_subdirectory(test)

add_test(NAME IS220-test COMMAND test/IS220-test)
