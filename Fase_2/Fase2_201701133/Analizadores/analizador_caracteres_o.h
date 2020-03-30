#ifndef ANALIZADOR_CARACTERES_O_H
#define ANALIZADOR_CARACTERES_O_H
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
class Analizador_Caracteres_O
{
public:
    Analizador_Caracteres_O();
    QList <std::string> Parametros;
    //variables
    int tamanio;
    std::string ruta;
    std::string rutaReporte;
    char fit[3]="FF";
    int tamaniobytes=1048576;
    std::string tiponombre;
    std::string id;

    //admin grupos y usuarios
    std::string Usuario;
    std::string Password;
    std::string Grupo;

    //admin de archivos
    std::string P;
    std::string cont_ruta;
    std::string file;

    //permisos
    int ugo;
    std::string R;

    void RecibirParametros(QList  <std::string> P);

    void AnalisarCaracteres();

    //comparador
    int case_insensitive_match(std::string s1, std::string s2);
};

#endif // ANALIZADOR_CARACTERES_O_H
