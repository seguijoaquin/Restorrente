//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_SIGNALHANDLER_H
#define RESTORRENTE_SIGNALHANDLER_H

#include <signal.h>
#include <stdio.h>
#include <memory.h>

#include "EventHandler.h"

class SignalHandler {

	private:
		static SignalHandler* instance;
		static EventHandler* signal_handlers [ NSIG ];

		SignalHandler ( void );
		static void dispatcher ( int signum );

	public:
		static SignalHandler* getInstance ();
		static void destruir ();
		EventHandler* registrarHandler ( int signum,EventHandler* eh );
		int removerHandler ( int signum );

};

#endif //RESTORRENTE_SIGNALHANDLER_H
