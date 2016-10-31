//
// Created by joaquin on 28/10/16.
//

#include "Diner.h"


Diner::Diner() {
    this->dinerInDoorFifo = new Fifo(DINER_IN_DOOR); //Escritura
    std::stringstream ssDinerFifoName;
    ssDinerFifoName << DINERS_FIFO << getpid();
    this->dinerFifo = new Fifo(ssDinerFifoName.str()); //Lectura
    this->ordersFifo = new Fifo(ORDERS); //Escritura

    this->leavingLock = new LockFile(LEAVING_LOCK);

    sharedMemory.crear(FILE_RESTAURANT, KEY_MEMORY);

    this->memorySemaphore = new Semaforo(FILE_RESTAURANT, KEY_MEMORY);
    this->tablesSemaphore = new Semaforo(FILE_RESTAURANT, KEY_TABLES);

    this->toPay = 0;
}

Diner::~Diner() {
    delete(memorySemaphore);
    memorySemaphore = NULL;

    delete(tablesSemaphore);
    tablesSemaphore = NULL;

    delete(dinerInDoorFifo);
    dinerInDoorFifo = NULL;

    delete(ordersFifo);
    ordersFifo = NULL;

    dinerFifo->cerrar();
    dinerFifo->eliminar();
    delete(dinerFifo);
    dinerFifo = NULL;
}

unsigned int Diner::menuPrice() {
    unsigned int entrada;
    unsigned int plato_principal;
    unsigned int postre;
    unsigned int bebida;

    entrada = Parser::getInstance()->getFromMenu("entrada", randomChoice());
    plato_principal = Parser::getInstance()->getFromMenu("plato_principal", randomChoice());
    postre = Parser::getInstance()->getFromMenu("postre", randomChoice());
    bebida = Parser::getInstance()->getFromMenu("bebida", randomChoice());

    unsigned int resultado = (entrada + plato_principal + bebida + postre);

    return resultado;
}

void Diner::run() {
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE, &this->senal_corte_handler);

    enterToRestaurant();

    bool hasPlace = waitToSeat();

    if (hasPlace && senal_corte_handler.luzPrendida()) {

        //this->ordersFifo->abrir(O_WRONLY);

        srand(time(NULL));
        int i = 0;
        while (i<repeatOrder() && senal_corte_handler.luzPrendida()) {
            order();
            waitOrder();
            eat();
            ++i;
        }
        pedirLaCuenta();
        pay(); //Verifico si esta la luz prendida adentro de pay, sino no hace nada
    }
    leaveRestaurant(this->senal_corte_handler.luzCortada());
}

void Diner::pedirLaCuenta() {

  __pid_t pid = getpid();
  Logger::getInstance()->insert(KEY_DINER, "Pide la cuenta a un mozo");

  order_t order;
  order.pid = pid;
  order.type = 'b';
  order.toPay = 0;

  char data[sizeof(order_t)];
  serializador.serialize(&order,data);

  //ordersFifo->abrir(O_WRONLY);
  ordersFifo->escribir(data, sizeof(order_t));
  //ordersFifo->cerrar();

}

void Diner::enterToRestaurant() {

  __pid_t pid = getpid();
  Logger::getInstance()->insert(KEY_DINER, STRINGS_ENTER_RESTO);

  //this->dinerInDoorFifo->abrir(O_WRONLY);
  this->dinerInDoorFifo->escribir((char *) &pid, sizeof(__pid_t));
  //this->dinerInDoorFifo->cerrar();
}

bool Diner::waitToSeat() {

  Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_FOR_A_TABLE);

  //this->dinerFifo->abrir(O_RDONLY);

  char wait;
  //Queda bloqueado hasta que Attendant o Host escriben en Diner_pid_fifo
  ssize_t result = dinerFifo->leer(&wait,sizeof(char));

  if (wait == 1) {
      Logger::getInstance()->insert(KEY_DINER, STRINGS_SEAT);
      return true;
  } else {
      return false;
  }
}

void Diner::order() {

  sleep(THINK_ORDER_TIME);

  __pid_t pid = getpid();
  Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_TO_ORDER);

  //Una vez que hace el pedido, se suma a la cantidad a pagar
  this->toPay += this->menuPrice();

  order_t order;
  order.pid = pid;
  order.type = 'd';
  order.toPay = 0;

  char data[sizeof(order_t)];
  serializador.serialize(&order,data);
  //ordersFifo->abrir(O_WRONLY);
  ordersFifo->escribir(data, sizeof(order_t));
  //ordersFifo->cerrar();

}

void Diner::waitOrder() {

  Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_ORDER);
  char wait;
  ssize_t result = dinerFifo->leer(&wait, sizeof(char));

}

void Diner::eat() {

  Logger::getInstance()->insert(KEY_DINER, STRINGS_EATING);
  sleep(EAT_TIME);

}

void Diner::esperoLaFactura() {

  char wait;
  ssize_t result = dinerFifo->leer(&wait, sizeof(char));

}

void Diner::pay() {

    esperoLaFactura();

    if (this->senal_corte_handler.luzPrendida()) {
      __pid_t pid = getpid();
      Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_TO_PAY);

      order_t order;
      order.pid = pid;
      order.type = 'p';
      order.toPay = this->toPay;

      char data[sizeof(order_t)];
      serializador.serialize(&order,data);

      //ordersFifo->abrir(O_WRONLY);
      ordersFifo->escribir(data, sizeof(order_t));
      //ordersFifo->cerrar();
    }

}

void Diner::leaveRestaurant(bool powerOutage) {


  this->leavingLock->tomarLock();

  Logger::getInstance()->insert(KEY_DINER, STRINGS_LEAVING);

  memorySemaphore->wait();
  restaurant_t restaurant = this->sharedMemory.leer();

  restaurant.dinersInRestaurant--;

  if (!powerOutage && restaurant.dinersInLiving > 0) {
      //Al irse un comensal, avisa que hay una mesa disponible
      tablesSemaphore->signal();
  } else {

      if (powerOutage) {
          restaurant.dinersInLiving = 0;
          restaurant.money_not_cashed += this->toPay;
      }

     if (restaurant.busyTables > 0) {
          restaurant.busyTables--;
      }

      Logger::getInstance()->insert(KEY_DINER, STRINGS_UPDATE_TABLE, restaurant.busyTables);

      if (restaurant.diners >= restaurant.diners_total && restaurant.dinersInRestaurant == 0) {
          Logger::getInstance()->insert(KEY_DINER, STRINGS_LAST_DINER);
          this->dinerInDoorFifo->cerrar(); //Cierro el fifo porque ya pasaron todos
          this->ordersFifo->cerrar();
          kill(restaurant.main_pid, SENAL_AVISO);
      }
  }

  this->sharedMemory.escribir(restaurant);

  memorySemaphore->signal();

  this->leavingLock->liberarLock();

}
