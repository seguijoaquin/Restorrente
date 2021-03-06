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

        this->ordersFifo->abrir(O_WRONLY); //Ya fue abierto en proceso que lanza diners

        srand(time(NULL));
        int i = 0;
        while (i<repeatOrder() && senal_corte_handler.luzPrendida()) {
            order();
            waitOrder();
            eat();
            ++i;
        }
        pedirLaCuenta();
        esperoLaFactura();
        pay(); //Verifico si esta la luz prendida adentro de pay, sino no hace nada
    }
    leaveRestaurant(this->senal_corte_handler.luzCortada(),hasPlace);

    SignalHandler::destruir();
}

void Diner::enterToRestaurant() {

  __pid_t pid = getpid();
  Logger::getInstance()->insert(KEY_DINER, STRINGS_ENTER_RESTO);

  this->dinerInDoorFifo->abrir(O_WRONLY); //Ya fue abierto en proceso que lanza diners
  this->dinerInDoorFifo->escribir((char *) &pid, sizeof(__pid_t));
  this->dinerInDoorFifo->cerrar(); //Ultima vez que escribo en dinerInDoorFifo

}

bool Diner::waitToSeat() {

  Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_FOR_A_TABLE);

  this->dinerFifo->abrir(O_RDONLY);

  char wait;
  //Queda bloqueado hasta que Attendant o Host escriben en Diner_pid_fifo
  ssize_t result = dinerFifo->leer(&wait,sizeof(char));

  while (result <= 0) {
    Logger::getInstance()->insert(KEY_DINER, "Error al leer dinerFifo->waitToSeat()");
    result = dinerFifo->leer(&wait, sizeof(char));
  }

  if ((wait == 1) && (result > 0)) {
      Logger::getInstance()->insert(KEY_DINER, STRINGS_SEAT);
      return true;
  } else {
      return false;
  }
}

void Diner::order() {
  if(this->senal_corte_handler.luzPrendida()) {
    sleep(THINK_ORDER_TIME);

    __pid_t pid = getpid();

    //Una vez que hace el pedido, se suma a la cantidad a pagar
    this->toPay += this->menuPrice();

    order_t order;
    order.pid = pid;
    order.type = 'd';
    order.toPay = 0;
    order.salida = false;

    char data[sizeof(order_t)];
    serializador.serialize(&order,data);
    //this->ordersFifo->abrir(O_WRONLY);
    ordersFifo->escribir(data, sizeof(order_t));
    //ordersFifo->cerrar();

    Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_TO_ORDER);
  }
}

void Diner::waitOrder() {
    char wait;
    ssize_t result = dinerFifo->leer(&wait, sizeof(char));

    while (result <= 0) {
      Logger::getInstance()->insert(KEY_DINER, "Error al leer dinerFifo->waitOrder()");
      result = dinerFifo->leer(&wait, sizeof(char));
      //return;
    }
    if (wait != NO_HAY_LUZ) {
      Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_ORDER);
    } else {
      Logger::getInstance()->insert(KEY_DINER, "Se retira sin esperar el pedido por corte de luz");
    }
}

void Diner::eat() {
  if(this->senal_corte_handler.luzPrendida()) {
    Logger::getInstance()->insert(KEY_DINER, STRINGS_EATING);
    sleep(EAT_TIME);
  }
}


void Diner::pedirLaCuenta() {
  if (this->senal_corte_handler.luzPrendida()) {
    __pid_t pid = getpid();
    Logger::getInstance()->insert(KEY_DINER, "Pide la cuenta a un mozo");

    order_t order;
    order.pid = pid;
    order.type = 'b';
    order.toPay = 0;
    order.salida = false;

    char data[sizeof(order_t)];
    serializador.serialize(&order,data);

    //ordersFifo->abrir(O_WRONLY);
    ordersFifo->escribir(data, sizeof(order_t));
    //ordersFifo->cerrar();
  }

}

void Diner::esperoLaFactura() {
  if (this->senal_corte_handler.luzPrendida()) {
    char wait;
    ssize_t result = dinerFifo->leer(&wait, sizeof(char));
    while (result <= 0) {
      result = dinerFifo->leer(&wait, sizeof(char));
    }
    if (result <= 0) {
      Logger::getInstance()->insert(KEY_DINER, "Error al leer dinerFifo->esperoLaFactura()");
      return;
    }
  }
}

void Diner::pay() {

    if (this->senal_corte_handler.luzPrendida()) { //Paga solo si esta la luz prendida
      __pid_t pid = getpid();
      Logger::getInstance()->insert(KEY_DINER, STRINGS_WAITING_TO_PAY);

      order_t order;
      order.pid = pid;
      order.type = 'p';
      order.toPay = this->toPay;
      order.salida = false;

      char data[sizeof(order_t)];
      serializador.serialize(&order,data);

      //ordersFifo->abrir(O_WRONLY);
      this->ordersFifo->escribir(data, sizeof(order_t));
      this->ordersFifo->cerrar(); //Ultima vez que escribo en ordersFifo antes de salir
    }

}

void Diner::leaveRestaurant(bool powerOutage, bool hasPlace) {

  Logger::getInstance()->insert(KEY_DINER, STRINGS_LEAVING);

  if (!hasPlace) {
    return;
  }

  if(memorySemaphore->wait() != -1) {
    restaurant_t restaurant = this->sharedMemory.leer();

    restaurant.dinersInRestaurant--;

    if (!powerOutage && restaurant.dinersInLiving > 0) {
      //Al irse un comensal, avisa que hay una mesa disponible
      tablesSemaphore->signal();
    } else {

      if (powerOutage) {
        restaurant.dinersInLiving = 0;
        restaurant.dinersInRestaurant = 0;
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
        //kill(restaurant.main_pid, SENAL_AVISO);
      }
    }

    this->sharedMemory.escribir(restaurant);

    memorySemaphore->signal();

  } else {
    memorySemaphore->signal();
  }

}
