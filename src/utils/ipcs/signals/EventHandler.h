//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_EVENTHANDLER_H
#define RESTORRENTE_EVENTHANDLER_H

class EventHandler {

public:
	virtual int handleSignal ( int signum ) = 0;
	virtual ~EventHandler () {};
};

#endif //RESTORRENTE_EVENTHANDLER_H
