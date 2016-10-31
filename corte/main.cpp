#include <iostream>
#include <unistd.h>

#include "types.h"
#include "MemoriaCompartida.h"
#include "logger/logger.h"
#include "logger/mensajes.h"
#include "constants.h"

#include <sys/types.h>
#include <signal.h>


int main(int argc, char** argv) {
    MemoriaCompartida<restaurant_t> memoriaCompartida;

    int estadoMemoria = memoriaCompartida.crear(FILE_RESTAURANT,KEY_MEMORY);

    if (estadoMemoria == SHM_OK) {
        restaurant_t consulta_restaurant = memoriaCompartida.leer();
        killpg(consulta_restaurant.main_pid,SENAL_CORTE);
    } else {
        Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
    }
    return 0;
}
