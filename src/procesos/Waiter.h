//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_WAITER_H
#define RESTORRENTE_WAITER_H

#include "../utils/types.h"
#include "../utils/constants.h"
#include "../utils/ipcs/Fifo.h"
#include "../utils/ipcs/Lock.h"
#include "../utils/ipcs/Semaforo.h"
#include "../utils/ipcs/MemoriaCompartida.h"
#include "../utils/Serializador.h"
#include "../utils/ipcs/signals/SENAL_CORTE_Handler.h"
#include "../utils/ipcs/signals/SENAL_SALIDA_Handler.h"
#include "../utils/ipcs/signals/SignalHandler.h"
#include "../logger/mensajes.h"

class Waiter {
private:

    MemoriaCompartida<restaurant_t> sharedMemory;
    Semaforo* memorySemaphore;

    Fifo* ordersFifo; //Lectura
    LockFile* ordersLock;

    Fifo* ordersToCookFifo; //Escritura

    SENAL_CORTE_Handler senal_corte_handler;

    Serializador serializador;

    order_t searchOrder();
    void requestOrder(order_t order);
    void hacerLaFactura(order_t order);
    void chargeOrder(order_t order);
    void deliverOrder(order_t order);

public:
    Waiter();
    virtual ~Waiter();
    void run();
};

#endif //RESTORRENTE_WAITER_H
