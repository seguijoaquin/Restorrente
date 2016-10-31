//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_ATTENDANT_H
#define RESTORRENTE_ATTENDANT_H

#include "../utils/ipcs/Fifo.h"
#include "../utils/ipcs/Semaforo.h"
#include "../utils/ipcs/MemoriaCompartida.h"
#include "../utils/types.h"
#include "../utils/ipcs/signals/SENAL_CORTE_Handler.h"
#include "../utils/ipcs/signals/SENAL_SALIDA_Handler.h"
#include "../utils/ipcs/signals/SignalHandler.h"
#include "../logger/logger.h"
#include "../logger/mensajes.h"

class Attendant {
private:

    Fifo* dinersInLivingFifo; //Lectura

    MemoriaCompartida<restaurant_t> sharedMemory;
    Semaforo* memorySemaphore;
    Semaforo* freeTableSemaphore;

    bool asignTable(SENAL_CORTE_Handler senal_corte_handler);

public:
    Attendant();
    virtual ~Attendant();
    void run();
};

#endif //RESTORRENTE_ATTENDANT_H
