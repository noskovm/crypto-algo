cmake_minimum_required(VERSION 3.26)
project(crypto_algo)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/Elgamal)

add_executable(crypto_algo
        src/Elgamal/Elgamal.cpp
        src/Elgamal/Elgamal.h
        src/Elgamal/primality_test.cpp)
