cmake_minimum_required(VERSION 3.5)
project(consultar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES  main.cpp  types.h  constants.h  MemoriaCompartida.h  logger/logger.cpp  logger/logger.h  logger/mensajes.h)
add_executable(consultar ${SOURCE_FILES})
