#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>

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
  restaurant_t consultar = sharedMemory->leer();
  if(!consultar.isOpen) {
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
}

void liberarRecursos(Semaforo* sem1, Semaforo* sem2, Fifo* f1, Fifo* f2, Fifo* f3, Fifo* f4,Semaforo* sem3, Semaforo* sem4) {
    //std::cout << "Estoy liberando cosas desde ps: " << getpid() << std::endl;
    sem1->eliminar();
    sem2->eliminar();
    sem3->eliminar();
    sem4->eliminar();
    f1->cerrar();
    f1->eliminar();
    f2->cerrar();
    f2->eliminar();
    f3->cerrar();
    f3->eliminar();
    f4->cerrar();
    f4->eliminar();
}


static const char *optString = "icd:q:p:sh?";

static const struct option longOpts[] = {
        { "init", no_argument, NULL, 'i' },
        { "diner", required_argument, NULL,'d' },
        { "query", required_argument, NULL, 'q' },
        { "power", required_argument, NULL, 'p' },
        { "help", no_argument, NULL, 'h' },
        { NULL, no_argument, NULL, 0 }
};

void imprimirConsulta(MemoriaCompartida<restaurant_t>* mem) {
  restaurant_t consulta_restaurant = mem->leer();
  std::cout << "******************************************************************" << std::endl;
  Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH, consulta_restaurant.cash);
  Logger::getInstance()->insert(KEY_RESTO, STRINGS_DINERS_IN_LIVING, consulta_restaurant.dinersInLiving);
  Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH_LOST, consulta_restaurant.money_not_cashed);
  std::cout << "******************************************************************" << std::endl;
}

int main(int argc, char** argv) {
    restaurant_t restaurant;
    FILE* file = fopen(FILE_RESTAURANT, "w");

    if (!file) {
        std::stringstream log;
        log << "Error en fopen():" << strerror(errno);
        Logger::getInstance()->error(log.str());
        exit(0);
    } else {
        fclose(file);
    }

    MemoriaCompartida<restaurant_t> memoriaCompartida;

    Semaforo semaforoMemoria(FILE_RESTAURANT,KEY_MEMORY);
    Semaforo semaforoMesas(FILE_RESTAURANT,KEY_TABLES);
    Semaforo semaforoSalidaHosts(FILE_RESTAURANT,KEY_SALIDA_HOSTS);
    Semaforo semaforoSalidaWaiters(FILE_RESTAURANT,KEY_SALIDA_WAITERS);

    Fifo orders(ORDERS);
    Fifo ordersToCook(ORDERS_TO_COOK);
    Fifo dinerInDoor(DINER_IN_DOOR);
    Fifo dinerInLiving(DINER_IN_LIVING);

    Serializador serializador;

    int estadoMemoria = memoriaCompartida.crear(FILE_RESTAURANT,KEY_MEMORY);

    if (estadoMemoria == SHM_OK) {

      __pid_t empleados_pid = 0;
      __pid_t comensales_pid = 0;

      int opt = 0;
      int longIndex;

      __pid_t resto_pid = getpid();
      opt = getopt_long(argc, argv, optString, longOpts, &longIndex);

      while (opt != -1) {
          switch (opt) {
              case 'i':{
                empleados_pid = getpid();

                //Al iniciar el resto, debo inicialir los semaforos y memoriaCompartida, sino no
                semaforoMemoria.inicializar(1);
                semaforoMesas.inicializar(0);
                semaforoSalidaHosts.inicializar(0);
                semaforoSalidaWaiters.inicializar(0);
                inicializar(&memoriaCompartida);

                restaurant_t resto = memoriaCompartida.leer();

                lanzarEmpleados(resto_pid,resto.hosts,resto.waiters);
                break;
              }
              case 'd': {
                restaurant_t resto = memoriaCompartida.leer();
                comensales_pid = getpid();
                resto.diners_main_pid = comensales_pid;
                memoriaCompartida.escribir(resto);

                if (resto.isOpen) {
                  dinerInDoor.abrir(O_WRONLY); //Abro para que arranquen los HOSTS y se traben al leer fifo vacio
                  orders.abrir(O_WRONLY); //Abro para que arranquen los waiters y se traben al leer fifo vacio
                  ordersToCook.abrir(O_WRONLY);
                  dinerInLiving.abrir(O_WRONLY);
                  lanzarComensales(atoi(optarg));
                }
                else {
                  Logger::getInstance()->info("Resto cerrado");
                }
                break;
              }
          }
          break;
      }

      if (empleados_pid == getpid()) {
        //Salgo del wait de los empleados
        imprimirConsulta(&memoriaCompartida);
        __pid_t pid = getpid();
        Logger::getInstance()->insert(KEY_RESTO, STRINGS_DESTROY, (int)pid);
        liberarRecursos(&semaforoMemoria,&semaforoMesas,&orders,&ordersToCook,&dinerInDoor,&dinerInLiving,&semaforoSalidaHosts,&semaforoSalidaWaiters);
        Logger::getInstance()->insert(KEY_RESTO, STRINGS_FINISHED);
      }

      if(comensales_pid == getpid()) {
        restaurant_t resto = memoriaCompartida.leer();

          imprimirConsulta(&memoriaCompartida);

          if (resto.diners >= resto.diners_total && resto.dinersInRestaurant == 0) {

          Semaforo* semHosts = new Semaforo(FILE_RESTAURANT,KEY_SALIDA_HOSTS);
          Semaforo* semWaiters = new Semaforo(FILE_RESTAURANT,KEY_SALIDA_WAITERS);
          //SALGO DEL WAIT DE LOS DINERS
          __pid_t salida = SALIDA;
          for (int i = 0; i < resto.hosts ; ++i) {
            dinerInDoor.escribir((char*) &salida, sizeof(__pid_t));
            //std::cout << "wait host" << i << std::endl;
            //semHosts->wait();
            //sleep(2);
            //std::cout << "waited host" << i << std::endl;
          }
          dinerInDoor.cerrar();

          order_t order;
          order.salida = true;
          order.type = 's';
          char data[sizeof(order_t)];
          serializador.serialize(&order,data);

          for (int i = 0; i < resto.waiters ; ++i) {
            orders.escribir(data, sizeof(order_t));
          }
          orders.cerrar();

          dinerInLiving.escribir((char*) &salida, sizeof(__pid_t));
          dinerInLiving.cerrar();

          ordersToCook.escribir(data,sizeof(order_t));
          ordersToCook.cerrar();

          delete(semHosts);
          delete(semWaiters);
        }

      }

    } else {
      Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
      liberarRecursos(&semaforoMemoria,&semaforoMesas,&orders,&ordersToCook,&dinerInDoor,&dinerInLiving,&semaforoSalidaHosts,&semaforoSalidaWaiters);
    }
    return 0;
}
