cmake_minimum_required(VERSION 3.5)
project(corte)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES  main.cpp  logger/logger.cpp  logger/logger.h  logger/mensajes.h MemoriaCompartida.h types.h constants.h)
add_executable(corte ${SOURCE_FILES})
