//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_SERIALIZADOR_H
#define RESTORRENTE_SERIALIZADOR_H

#include <iostream>
#include <cstring>
#include "types.h"

#define BUFSIZE 1024
#define PACKETSIZE sizeof(order_t)

class Serializador {

public:
    Serializador();
    ~Serializador();

    void serialize (order_t* msgPacket, char *data);
    void deserialize (char* data, order_t* msgPacket);
};

#endif //RESTORRENTE_SERIALIZADOR_H
