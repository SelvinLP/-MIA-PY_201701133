#ifndef ADMIN_DISCO_H
#define ADMIN_DISCO_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
//Qt
#include <QList>
#include <QString>
#include <qdebug.h>
#include <qdir.h>
#include <qprocess.h>
//fecha
#include <ctime>
//clases
#include <admin_particiones.h>
#include <nodo_mount.h>
#include <Analizadores/analizador_caracteres_o.h>


#include <Users/structs_users.h>

struct MBR_Disco{
  int mbr_tamanio;
  char mbr_fecha_creacion[9];
  int mbr_disk_asignature;
  char fisk_fit[3];
  //aqui agregar particion
  MBR_Particion mbr_partition_1;
  MBR_Particion mbr_partition_2;
  MBR_Particion mbr_partition_3;
  MBR_Particion mbr_partition_4;
};


class Admin_Disco
{
public:
    Admin_Disco();

    Admin_Particiones *AdminParticion;
    MBR_Disco nuevo;
    int TamanioMBRDisco;
    QList <std::string> Parametros;

    QList <Nodo_Mount> Lista_Montaje;
    QList <Nodo_Mount> RutaCantidad;
    //structs particiones
    //disco
    void RecibirParametros(QList  <std::string> P);
    void CrearArchivo();
    void EliminarArchivo();
    void Reporte();
    void Montar();
    void Desmontar();
    //particiones
    void EventoParticion();

    //FASE 2
    void FormateoEXT();
    //comparador
    int case_insensitive_match(std::string s1, std::string s2);
};

#endif // ADMIN_DISCO_H
