#include <iostream>
#include <unistd.h>

#include "../src/utils/types.h"
#include "../src/utils/ipcs/MemoriaCompartida.h"
#include "../src/logger/logger.h"
#include "../src/logger/mensajes.h"
#include "../src/utils/constants.h"

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
          Logger::getInstance()->insert(KEY_RESTO, "tables: ", consulta_restaurant.tables);
          Logger::getInstance()->insert(KEY_RESTO, "busyTables: ", consulta_restaurant.busyTables);
          Logger::getInstance()->insert(KEY_RESTO, "dinersInLiving: ", consulta_restaurant.dinersInLiving);
          Logger::getInstance()->insert(KEY_RESTO, "diners: ", consulta_restaurant.diners);
          Logger::getInstance()->insert(KEY_RESTO, "dinersInRestaurant: ", consulta_restaurant.dinersInRestaurant);
          std::cout << "******************************************************************" << std::endl;
        } else {
          Logger::getInstance()->info("Restaurant Cerrado - No se puede hacer consultas");
        }
    } else {
        Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
    }
    return 0;
}
