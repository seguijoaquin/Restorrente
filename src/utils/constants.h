//
// Created by joaquin on 27/10/16.
//

#ifndef RESTORRENTE_CONSTANTS_H
#define RESTORRENTE_CONSTANTS_H

#include <signal.h>

//ERRORES
#define ERROR_MEMORIA_COMPARTIDA "Error en memoria compartida: "


//FIFOS
#define	DINER_IN_DOOR	"/tmp/resto/diner_in_door"
#define	DINER_IN_LIVING "/tmp/resto/diner_in_living"
#define ORDERS  "/tmp/resto/orders"
#define ORDERS_TO_COOK "/tmp/resto/orders_to_cook"
#define	DINERS_FIFO	"/tmp/resto/diner_fifo_"
#define PRUEBA "/tmp/resto/FIFOPRUEBA"

//LOCK
#define DINER_IN_DOOR_LOCK "/tmp/resto/diner_in_door_lock"
#define ORDERS_LOCK "/tmp/resto/orders_lock"
#define DINER_IN_LIVING_LOCK "/tmp/resto/diner_in_living_lock"
#define LEAVING_LOCK "/tmp/resto/leaving_lock"

//SEMAPHORES
#define FILE_RESTAURANT "/tmp/resto/restaurant.tmp"
#define KEY_DINER_IN_DOOR 'd'
#define KEY_DINER_IN_LIVING 'l'
#define KEY_MEMORY 'm'
#define KEY_TABLES 't'
#define KEY_SALIDA_HOSTS 'h'
#define KEY_SALIDA_WAITERS 'w'

#define MOVE_TO_TABLE_TIME 1
#define MOVE_TO_LIVING_TIME 0

#define THINK_ORDER_TIME 0
#define EAT_TIME 0

#define TAKE_ORDER_TIME 1
#define DELIVER_ORDER_TIME 1

#define COOK_ORDER_TIME 1

#define FILE_CONFIG "src/config/config.json"
//#define FILE_CONFIG "/tmp/resto/config.json"

#define SENAL_CORTE SIGCHLD
#define SENAL_SALIDA SIGUSR2
#define SENAL_AVISO SIGUSR1

#define LUZ_CORTADA 1
#define LUZ_PRENDIDA 0

#define SALIDA 9


#endif //RESTORRENTE_CONSTANTS_H
