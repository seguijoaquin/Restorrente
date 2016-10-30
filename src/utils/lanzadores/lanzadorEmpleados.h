//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_LANZADOREMPLEADOS_H
#define RESTORRENTE_LANZADOREMPLEADOS_H

#include "../../procesos/Host.h"
#include "../../procesos/Waiter.h"
#include "../../procesos/Cook.h"
#include "../../procesos/Attendant.h"

#include <sys/types.h>
#include <sys/wait.h>


void lanzarEmpleados(__pid_t resto_pid, unsigned int hosts, unsigned int waiters);

void lanzarEmpleados(__pid_t resto_pid, unsigned int hosts, unsigned int waiters) {

    //Creo HOSTS
    __pid_t id = 0;
    for (int i = 0; i < hosts; ++i) {
        id = fork();
        if (id == 0) {
            break;
        }
    }
    if (id == 0) {
        Host host;
        host.run();
    } else {
        //Creo WAITERS
        __pid_t id = 0;
        for (int i = 0; i < waiters; i++) {
            id = fork();
            if (id == 0) {
                break;
            }
        }
        if (id == 0) {
            Waiter waiter;
            waiter.run();
        } else {
            // Creo Cook
            id = fork();
            if (id == 0) {
                Cook cook;
                cook.run();
            } else {
                // Creo Attendant
                id = fork();
                if (id == 0) {
                    Attendant attendant;
                    attendant.run();
                } else {
                    //PROCESO PRINCIPAL
                }
            }
        }
    }
}


#endif //RESTORRENTE_LANZADOREMPLEADOS_H
