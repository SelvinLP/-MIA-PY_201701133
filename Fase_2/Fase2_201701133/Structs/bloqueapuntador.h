#ifndef BLOQUEAPUNTADOR_H
#define BLOQUEAPUNTADOR_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
//QT
#include <qstring.h>
#include <QList>
struct Bloque_Apuntador{
    int ID;
    int b_pointers [15];
};
class BloqueApuntador
{
public:
    BloqueApuntador();
    Bloque_Apuntador Bloque_Apuntador_Nuevo;

    void CrearApuntador(std::string rutabrir,int posicionStart,int ID);
};

#endif // BLOQUEAPUNTADOR_H
