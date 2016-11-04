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
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE,&senal_corte_handler);

    this->dinersInLivingFifo->abrir(O_RDONLY);

    bool salida = asignTable(senal_corte_handler);
    while (salida) {
      salida = asignTable(senal_corte_handler);
      //sleep(1);
    }

    this->dinersInLivingFifo->cerrar();

    SignalHandler::destruir();
}

bool Attendant::asignTable(SENAL_CORTE_Handler senal_corte_handler) {

  __pid_t dinerPid;

  //se bloquea esperando leer algo en dinersInLivingFifo
  ssize_t result = dinersInLivingFifo->leer((char*) (&dinerPid), sizeof(__pid_t));
  while (result <= 0) {
    result = dinersInLivingFifo->leer((char*) (&dinerPid), sizeof(__pid_t));
  }

  if ((result > 0) && (dinerPid == SALIDA)) {
    //std::cout << "Me voy Attendant" << std::endl;
    return false;
  }

  //Logger::getInstance()->insert(KEY_ATTENDANT,"Recibo a Diner: ", dinerPid);
  //if (senal_corte_handler.luzPrendida()) std::cout << "Luz prendida" << std::endl;
  //if (senal_corte_handler.luzCortada()) std::cout << "Luz cortada" << std::endl;

  if ( (result > 0) && senal_corte_handler.luzPrendida()) {
    //std::cout << "Antes de freeTableSemaphore" << std::endl;
    if (freeTableSemaphore->wait() != -1) {
      //std::cout << "Antes de memorySemaphore" << std::endl;
      // Actualizo Lista de Comensales
      if (memorySemaphore->wait() != -1) {

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
        dinerFifo.abrir(O_WRONLY);
        dinerFifo.escribir(&response, sizeof(char));
      } else {
        //std::cout << "Error en memorySemaphore" << std::endl;
        memorySemaphore->signal();
      }
    } else {
      //std::cout << "Error en freeTableSemaphore" << std::endl;
      //Comunico que se tiene que ir el diner aunque tenga error en semaforo porque no puede entrar y no lo puedo saltear
      stringstream ssDinerFifoName;
      ssDinerFifoName << DINERS_FIFO << dinerPid;

      char response = 0;
      Fifo dinerFifo(ssDinerFifoName.str());
      dinerFifo.abrir(O_WRONLY);
      while (dinerFifo.escribir(&response, sizeof(char)) == -1) {}
      Logger::getInstance()->insert(KEY_ATTENDANT,"Comunico que no hay luz al Diner: ", dinerPid);
      freeTableSemaphore->signal();
    }

  } else {
    //Si la luz está apagada le aviso al Diner que no puede sentarse
      //std::cout << "Entro al else" << std::endl;
      stringstream ssDinerFifoName;
      ssDinerFifoName << DINERS_FIFO << dinerPid;

      char response = 0;
      Fifo dinerFifo(ssDinerFifoName.str());
      dinerFifo.abrir(O_WRONLY);
      while (dinerFifo.escribir(&response, sizeof(char)) == -1) {}
      Logger::getInstance()->insert(KEY_ATTENDANT,"Comunico que no hay luz al Diner: ", dinerPid);
  }

  return true;

}
