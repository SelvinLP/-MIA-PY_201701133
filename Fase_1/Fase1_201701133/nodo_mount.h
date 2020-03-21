#ifndef NODO_MOUNT_H
#define NODO_MOUNT_H
#include <iostream>
#include <fstream>
#include <QList>

class Nodo_Mount
{
public:
    Nodo_Mount();

    std::string Ruta="";
    std::string Id="";
    std::string Nombre="";
    int cantidad=1;


};

#endif // NODO_MOUNT_H
