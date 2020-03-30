#ifndef BLOQUE_JOURNALI_H
#define BLOQUE_JOURNALI_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//QT
#include <qstring.h>
//fecha
#include <ctime>
//clases
#include <Structs/superbloque.h>
struct Nodo_Journaling{
    int Ultimo;
    char ruta[60];
    int size;
    char tipo[10];
    char Nombre[11];
    char mtime [9];
    char Descripcion[25];
};
class Bloque_Journali
{
public:
    Bloque_Journali();
    void Insertar_BloqueJour(std::string rutabrir, int ParticionStart,char ruta[60],int size,char tipo[10],char Nombre[11],char Descripcion[25]);
};

#endif // BLOQUE_JOURNALI_H
