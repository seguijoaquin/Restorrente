//
// Created by joaquin on 28/10/16.
//

#include "Waiter.h"

using namespace std;

Waiter::Waiter() {
    sharedMemory.crear(FILE_RESTAURANT, KEY_MEMORY);
    this->memorySemaphore = new Semaforo(FILE_RESTAURANT, KEY_MEMORY);
    this->semaforoSalidaWaiters = new Semaforo(FILE_RESTAURANT, KEY_SALIDA_WAITERS);

    this->ordersFifo = new Fifo(ORDERS); //Lectura
    this->ordersLock = new LockFile(ORDERS_LOCK);

    this->ordersToCookFifo = new Fifo(ORDERS_TO_COOK); //Escritura
}

Waiter::~Waiter() {
    delete(memorySemaphore);
    memorySemaphore = NULL;

    delete(ordersFifo);
    ordersFifo = NULL;

    delete(ordersLock);
    ordersLock = NULL;

    delete(ordersToCookFifo);
    ordersToCookFifo = NULL;

    delete(semaforoSalidaWaiters);
    semaforoSalidaWaiters = NULL;
}


void Waiter::run() {
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE,&this->senal_corte_handler);

    this->ordersFifo->abrir(O_RDONLY);

    order_t order;
    order = searchOrder();

    while (!order.salida) {
      //std::cout << "Waiter " << getpid() << "recibe order: valid: " << order.valid << " salida: " << order.salida << " type: " << order.type << std::endl;
        if (order.valid) {
            //std::cout << "[Waiter:" << getpid() <<"] - Recibe order: " << "type: "<< order.type  <<" pid: " << order.pid << std::endl;
            if (order.type == 'd') {
                requestOrder(order);
            } else if (order.type == 'p') {
                //si paga la cuenta
                chargeOrder(order);
            } else if (order.type == 'c') {
                //Es una orden del cocinero
                deliverOrder(order);
            } else if (order.type == 'b') {
                //es una orden para pedir la cuenta
                hacerLaFactura(order);
            } else {
                //Hubo un fallo al buscar orden o el fifo esta vacio
                Logger::getInstance()->insert(KEY_WAITER, "Fallo al buscar una orden");
            }
        }
        order = searchOrder();
    }

    //std::cout << "Sale waiter " << getpid() << " con order: " << order.salida <<" " << order.valid << " "<< order.type << std::endl;

    this->semaforoSalidaWaiters->signal();

    this->ordersToCookFifo->cerrar();

    SignalHandler::destruir();

}

order_t Waiter::searchOrder() {

  order_t order;

  //Los demas waiters se clavan aca, esperando el lock
  ordersLock->tomarLock();

  char data[sizeof(order_t)];

  //El primer waiter se clava aca
  ssize_t result = ordersFifo->leer(data, sizeof(order_t));
  while (result <= 0) {
    result = ordersFifo->leer(data,sizeof(order_t));
  }
  ordersLock->liberarLock();

  serializador.deserialize(data,&order);

  if (result <= 0 ) {
      //std::cout << "SEARCH ORDER ERROR con waiter " << getpid() << std::endl;
      order.valid = false;
      //order.salida = false;
      order.type = 'n';
  }

  return order;

}

void Waiter::requestOrder(order_t order) {
  //sleep(TAKE_ORDER_TIME);
  if (this->senal_corte_handler.luzPrendida()) {

    char data[sizeof(order_t)];
    serializador.serialize(&order,data);

    this->ordersToCookFifo->abrir(O_WRONLY);
    this->ordersToCookFifo->escribir(data, sizeof(order_t));
    //this->ordersToCookFifo->cerrar();
    Logger::getInstance()->insert(KEY_WAITER, STRINGS_TAKE_ORDER, order.pid);
  } else {
    stringstream ssDinerFifoName;
    ssDinerFifoName << DINERS_FIFO << order.pid;

    char response;
    Fifo dinerFifo(ssDinerFifoName.str());
    dinerFifo.abrir(O_WRONLY);
    response = NO_HAY_LUZ;

    //std::cout << "Estoy por escribir una respuesta de NO HAY LUZ al diner: " << order.pid << std::endl;
    while (dinerFifo.escribir(&response, sizeof(char) == -1)) {}
    Logger::getInstance()->insert(KEY_WAITER, "Comunica que no hay luz al Diner: ", order.pid);
  }
}

void Waiter::hacerLaFactura(order_t order) {

  if (this->senal_corte_handler.luzPrendida()) {
    Logger::getInstance()->insert(KEY_WAITER, "Entrega el ticket al comensal ", order.pid);

    stringstream ssDinerFifoName;
    ssDinerFifoName << DINERS_FIFO << order.pid;

    char response = 1;
    Fifo dinerFifo(ssDinerFifoName.str());
    dinerFifo.abrir(O_WRONLY);
    dinerFifo.escribir(&response, sizeof(char));
  }
}

void Waiter::chargeOrder(order_t order) {

  if (this->senal_corte_handler.luzPrendida()) {
    if (memorySemaphore->wait() != -1) {
      restaurant_t restaurant = sharedMemory.leer();
      restaurant.cash += order.toPay;
      Logger::getInstance()->insert(KEY_WAITER, "Recibe $", order.toPay);
      Logger::getInstance()->insert(KEY_WAITER, STRINGS_MONEY_IN_CASH, restaurant.cash);
      sharedMemory.escribir(restaurant);
    }

    memorySemaphore->signal();
  }
}

void Waiter::deliverOrder(order_t order) {
  stringstream ssDinerFifoName;
  ssDinerFifoName << DINERS_FIFO << order.pid;
  char response;
  Fifo dinerFifo(ssDinerFifoName.str());
  dinerFifo.abrir(O_WRONLY);

  sleep(DELIVER_ORDER_TIME);

  if (this->senal_corte_handler.luzPrendida()) {

    response = PLATO_COMIDA;
    dinerFifo.escribir(&response, sizeof(char));
    Logger::getInstance()->insert(KEY_WAITER, STRINGS_DISPATCH_ORDER, order.pid);
  } else {
    response = NO_HAY_LUZ;
    dinerFifo.escribir(&response, sizeof(char));
    Logger::getInstance()->insert(KEY_WAITER, "Contesta que no hay luz al Diner: ", order.pid);
  }

}
