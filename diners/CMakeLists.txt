cmake_minimum_required(VERSION 3.5)
project(comensales)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES  main.cpp  utils/types.h  utils/constants.h  utils/ipcs/MemoriaCompartida.h  logger/logger.cpp  logger/logger.h  logger/mensajes.h  utils/ipcs/Semaforo.cpp  utils/ipcs/Semaforo.h  parser/Parser.cpp  parser/Parser.h utils/lanzadores/lanzarComensales.h  procesos/Diner.cpp  procesos/Diner.h  utils/Serializador.cpp  utils/Serializador.h  utils/ipcs/Fifo.cpp  utils/ipcs/Fifo.h  utils/ipcs/Lock.cpp  utils/ipcs/Lock.h  utils/ipcs/signals/EventHandler.h  utils/ipcs/signals/SignalHandler.cpp  utils/ipcs/signals/SignalHandler.h  utils/ipcs/signals/SENAL_CORTE_Handler.h  utils/ipcs/signals/SENAL_SALIDA_Handler.h  utils/ipcs/signals/SENAL_AVISO_Handler.h)
add_executable(comensales ${SOURCE_FILES})
