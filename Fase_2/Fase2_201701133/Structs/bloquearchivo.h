#ifndef BLOQUEARCHIVO_H
#define BLOQUEARCHIVO_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
//Clases
#include <Structs/superbloque.h>
#include <Structs/bloqueapuntador.h>
struct Bloque_Archivo{
    int ID;
    char b_content [60];
};
class BloqueArchivo
{
public:
    BloqueArchivo();
    Bloque_Archivo Bloque_Archivo_Nuevo;

    void Busqueda_Archivo(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar,int tamanio, std::string cont_ruta,int ID_Usuario);
    int Insertar_BloqueArchivo_Contenido(int Posicion_Super,std::string rutabrir,int PosicionStart,char contenido[60]);

    //Usuarios
    void Modificar_Users(int Posicion_Super,std::string rutabrir,int PosicionStart,char contenido[60], char contenidocomparar[60]);

    //Otros
    std::string Mostrar_Contenido(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar);
    void Editar_Contenido(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar,char contenido[60]);

};

#endif // BLOQUEARCHIVO_H
