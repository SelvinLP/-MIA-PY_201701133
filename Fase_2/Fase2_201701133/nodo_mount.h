#ifndef NODO_MOUNT_H
#define NODO_MOUNT_H
#include <iostream>
#include <fstream>
#include <QList>
#include<Users/structs_users.h>
class Nodo_Mount
{
public:
    Nodo_Mount();

    std::string Ruta="";
    std::string Id="";
    std::string Nombre="";
    std::string Fs;
    unsigned long long int  Posicion_Start;
    unsigned long long int Particion_Size;
    int cantidad=1;
    //QList <Structs_Users> Lista_Usuario;
};

#endif // NODO_MOUNT_H
