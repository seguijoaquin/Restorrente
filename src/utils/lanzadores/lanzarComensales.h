//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_LANZARCOMENSALES_H
#define RESTORRENTE_LANZARCOMENSALES_H

#include "../../procesos/Diner.h"
#include "../../utils/ipcs/Fifo.h"

#include "../ipcs/signals/SENAL_AVISO_Handler.h"
#include "../ipcs/signals/SignalHandler.h"


#include <sys/types.h>
#include <sys/wait.h>

void lanzarComensales(unsigned int diners) {

    __pid_t id = 0;

    for (int i = 0; i < diners; ++i) {
        id = fork();
        if (id == 0) {
            break;
        }
    }
    if (id == 0) {
        Diner diner;
        diner.run();
    } else {

        //Espero a que terminen todos los diners
        for (int i = 0; i < diners; ++i) {
            wait(NULL);
        }
    }
}



#endif //RESTORRENTE_LANZARCOMENSALES_H
