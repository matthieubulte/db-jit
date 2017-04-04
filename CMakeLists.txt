cmake_minimum_required(VERSION 3.6)
project(db_jit)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.hpp isa/code_emitter.cpp isa/code_emitter.hpp main.cpp isa/stack_machine.cpp isa/stack_machine.hpp)

add_executable(db_jit ${SOURCE_FILES})