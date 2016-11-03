cmake_minimum_required(VERSION 3.5)
project(corte)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES  main.cpp  ../src/logger/logger.cpp  ../src/logger/logger.h  ../src/logger/mensajes.h ../src/utils/ipcs/MemoriaCompartida.h ../src/utils/types.h ../src/utils/constants.h)
add_executable(corte ${SOURCE_FILES})
