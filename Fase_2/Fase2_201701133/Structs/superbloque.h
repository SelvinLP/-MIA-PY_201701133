#ifndef SUPERBLOQUE_H
#define SUPERBLOQUE_H
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
#include <Structs/bloqueapuntador.h>
#include <Structs/bloquearchivo.h>
#include <Structs/bloquecarpeta.h>
#include <Structs/tablainodo.h>
#include <Structs/bitmap.h>
#include <Structs/bloque_journali.h>
struct Super_Bloque{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    char mtime [9];
    char umtime [9];
    int s_mnt_count;
    char s_magic [7];
    int s_inode_size;
    int s_block_size;
    int s_firts_ino;
    int s_firts_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};
class SuperBloque
{
public:
    SuperBloque();
    Super_Bloque Super_Bloque_Nuevo;
    void InsertarBloque(std::string ruta, int filesystem, unsigned long long int  PosicionStart, unsigned long long int  ParticionSize);
    void EventoMount(std::string rutabrir,int PosicionStart,int Tipo);

    //Creacion de Inodos y Bloques
    void Crear_Carpeta(std::string rutabrir,int PosicionStart,std::string Nombre_Carpeta,std::string Nombre_Padre,int ID_Padre,int ID_Usuario);
    void Crear_Archivo(std::string rutabrir,int PosicionStart,int Tamanio,std::string cont_ruta,int ID_Usuario);

    //Actualizaciones
    void Actualizar_Cantidades(std::string rutabrir,int PosicionStart, int Cantidad_Inodos, int Cantidad_Bloques);

};

#endif // SUPERBLOQUE_H
