cmake_minimum_required(VERSION 3.22)
project(crypto_algo)

set(CMAKE_CXX_STANDARD 17)


#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/boost/boost_1_83_0/")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/boost/boost_1_83_0/lib64-msvc-14.3/")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

include_directories(src/Elgamal/
                    src/Magenta
                    src)

add_executable(crypto_algo
        tests/main.cpp
        src/Elgamal/primality_test.cpp
        src/Elgamal/primality_test.h
        src/Elgamal/elgamal.cpp
        src/Elgamal/keys.h
        src/Elgamal/utils.cpp
        src/Elgamal/utils.h
        src/Elgamal/elgamal.h
        src/Magenta/magenta.cpp
        src/Magenta/magenta.h
        src/file_utils.cpp
        src/file_utils.h
        src/Magenta/mag_file_processing.cpp
        src/Magenta/mag_file_processing.h
        src/Elgamal/elg_file_processing.cpp
        src/Elgamal/elg_file_processing.h
        tests/main.cpp
)

target_include_directories(crypto_algo PUBLIC
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/Elgamal/
        ${PROJECT_SOURCE_DIR}/src/Magenta/
)

install(FILES ${PROJECT_SOURCE_DIR}/src/file_utils.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/)
install(FILES ${PROJECT_SOURCE_DIR}/src/Elgamal/elg_file_processing.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/)
install(FILES ${PROJECT_SOURCE_DIR}/src/Elgamal/elgamal.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/)
install(FILES ${PROJECT_SOURCE_DIR}/src/Elgamal/primality_test.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/)
install(FILES ${PROJECT_SOURCE_DIR}/src/Elgamal/utils.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/)
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/mt_proxy_manage.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION  ${PROJECT_SOURCE_DIR}/lib/
        LIBRARY DESTINATION  ${PROJECT_SOURCE_DIR}/lib/
        ARCHIVE DESTINATION  ${PROJECT_SOURCE_DIR}/lib/)
