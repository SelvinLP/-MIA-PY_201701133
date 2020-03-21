#ifndef ADMIN_USUARIOSYGRUPOS_H
#define ADMIN_USUARIOSYGRUPOS_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
//Qt
#include <QList>
#include <QString>
#include <nodo_mount.h>
#include <Analizadores/analizador_caracteres_o.h>
class Admin_UsuariosyGrupos
{
public:
    Admin_UsuariosyGrupos();
    QList <std::string> Parametros;
    QList <Nodo_Mount> Lista_Montaje;

    QString UsuarioLog;
    QString Id_Particion;

    void RecibirParametros(QList  <std::string> P);
    void Login();
    void Logout();
    void CrearGrupo();
    void EliminarGrupo();
    void CrearUsuario();
    void EliminarUsuario();

    //comparador
    int case_insensitive_match(std::string s1, std::string s2);
};

#endif // ADMIN_USUARIOSYGRUPOS_H
