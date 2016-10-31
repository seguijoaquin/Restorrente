//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_SEMAFORO_H
#define RESTORRENTE_SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

#define MAX_RETRIES 10

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

class Semaforo {

private:
    int id;

    int init(key_t key, int nsems);

public:
    Semaforo ( const std::string& nombre, char key);
    ~Semaforo();

    int inicializar (int valorInicial) const;

    int p () const; // decrementa
    int v () const; // incrementa
    void eliminar () const;
    int wait() const {return p();}
    int signal() const {return v();}
};

#endif //RESTORRENTE_SEMAFORO_H
