//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_SENAL_CORTE_HANDLER_H
#define RESTORRENTE_SENAL_CORTE_HANDLER_H


#include <signal.h>
#include <assert.h>

#include "EventHandler.h"
#include "../../constants.h"
#include "../../../logger/logger.h"

class SENAL_CORTE_Handler : public EventHandler {

private:
    sig_atomic_t gracefulQuit;

public:

    SENAL_CORTE_Handler () : gracefulQuit(LUZ_PRENDIDA) {
    }

    ~SENAL_CORTE_Handler () {
    }

    virtual int handleSignal ( int signum ) {
        assert ( signum == SENAL_CORTE );
        if (this->getGracefulQuit() == LUZ_PRENDIDA) {
            this->gracefulQuit = LUZ_CORTADA;
            //Logger::getInstance()->info("SE CORTA LA LUZ");
        } else {
            this->gracefulQuit = LUZ_PRENDIDA;
            //Logger::getInstance()->info("VUELVE LA LUZ");
        }

        return 0;
    }

    sig_atomic_t getGracefulQuit () const {
        return this->gracefulQuit;
    }

    bool luzCortada() const {
        return (this->getGracefulQuit() == LUZ_CORTADA);
    }

    bool luzPrendida() const {
        return (this->getGracefulQuit() == LUZ_PRENDIDA);
    }

};


#endif //RESTORRENTE_SENAL_CORTE_HANDLER_H
