//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_DINER_H
#define RESTORRENTE_DINER_H

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <exception>

#include "../utils/types.h"
#include "../utils/ipcs/Fifo.h"
#include "../utils/ipcs/MemoriaCompartida.h"
#include "../utils/ipcs/Semaforo.h"
#include "../utils/Serializador.h"
#include "../utils/constants.h"
#include "../utils/ipcs/signals/SENAL_CORTE_Handler.h"
#include "../parser/Parser.h"
#include "../logger/mensajes.h"
#include "../utils/ipcs/signals/SignalHandler.h"

using namespace std;

class Diner {
private:
    Fifo* dinerInDoorFifo;
    Fifo* dinerFifo;
    Fifo* ordersFifo;

    MemoriaCompartida<restaurant_t> sharedMemory;

    Semaforo* memorySemaphore;
    Semaforo* tablesSemaphore;

    unsigned int toPay;

    Serializador serializador;

    SENAL_CORTE_Handler senal_corte_handler;

    void enterToRestaurant();
    bool waitToSeat();
    void order();
    void waitOrder();
    void eat();
    void pedirLaCuenta();
    void esperoLaFactura();
    void pay();
    void leaveRestaurant(bool powerOutage);
    int repeatOrder() {
        return 1;
        //return rand() % 3 + 1;
    }
    int randomChoice() {
        return 1;
        //return rand() % 4;
    }
    unsigned int menuPrice();



public:
    Diner();
    virtual ~Diner();
    void run();
};

#endif //RESTORRENTE_DINER_H
