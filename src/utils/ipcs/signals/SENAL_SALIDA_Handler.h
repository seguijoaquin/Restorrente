//
// Created by joaquin on 29/10/16.
//

#ifndef RESTORRENTE_SENAL_SALIDA_HANDLER_H
#define RESTORRENTE_SENAL_SALIDA_HANDLER_H


#include <signal.h>
#include <assert.h>

#include "EventHandler.h"
#include "../../constants.h"
#include "../../../logger/logger.h"

class SENAL_SALIDA_Handler : public EventHandler {

private:
    sig_atomic_t gracefulQuit;

public:

    SENAL_SALIDA_Handler () : gracefulQuit(0) {
    }

    ~SENAL_SALIDA_Handler () {
    }

    virtual int handleSignal ( int signum ) {
        assert ( signum == SENAL_SALIDA );
        sleep(2);
        std::cout << "Recibo senial salida: " << getpid() << std::endl;
        this->gracefulQuit = 1;
        return 0;
    }

    sig_atomic_t getGracefulQuit () const {
        return this->gracefulQuit;
    }

};


#endif //RESTORRENTE_SENAL_SALIDA_HANDLER_H
