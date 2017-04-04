cmake_minimum_required(VERSION 3.6)
project(db_jit)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES isa/instructions.cpp isa/instructions.hpp main.hpp code_emitter.cpp code_emitter.hpp main.cpp )

add_executable(db_jit ${SOURCE_FILES})