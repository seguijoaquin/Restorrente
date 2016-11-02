//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_HOST_H
#define RESTORRENTE_HOST_H

#include "../utils/types.h"
#include "../utils/constants.h"
#include "../utils/ipcs/Fifo.h"
#include "../utils/ipcs/Lock.h"
#include "../utils/ipcs/Semaforo.h"
#include "../utils/ipcs/MemoriaCompartida.h"
#include "../utils/Serializador.h"
#include "../utils/ipcs/signals/SENAL_CORTE_Handler.h"
#include "../logger/mensajes.h"
#include "../utils/ipcs/signals/SignalHandler.h"
#include "../utils/ipcs/signals/SENAL_SALIDA_Handler.h"
#include <sstream>

class Host {
private:
    MemoriaCompartida<restaurant_t> sharedMemory;

    Fifo* dinerInDoorFifo; //Lectura
    Fifo* dinerInLivingFifo; //Escritura

    LockFile* dinerInDoorLock;
    Semaforo* memorySemaphore;
    Semaforo* semaforoSalidaHosts;

    Serializador serializador;

    SENAL_CORTE_Handler senal_corte_handler;

    __pid_t searchDinerInDoor();
    bool dinerCanEnter();
    bool existFreeTable();
    void sendOutDiner(__pid_t dinerPid);
    void moveDinerToTable(__pid_t dinerPid);
    void moveDinerToLiving(__pid_t dinerPid);


public:
    Host();
    virtual ~Host();
    void run();
};
#endif //RESTORRENTE_HOST_H
