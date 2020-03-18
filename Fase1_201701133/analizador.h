#ifndef ANALIZADOR_H
#define ANALIZADOR_H
#include <iostream>
#include <fstream>
#include <QList>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <admin_disco.h>

class Analizador
{
public:
    Analizador();

    Admin_Disco *AdminDiscos;

    void LeerArchivo(char Ruta[200]);
    void AnalisarComando(char Comando[200]);
    QList <std::string> ListaParametros;
    void EjecuarComando();
    int case_insensitive_match(std::string s1, std::string s2);

};

#endif // ANALIZADOR_H
