//
// Created by joaquin on 28/10/16.
//

#include "Waiter.h"

using namespace std;

Waiter::Waiter() {
    sharedMemory.crear(FILE_RESTAURANT, KEY_MEMORY);
    this->memorySemaphore = new Semaforo(FILE_RESTAURANT, KEY_MEMORY);

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
}


void Waiter::run() {
    SENAL_SALIDA_Handler senal_salida_handler;
    SignalHandler::getInstance()->registrarHandler(SENAL_SALIDA,&senal_salida_handler);
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE,&this->senal_corte_handler);

    //this->ordersToCookFifo->abrir(); NO
    //this->ordersFifo->abrir();

    while (senal_salida_handler.getGracefulQuit() == 0) {
        order_t order = searchOrder();
        if (order.valid) {
            std::cout << "[Waiter:" << getpid() <<"] - Recibe order: " << "type: "<< order.type  <<" pid: " << order.pid << std::endl;
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
                std::cerr << "Waiter:" << getpid() << "falló al buscar una orden" << std::endl;
            }
        }
        sleep(1);
    }

    SignalHandler::destruir();
}

order_t Waiter::searchOrder() {
  order_t order;

  ordersLock->tomarLock();

  char data[sizeof(order_t)];

  ssize_t result = ordersFifo->leer(data, sizeof(order_t));

  serializador.deserialize(data,&order);

  if (result == -1 ) {
      order.valid = false;
  }

  ordersLock->liberarLock();

  return order;
}

void Waiter::requestOrder(order_t order) {
  Logger::getInstance()->insert(KEY_WAITER, STRINGS_TAKE_ORDER, order.pid);
  sleep(TAKE_ORDER_TIME);

  char data[sizeof(order_t)];
  serializador.serialize(&order,data);

  //this->ordersToCookFifo->abrir();
  this->ordersToCookFifo->escribir(data, sizeof(order_t));
  //this->ordersToCookFifo->cerrar();
}

void Waiter::hacerLaFactura(order_t order) {
  Logger::getInstance()->insert(KEY_WAITER, "Cobra al comensal ", order.pid);

  stringstream ssDinerFifoName;
  ssDinerFifoName << DINERS_FIFO << order.pid;

  char response = 1;
  Fifo dinerFifo(ssDinerFifoName.str());
  //dinerFifo.abrir();
  dinerFifo.escribir(&response, sizeof(char));
  //dinerFifo.cerrar();
}

void Waiter::chargeOrder(order_t order) {
  memorySemaphore->wait();

  restaurant_t restaurant = sharedMemory.leer();
  restaurant.cash += order.toPay;
  Logger::getInstance()->insert(KEY_WAITER, STRINGS_MONEY_IN_CASH, restaurant.cash);
  sharedMemory.escribir(restaurant);

  memorySemaphore->signal();
}

void Waiter::deliverOrder(order_t order) {
  Logger::getInstance()->insert(KEY_WAITER, STRINGS_DISPATCH_ORDER, order.pid);

  sleep(DELIVER_ORDER_TIME);

  stringstream ssDinerFifoName;
  ssDinerFifoName << DINERS_FIFO << order.pid;

  char response = 1;
  Fifo dinerFifo(ssDinerFifoName.str());
  //dinerFifo.abrir();
  dinerFifo.escribir(&response, sizeof(char));
  //dinerFifo.cerrar();
}
