//
// Created by joaquin on 28/10/16.
//

#include "Fifo.h"

#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

Fifo::Fifo(std::string nombre) {

    this->nombre = nombre;
    // se crea el fifo
    mknod(nombre.c_str(), S_IFIFO | 0666, 0);
    // se inicializa el descriptor en -1
    this->fileDes = -1;
}

Fifo::~Fifo() {
    if (this->fileDes != -1) {
        close(this->fileDes);
    }
}

void Fifo::abrir(int __oflag) {
    if (this->fileDes == -1) {
        this->fileDes = open(this->nombre.c_str(), __oflag);
    }
}

ssize_t Fifo::escribir(char* dato, size_t datoSize) {
    // se abre el file descriptor para escritura
    if (this->fileDes == -1) {
        this->fileDes = open(this->nombre.c_str(), O_WRONLY);
    }

    // se escriben los datos en el fifo
    ssize_t resultado = write(this->fileDes, (const void *) dato, datoSize);

    char pid[10];
    char* str;
    snprintf(pid, 10,"%d",(int)getpid());
    strcat (str, pid);
    if (resultado == -1) {
      std::string mensaje = str + std::string(": Error en Fifo->write(): ") + std::string(strerror(errno)) + std::string("\n");
      throw mensaje;
    }

    return resultado;
}

ssize_t Fifo::leer(char* buffer, size_t buffSize) {
    ssize_t resultado = 0;

    while (resultado == 0) {
        if (this->fileDes == -1) {
            this->fileDes = open(this->nombre.c_str(), O_RDONLY);
        }
        resultado = read(this->fileDes, (void *) buffer, buffSize);
        if (resultado == 0) {
            cerrar();
        }
    }
/*
    char pid[10];
    char* str;
    snprintf(pid, 10,"%d",(int)getpid());
    strcat (str, pid);
    if (resultado == -1) {
      std::string mensaje = str + std::string(": Error en Fifo->read(): ") + std::string(strerror(errno)) + std::string("\n");
      throw mensaje;
    }
*/
    return resultado;
}

void Fifo::cerrar() {
    close(this->fileDes);
    this->fileDes = -1;
}

void Fifo::eliminar() {
    unlink(this->nombre.c_str());
}
