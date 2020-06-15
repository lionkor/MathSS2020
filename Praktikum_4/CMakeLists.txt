cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -pedantic-errors")

project(Praktikum_4)

add_executable(${CMAKE_PROJECT_NAME} 
    CKomplex.cpp
    CKomplex.h
    FT.cpp
    FT.h
    hoever_io.cpp
    hoever_io.h
    main.cpp
)
