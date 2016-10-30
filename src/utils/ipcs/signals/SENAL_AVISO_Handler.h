//
// Created by joaquin on 29/10/16.
//

#ifndef RESTORRENTE_SENAL_AVISO_HANDLER_H
#define RESTORRENTE_SENAL_AVISO_HANDLER_H

#include <assert.h>
#include <signal.h>

#include "EventHandler.h"
#include "../../constants.h"
#include "../../../logger/logger.h"

class SENAL_AVISO_Handler : public EventHandler {

public:

    SENAL_AVISO_Handler () {
    }

    ~SENAL_AVISO_Handler () {
    }

    virtual int handleSignal ( int signum ) {
        assert ( signum == SENAL_AVISO );
        sleep(2);
        kill(0,SENAL_SALIDA);
        return 0;
    }

};


#endif //RESTORRENTE_SENAL_AVISO_HANDLER_H
