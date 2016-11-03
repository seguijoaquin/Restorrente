#include <iostream>
#include <unistd.h>

#include "../src/utils/types.h"
#include "../src/utils/ipcs/MemoriaCompartida.h"
#include "../src/logger/logger.h"
#include "../src/logger/mensajes.h"
#include "../src/utils/constants.h"

#include <sys/types.h>
#include <signal.h>


int main(int argc, char** argv) {
    MemoriaCompartida<restaurant_t> memoriaCompartida;

    int estadoMemoria = memoriaCompartida.crear(FILE_RESTAURANT,KEY_MEMORY);

    if (estadoMemoria == SHM_OK) {
        restaurant_t consulta_restaurant = memoriaCompartida.leer();
        if (consulta_restaurant.isOpen) {
            Logger::getInstance()->info("Señal de corte lanzada");
            killpg(consulta_restaurant.main_pid,SENAL_CORTE);
            killpg(consulta_restaurant.diners_main_pid,SENAL_CORTE);
        } else {
          Logger::getInstance()->info("Restaurant cerrado - No se puede lanzar señal de corte");
        }
    } else {
        Logger::getInstance()->insert(KEY_ERROR,ERROR_MEMORIA_COMPARTIDA,estadoMemoria);
    }
    return 0;
}
