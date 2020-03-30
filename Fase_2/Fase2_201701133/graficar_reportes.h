#ifndef GRAFICAR_REPORTES_H
#define GRAFICAR_REPORTES_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
//Qt
#include <QList>
#include <QString>
#include <qdir.h>
//clases
#include <nodo_mount.h>
#include <admin_disco.h>
#include <Structs/superbloque.h>
#include <iomanip>
class Graficar_Reportes
{
public:
    Graficar_Reportes();

    QList <Nodo_Mount> Lista_Montaje;
    std::string CadenaImprimir;
    QList <int> temporal;
    QList <std::string> Id_Loss;
    void Graficar_Mbr(std::string rutaarir,std::string id, std::string ruta);
    void Graficar_Disk(std::string rutaarir,std::string id, std::string ruta);
    void Graficar_Sb(std::string rutabrir, std::string id, std::string ruta);
    void Graficar_bm(std::string rutabrir, std::string id, std::string ruta,int tipo);
    void Graficar_tree(std::string rutabrir, std::string id, std::string ruta);
    void Agregar_Contenido_Inodo_tree(std::string rutabrir,int posicionStart, int PosicionSuperB);
    void Agregar_Contenido_Block_tree(std::string rutabrir,int posicionStart, int tipo,int PosicionSuperB,int PosicionCuadroInode);
    void Agregar_Contenido_Block_tree_Puntero(std::string rutabrir,int posicionStart, int tipo,int PosicionSuperB,int NumerodeApuuntadores);
    void Graficar_inode(std::string rutabrir, std::string id, std::string ruta);
    void Graficar_file(std::string rutabrir, std::string id, std::string ruta,std::string rutaBuscar);
    void Graficar_Journaling(std::string rutabrir, std::string id, std::string ruta);
    void Graficar_Ls(std::string rutabrir, std::string id, std::string ruta);

    void Graficar_block(std::string rutabrir, std::string id, std::string ruta);
    void Graficar_NodoBlock(std::string rutabrir,int PosicionSuperB, int tipo, int posicion);
    void Punteros(std::string rutabrir, int posicionStart, int tipo,int PosicionSuperB ,int NumerodeApuuntadores);
};

#endif // GRAFICAR_REPORTES_H
