#include <iostream>
#include <unistd.h>

#include "types.h"
#include "MemoriaCompartida.h"
#include "logger/logger.h"
#include "logger/mensajes.h"
#include "constants.h"

int main(int argc, char** argv) {
    MemoriaCompartida<restaurant_t> memoriaCompartida;

    int estadoMemoria = memoriaCompartida.crear(FILE_RESTAURANT,KEY_MEMORY);

    if (estadoMemoria == SHM_OK) {
        restaurant_t consulta_restaurant = memoriaCompartida.leer();
        if (consulta_restaurant.isOpen) {
          std::cout << "******************************************************************" << std::endl;
          Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH, consulta_restaurant.cash);
          Logger::getInstance()->insert(KEY_RESTO, STRINGS_DINERS_IN_LIVING, consulta_restaurant.dinersInLiving);
          Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH_LOST, consulta_restaurant.money_not_cashed);
          std::cout << "******************************************************************" << std::endl;
        } else {
          Logger::getInstance()->info("Restaurant Cerrado - No se puede hacer consultas");
        }
    } else {
        Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
    }
    return 0;
}
