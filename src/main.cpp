#include <iostream>
#include <unistd.h>

#include "utils/types.h"
#include "utils/constants.h"
#include "utils/ipcs/MemoriaCompartida.h"
#include "logger/logger.h"
#include "logger/mensajes.h"
#include "utils/ipcs/Semaforo.h"
#include "parser/Parser.h"

#include "utils/lanzadores/lanzadorEmpleados.h"
#include "utils/lanzadores/lanzarComensales.h"
#include "utils/ipcs/Fifo.h"
#include "utils/ipcs/signals/SENAL_AVISO_Handler.h"

void inicializar(MemoriaCompartida<restaurant_t>* sharedMemory) {
    Logger::getInstance()->insert(KEY_RESTO, "Initing Resto ", getpid());
    unsigned int hosts = Parser::getInstance()->getIntValue("hosts");
    unsigned int waiters = Parser::getInstance()->getIntValue("waiters");
    unsigned int tables = Parser::getInstance()->getIntValue("tables");
    unsigned int diners_total = Parser::getInstance()->getIntValue("diners_total");
    unsigned int diners_arribados = Parser::getInstance()->getIntValue("diners_arribados");

    restaurant_t restaurant;
    restaurant.main_pid = getpid();
    restaurant.diners_main_pid = 0;
    restaurant.tables = tables;
    restaurant.busyTables = 0;
    restaurant.dinersInLiving = 0;
    restaurant.cash = 0;
    restaurant.diners = 0;
    restaurant.dinersInRestaurant = 0;
    restaurant.money_not_cashed = 0;
    restaurant.hosts = hosts;
    restaurant.waiters = waiters;
    restaurant.diners_total = diners_total;
    restaurant.diners_arribados = diners_arribados;
    restaurant.isOpen = true;

    sharedMemory->escribir(restaurant);
}

void liberarRecursos(Semaforo* sem1, Semaforo* sem2, Fifo* f1, Fifo* f2, Fifo* f3, Fifo* f4) {
    //std::cout << "Estoy liberando cosas desde ps: " << getpid() << std::endl;
    sem1->eliminar();
    sem2->eliminar();
    f1->cerrar();
    f1->eliminar();
    f2->cerrar();
    f2->eliminar();
    f3->cerrar();
    f3->eliminar();
    f4->cerrar();
    f4->eliminar();
}

int main(int argc, char** argv) {
    //TODOS HANDLEAN SIGUSR1
    SENAL_AVISO_Handler senal_aviso_handler;
    SignalHandler::getInstance()->registrarHandler(SENAL_AVISO,&senal_aviso_handler);

    MemoriaCompartida<restaurant_t> memoriaCompartida;

    Semaforo semaforoMemoria(FILE_RESTAURANT,KEY_MEMORY);
    Semaforo semaforoMesas(FILE_RESTAURANT,KEY_TABLES);
    semaforoMemoria.inicializar(1);
    semaforoMesas.inicializar(0);

    Fifo orders(ORDERS);
    Fifo ordersToCook(ORDERS_TO_COOK);
    Fifo dinerInDoor(DINER_IN_DOOR);
    Fifo dinerInLiving(DINER_IN_LIVING);

    int estadoMemoria = memoriaCompartida.crear(FILE_RESTAURANT,KEY_MEMORY);

    if (estadoMemoria == SHM_OK) {
        inicializar(&memoriaCompartida);
        restaurant_t resto = memoriaCompartida.leer();
        lanzarEmpleados(getpid(),resto.hosts,resto.waiters);
        if (resto.main_pid == getpid()) {
            lanzarComensales(resto.diners_arribados);
            if (resto.main_pid == getpid()) {

                killpg(0,SENAL_AVISO);
                //Estoy en proceso main
                //Terminaron los comensales, espero a que terminen los empleados
                for (int i = 0; i < (resto.hosts + resto.waiters + 1 + 1); ++i) {
                    wait(NULL);
                }

                restaurant_t consulta_restaurant = memoriaCompartida.leer();
                std::cout << "******************************************************************" << std::endl;
                Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH, consulta_restaurant.cash);
                Logger::getInstance()->insert(KEY_RESTO, STRINGS_DINERS_IN_LIVING, consulta_restaurant.dinersInLiving);
                Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH_LOST, consulta_restaurant.money_not_cashed);
                std::cout << "******************************************************************" << std::endl;


                //Al salir de aca se ejecuta destructor de fifos, semaforos y memoria compartida para main
                //SignalHandler::destruir();
                liberarRecursos(&semaforoMemoria,&semaforoMesas,&orders,&ordersToCook,&dinerInDoor,&dinerInLiving);
            } else {
                //Al salir de aca se ejecuta destructor de fifos, semaforos y memoria compartida para Diners
                //Soy un Diner que terminó su run y debe morir
                //liberarRecursos(&semaforoMemoria,&semaforoMesas,&orders,&ordersToCook,&dinerInDoor,&dinerInLiving);
            }
        } else {
            //Al salir de aca se ejecuta destructor de fifos, semaforos y memoria compartida para empleados
            //Soy un empleado que terminó su run y debo morir
            //liberarRecursos(&semaforoMemoria,&semaforoMesas,&orders,&ordersToCook,&dinerInDoor,&dinerInLiving);
        }
    } else {
        Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
        liberarRecursos(&semaforoMemoria,&semaforoMesas,&orders,&ordersToCook,&dinerInDoor,&dinerInLiving);
    }
    return 0;
}
