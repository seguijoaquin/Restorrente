//
// Created by joaquin on 28/10/16.
//

#include "Cook.h"

Cook::Cook() {
    this->ordersFifo = new Fifo(ORDERS); //Escritura
    this->ordersToCookFifo = new Fifo(ORDERS_TO_COOK); //Lectura
}

Cook::~Cook() {
    delete(ordersFifo);
    ordersFifo = NULL;

    delete(ordersToCookFifo);
    ordersToCookFifo = NULL;
}

void Cook::run() {
    SENAL_CORTE_Handler senal_corte_handler;
    SENAL_SALIDA_Handler senal_salida_handler;
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE, &senal_corte_handler);
    SignalHandler::getInstance()->registrarHandler(SENAL_SALIDA, &senal_salida_handler);

    //this->ordersToCookFifo->abrir();
    //this->ordersFifo->abrir(); NO

    while (senal_salida_handler.getGracefulQuit() == 0) {
        order_t order = searchOrder();
        if (order.valid && senal_corte_handler.luzPrendida()) {
            cookOrder(order);
            sendOrder(order);
        }
        sleep(1);
    }

    SignalHandler::destruir();
}

order_t Cook::searchOrder() {
  order_t order;

  char data[sizeof(order_t)];

  ssize_t result = ordersToCookFifo->leer(data, sizeof(order_t));

  serializador.deserialize(data,&order);

  if (result == -1) {
      order.valid = false;
  }

  return order;
}

void Cook::cookOrder(order_t order) {
  Logger::getInstance()->insert(KEY_COOK, STRINGS_COOKING_ORDER, order.pid);
  sleep(COOK_ORDER_TIME);
}

void Cook::sendOrder(order_t order) {
  Logger::getInstance()->insert(KEY_COOK, STRINGS_FINISH_ORDER, order.pid);
  order.type = 'c';

  char data[sizeof(order_t)];
  serializador.serialize(&order,data);

  //ordersFifo->abrir();
  ordersFifo->escribir(data, sizeof(order_t));
  //ordersFifo->cerrar();
}
