#ifndef PERMISOS_H
#define PERMISOS_H
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

class Permisos
{
public:
    Permisos();
    bool Permiso_Lectura(int ugo, int Id_UserInodo,int Id_UserGrupo,int Id_Log);
    bool Permiso_Escritura(int ugo, int Id_UserInodo,int Id_UserGrupo,int Id_Log);
    bool Permiso_Ejecucion(int ugo, int Id_UserInodo,int Id_UserGrupo,int Id_Log);
    void Cambio_Permisos(std::string rutabrir,int posicionStart,std::string ruta,int ID_Log,int Ugo);
    void Cambio_Propetario(std::string rutabrir,int posicionStart,std::string ruta,int ID_Log,int Id_Nueva);
};

#endif // PERMISOS_H
