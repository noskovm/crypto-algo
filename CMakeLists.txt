cmake_minimum_required(VERSION 3.26)
project(crypto_algo)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/boost/boost_1_83_0/")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/boost/boost_1_83_0/lib64-msvc-14.3/")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

include_directories(src/Elgamal)

add_executable(crypto_algo
        src/Elgamal/Elgamal.cpp
        src/Elgamal/Elgamal.h
        src/Elgamal/primality_test.cpp
        tests/main.cpp
        src/Elgamal/primality_test.h
        src/Elgamal/primality_test.h)
