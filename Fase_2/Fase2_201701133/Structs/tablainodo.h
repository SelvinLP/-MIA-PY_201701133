#ifndef TABLAINODO_H
#define TABLAINODO_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
//QT
#include <qstring.h>
//fecha
#include <ctime>
//Clases
#include <Structs/superbloque.h>
struct Tabla_Inodo{
    int ID;
    int i_uid;
    int i_gid;
    int i_size;
    char i_atime[9];
    char i_ctime[9];
    char i_mtime[9];
    int i_block [15];
    int i_type;
    int i_perm;

};
class TablaInodo
{
public:
    TablaInodo();

    Tabla_Inodo Tabla_Inodo_Nuevo;

    void Insertar_Inodo(std::string rutabrir,int posicionStart,int tipo,int ID,int ID_Blck,int ID_Usuario);
};

#endif // TABLAINODO_H
