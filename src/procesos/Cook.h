//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_COOK_H
#define RESTORRENTE_COOK_H

#include "../utils/ipcs/Fifo.h"
#include "../utils/Serializador.h"
#include "../utils/types.h"
#include "../utils/constants.h"
#include "../utils/ipcs/signals/SENAL_CORTE_Handler.h"
#include "../utils/ipcs/signals/SENAL_SALIDA_Handler.h"
#include "../utils/ipcs/signals/SignalHandler.h"
#include "../logger/logger.h"
#include "../logger/mensajes.h"

class Cook {
private:

    Fifo* ordersFifo; //Escritura
    Fifo* ordersToCookFifo; //Lectura
    Serializador serializador;

    order_t searchOrder();
    void cookOrder(order_t order);
    void sendOrder(order_t order);

public:
    Cook();
    virtual ~Cook();
    void run();
};

#endif //RESTORRENTE_COOK_H
