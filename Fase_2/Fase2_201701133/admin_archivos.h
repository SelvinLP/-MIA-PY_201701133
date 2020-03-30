#ifndef ADMIN_ARCHIVOS_H
#define ADMIN_ARCHIVOS_H
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
#include <Analizadores/analizador_caracteres_o.h>
#include <Structs/bloquecarpeta.h>
#include <Structs/bloqueapuntador.h>
#include <Structs/bloquearchivo.h>
#include <nodo_mount.h>
#include <Structs/bloque_journali.h>
#include <Administrador_UsuyGrup/permisos.h>
class Admin_Archivos
{
public:
    Admin_Archivos();

    QList <std::string> Parametros;
    QList <Nodo_Mount> Lista_Montaje;
    QString id_montada;
    int ID_Usuario;
    void RecibirParametros(QList  <std::string> P);

    void Ejecutar_MKFILE();
    void Ejecutar_MKDIR();

    void Ejecutar_CAT();
    void Ejecutar_EDIT();
    void Ejecutar_REN();
    void Ejecutar_CP();
    void Ejecutar_FIND();
    void Ejecutar_LOSS();
    void Ejecutar_CHMOD();
    void Ejecutar_CHOWN();

    std::string inicio;
    std::string fin;
    void Graficar_Nodofind(std::string rutabrir,int PosicionSuperB, int tipo, int posicion,std::string Contenido,bool bandera);
    void Punteros(std::string rutabrir, int posicionStart, int tipo,int PosicionSuperB ,int NumerodeApuuntadores,std::string Contenido, bool bandera);

    //comparador
    int case_insensitive_match(std::string s1, std::string s2);
};

#endif // ADMIN_ARCHIVOS_H
