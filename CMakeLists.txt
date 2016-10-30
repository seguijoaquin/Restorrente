cmake_minimum_required(VERSION 3.5)
project(Restorrente)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/utils/types.h src/utils/constants.h src/utils/ipcs/MemoriaCompartida.h src/logger/logger.cpp src/logger/logger.h src/logger/mensajes.h src/utils/ipcs/Semaforo.cpp src/utils/ipcs/Semaforo.h src/parser/Parser.cpp src/parser/Parser.h src/utils/lanzadores/lanzadorEmpleados.h src/procesos/Host.cpp src/procesos/Host.h src/procesos/Waiter.cpp src/procesos/Waiter.h src/procesos/Cook.cpp src/procesos/Cook.h src/procesos/Attendant.cpp src/procesos/Attendant.h src/utils/lanzadores/lanzarComensales.h src/procesos/Diner.cpp src/procesos/Diner.h src/utils/Serializador.cpp src/utils/Serializador.h src/utils/ipcs/Fifo.cpp src/utils/ipcs/Fifo.h src/utils/ipcs/Lock.cpp src/utils/ipcs/Lock.h src/utils/ipcs/signals/EventHandler.h src/utils/ipcs/signals/SignalHandler.cpp src/utils/ipcs/signals/SignalHandler.h src/utils/ipcs/signals/SENAL_CORTE_Handler.h src/utils/ipcs/signals/SENAL_SALIDA_Handler.h src/utils/ipcs/signals/SENAL_AVISO_Handler.h)
add_executable(Restorrente ${SOURCE_FILES})
