//
// Created by joaquin on 28/10/16.
//

#include "Serializador.h"

using namespace std;

Serializador::Serializador() {

}

Serializador::~Serializador() {

}

void Serializador::serialize(order_t* msgPacket, char *data) {
    char *q = (char*)data;
    *q = msgPacket->type;
    q++;

    __pid_t *p = (__pid_t*)q;
    *p = msgPacket->pid;
    p++;

    unsigned int *r = (unsigned int*)p;
    *r = msgPacket->toPay;
    r++;

    bool *s = (bool*)r;
    *s = msgPacket->valid;
    s++;
}

void Serializador::deserialize(char *data, order_t* msgPacket) {
    char *q = (char*)data;
    msgPacket->type = *q;
    q++;

    __pid_t *p = (__pid_t*)q;
    msgPacket->pid = *p;
    p++;

    unsigned int *r = (unsigned int*)p;
    msgPacket->toPay = *r;
    r++;

    bool *s = (bool*)r;
    msgPacket->valid = *s;
    s++;
}