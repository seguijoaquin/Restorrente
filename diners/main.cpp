#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "utils/types.h"
#include "utils/constants.h"
#include "utils/ipcs/MemoriaCompartida.h"
#include "logger/logger.h"
#include "logger/mensajes.h"

#include "utils/lanzadores/lanzarComensales.h"

int main(int argc, char** argv) {
    MemoriaCompartida<restaurant_t> memoriaCompartida;

    int estadoMemoria = memoriaCompartida.crear(FILE_RESTAURANT,KEY_MEMORY);

    if (estadoMemoria == SHM_OK) {
        restaurant_t resto = memoriaCompartida.leer();
        if (resto.isOpen) {
            lanzarComensales(atoi(argv[1]));
                restaurant_t consulta_restaurant = memoriaCompartida.leer();
                std::cout << "******************************************************************" << std::endl;
                Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH, consulta_restaurant.cash);
                Logger::getInstance()->insert(KEY_RESTO, STRINGS_DINERS_IN_LIVING, consulta_restaurant.dinersInLiving);
                Logger::getInstance()->insert(KEY_RESTO, STRINGS_CASH_LOST, consulta_restaurant.money_not_cashed);
                std::cout << "******************************************************************" << std::endl;
        } else {
            Logger::getInstance()->info("No entra nadie porque el resto está cerrado");
        }
    } else {
        Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
    }
    return 0;
}
