#ifndef ANALIZADOR_H
#define ANALIZADOR_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <QList>
#include <qprocess.h>

#include <admin_disco.h>
#include <Administrador_UsuyGrup/admin_usuariosygrupos.h>
class Analizador
{
public:
    Analizador();

    Admin_Disco *AdminDiscos;
    Admin_UsuariosyGrupos *AdminUsuyG;

    QList <Nodo_Mount> Lista_Montaje;

    void LeerArchivo(char Ruta[200]);
    void AnalisarComando(char Comando[200]);
    QList <std::string> ListaParametros;
    void EjecuarComando();
    int case_insensitive_match(std::string s1, std::string s2);

};

#endif // ANALIZADOR_H
