//
// Created by joaquin on 28/10/16.
//

#include "Host.h"

using namespace std;

Host::Host() {
    sharedMemory.crear(FILE_RESTAURANT, KEY_MEMORY);

    this->dinerInDoorFifo = new Fifo(DINER_IN_DOOR); //Lectura
    this->dinerInLivingFifo = new Fifo(DINER_IN_LIVING); //Escritura
    this->dinerInDoorLock = new LockFile(DINER_IN_DOOR_LOCK);
    this->memorySemaphore = new Semaforo(FILE_RESTAURANT, KEY_MEMORY);
}

Host::~Host() {
    delete(dinerInDoorFifo);
    dinerInDoorFifo = NULL;

    delete(dinerInLivingFifo);
    dinerInLivingFifo = NULL;

    delete(dinerInDoorLock);
    dinerInDoorLock = NULL;

    delete(memorySemaphore);
    memorySemaphore = NULL;
}

void Host::run() {
    SENAL_SALIDA_Handler senal_salida_handler;
    SignalHandler::getInstance()->registrarHandler(SENAL_CORTE, &this->senal_corte_handler);
    SignalHandler::getInstance()->registrarHandler(SENAL_SALIDA, &senal_salida_handler);

    __pid_t dinerPid = searchDinerInDoor();

    while ((dinerPid != 0) && senal_salida_handler.getGracefulQuit() == 0) {
        if (dinerPid != 0 && this->senal_corte_handler.luzPrendida()) { //Si cuando voy a buscar un diner nuevo, no tengo EOF
            if (dinerCanEnter()) {
                if (existFreeTable()) {
                    moveDinerToTable(dinerPid);
                } else {
                    moveDinerToLiving(dinerPid);
                }
            } else {
                sendOutDiner(dinerPid);
            }
        }
        dinerPid = searchDinerInDoor();
    }
    this->dinerInLivingFifo->cerrar();
}

__pid_t Host::searchDinerInDoor() {
  __pid_t dinerPid = 0;

  //Resto de los diners quedan aca esperando el lock
  dinerInDoorLock->tomarLock();

  //1º - Abrir, clavar aca al host
  ssize_t result = dinerInDoorFifo->leer((char*) (&dinerPid), sizeof(__pid_t));

  dinerInDoorLock->liberarLock();

  if ((result != 0) && (result != -1)) { //Si el fifo no esta vacio, entonces atiendo a alguien
      Logger::getInstance()->insert(KEY_HOST, STRINGS_SERVE_DINER, (int)dinerPid);
      return dinerPid;
  } else {
    return 0;//en caso de que el fifo esté vacío, dinerPid es 0
  }
}

bool Host::dinerCanEnter() {
  bool canEnter = false;

  if (this->senal_corte_handler.luzCortada()) {
      return false;
  }

  memorySemaphore->wait();

  restaurant_t restaurant = sharedMemory.leer();

  if (restaurant.diners < restaurant.diners_total) {
      restaurant.diners++;
      restaurant.dinersInRestaurant++;
      sharedMemory.escribir(restaurant);
      canEnter = true;
  }

  memorySemaphore->signal();

  return canEnter;
}

bool Host::existFreeTable() {
  bool existFreeTable = false;

  memorySemaphore->wait();

  restaurant_t restaurant = sharedMemory.leer();

  if (restaurant.tables > restaurant.busyTables) {
      restaurant.busyTables++;
      sharedMemory.escribir(restaurant);
      existFreeTable = true;
  }

  memorySemaphore->signal();

  return existFreeTable;
}

void Host::moveDinerToTable(__pid_t dinerPid) {

  Logger::getInstance()->insert(KEY_HOST, STRINGS_ASSIGN_TABLE, (int)dinerPid);
  sleep(MOVE_TO_TABLE_TIME);

  stringstream ssDinerFifoName;
  ssDinerFifoName << DINERS_FIFO << dinerPid;

  char response = 1;
  Fifo dinerFifo (ssDinerFifoName.str());
  //dinerFifo.abrir(O_WRONLY);
  dinerFifo.escribir(&response, sizeof(char));

}

void Host::moveDinerToLiving(__pid_t dinerPid) {

  Logger::getInstance()->insert(KEY_HOST, STRINGS_MOVE_DINER_TO_LIVING, (int)dinerPid);
  sleep(MOVE_TO_LIVING_TIME);

  memorySemaphore->wait();

  restaurant_t restaurant = this->sharedMemory.leer();
  restaurant.dinersInLiving++;
  this->sharedMemory.escribir(restaurant);

  memorySemaphore->signal();

  //dinerInLivingFifo->abrir(O_WRONLY);
  this->dinerInLivingFifo->escribir((char *) &dinerPid, sizeof(__pid_t));
  //dinerInLivingFifo->cerrar();

}

void Host::sendOutDiner(__pid_t dinerPid) {

  Logger::getInstance()->insert(KEY_HOST, STRINGS_SEND_OUT, (int)dinerPid);

  stringstream ssDinerFifoName;
  ssDinerFifoName << DINERS_FIFO << dinerPid;

  char response = 0;
  Fifo dinerFifo(ssDinerFifoName.str());
  //dinerFifo.abrir(O_WRONLY);
  dinerFifo.escribir(&response, sizeof(char));
}
