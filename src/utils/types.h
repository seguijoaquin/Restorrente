//
// Created by joaquin on 27/10/16.
//

#ifndef RESTORRENTE_TYPES_H
#define RESTORRENTE_TYPES_H

#include <iostream>

struct restaurant_t {
    __pid_t main_pid;
    __pid_t diners_main_pid;
    unsigned int tables;
    unsigned int busyTables;
    unsigned int dinersInLiving;
    unsigned int cash;
    unsigned int diners;
    unsigned int dinersInRestaurant;
    unsigned int money_not_cashed;
    unsigned int hosts;
    unsigned int waiters;
    unsigned int diners_total;
    unsigned int diners_arribados;
    bool isOpen = false;
};

struct order_t {
    char type = '0';
    __pid_t pid = 0;
    unsigned int toPay = 0;
    bool valid = true;
    bool salida = false;
};

struct pid_validos {
  __pid_t pid;
  bool salida = false;
};

#endif //RESTORRENTE_TYPES_H
