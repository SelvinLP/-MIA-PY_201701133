#ifndef ADMIN_PARTICIONES_H
#define ADMIN_PARTICIONES_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <QList>
#include <qprocess.h>
struct MBR_Particion{
  char part_status[2];
  char part_type [2];
  char part_fit [3];
  int part_start;
  int part_size;
  char part_name[16];
};

class Admin_Particiones
{
public:

    Admin_Particiones();
    MBR_Particion ArregloMBR[5];
    MBR_Particion nuevo;
    QList <std::string> Parametros;
    int TamanioMBRDisk;
    int TamanioTotalDisco;
    char fitdisk[3];

    void RecibirParametros(QList  <std::string> P);
    void EventoParticion();
    MBR_Particion RetornarParticionInsertada();
    int pos=-1;
    int Retornopos();

    //comparador
    int case_insensitive_match(std::string s1, std::string s2);
};

#endif // ADMIN_PARTICIONES_H
