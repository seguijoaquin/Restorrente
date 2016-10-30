//
// Created by joaquin on 28/10/16.
//

#include "Attendant.h"

using namespace std;

Attendant::Attendant() {
    sharedMemory.crear(FILE_RESTAURANT, KEY_MEMORY);

    this->dinersInLivingFifo = new Fifo(DINER_IN_LIVING); //Lectura
    this->freeTableSemaphore = new Semaforo(FILE_RESTAURANT, KEY_TABLES);
    this->memorySemaphore = new Semaforo(FILE_RESTAURANT, KEY_MEMORY);
}

Attendant::~Attendant() {
    delete(dinersInLivingFifo);
    dinersInLivingFifo = NULL;

    delete(freeTableSemaphore);
    freeTableSemaphore = NULL;

    delete(memorySemaphore);
    memorySemaphore = NULL;
}


void Attendant::run() {
    SENAL_CORTE_Handler senal_corte_handler;
    SENAL_SALIDA_Handler senal_salida_handler;
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE,&senal_corte_handler);
    SignalHandler::getInstance()->registrarHandler(SENAL_SALIDA,&senal_salida_handler);

    //this->dinersInLivingFifo->abrir();

    while (senal_salida_handler.getGracefulQuit() == 0) {
        asignTable(senal_corte_handler);
        sleep(1);
    }

    SignalHandler::destruir();
}

void Attendant::asignTable(SENAL_CORTE_Handler senal_corte_handler) {
  __pid_t dinerPid;

  //se bloquea esperando leer algo en dinersInLivingFifo
  ssize_t result = dinersInLivingFifo->leer((char*) (&dinerPid), sizeof(__pid_t));

  if (result != -1 && senal_corte_handler.luzPrendida()) {
    freeTableSemaphore->wait();

    // Actualizo Lista de Comensales
    memorySemaphore->wait();
    restaurant_t restaurant = sharedMemory.leer();
    if (restaurant.dinersInLiving > 0) restaurant.dinersInLiving--;
    sharedMemory.escribir(restaurant);
    memorySemaphore->signal();

    //Enivo Mensaje a Comensal
    Logger::getInstance()->insert(KEY_ATTENDANT,STRINGS_ASSIGN_TABLE, dinerPid);

    stringstream ssDinerFifoName;
    ssDinerFifoName << DINERS_FIFO << dinerPid;

    char response = 1;
    Fifo dinerFifo(ssDinerFifoName.str());
    //dinerFifo.abrir();
    dinerFifo.escribir(&response, sizeof(char));
    //dinerFifo.cerrar();
  }
}
