#ifndef BLOQUECARPETA_H
#define BLOQUECARPETA_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
//QT
#include <qstring.h>
#include <QList>
//fecha
#include <ctime>
//Clases
#include <Structs/superbloque.h>
#include <Structs/bloqueapuntador.h>
struct Bloque_Carpeta{
    int ID;
    char b_name1 [11];
    int b_inodo1;

    char b_name2 [11];
    int b_inodo2;

    char b_name3 [11];
    int b_inodo3;

    char b_name4 [11];
    int b_inodo4;
};
class BloqueCarpeta
{
public:
    BloqueCarpeta();
    Bloque_Carpeta Bloque_Carpeta_Nuevo;

    void Insertar_BloqueCarpeta(std::string rutabrir,int posicionStart,int ID,std::string Nombre_Carpeta,int Id_Inodo,std::string Nombre_Padre,int Id_Padre);
    void Busqueda_Carpeta(std::string rutabrir,int PosicionStart,std::string Ruta_Buscar, int ID_Usuario,int ID_Grupo);
    void Renombrar(std::string rutabrir,int PosicionStart,std::string Ruta_Buscar, char nombre[11]);
    void Copiar_Contenido(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar,std::string ruta_copiar,int ID_Usuario);

};

#endif // BLOQUECARPETA_H
