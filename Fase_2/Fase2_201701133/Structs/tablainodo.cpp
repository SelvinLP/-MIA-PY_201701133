#include "tablainodo.h"

TablaInodo::TablaInodo()
{

}
void TablaInodo::Insertar_Inodo(std::string rutabrir, int posicionStart, int tipo, int ID,int ID_Blck,int ID_Usuario){
    //tipo si es 0 es Carpeta
    //1 es Archivo
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        fseek(arch,posicionStart,SEEK_SET);
        Tabla_Inodo_Nuevo.ID=ID;
        Tabla_Inodo_Nuevo.i_uid=ID_Usuario;
        Tabla_Inodo_Nuevo.i_gid=2;
        Tabla_Inodo_Nuevo.i_size=64;
        //obtener tiempos
        //fecha
        time_t current_time;
        struct tm * time_info;
        char timeString[9];
        time(&current_time);
        time_info = localtime(&current_time);
        strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
        strcpy(Tabla_Inodo_Nuevo.i_atime,timeString);//la que se leyo
        strcpy(Tabla_Inodo_Nuevo.i_ctime,timeString);//la que se creo
        strcpy(Tabla_Inodo_Nuevo.i_mtime,"");

        for(int posicion=0;posicion<15;posicion++){
            Tabla_Inodo_Nuevo.i_block[posicion]=-1;
        }
        Tabla_Inodo_Nuevo.i_block[0]=ID_Blck;
        Tabla_Inodo_Nuevo.i_type=tipo;
        Tabla_Inodo_Nuevo.i_perm=664;

        fwrite(&Tabla_Inodo_Nuevo, sizeof(Tabla_Inodo), 1, arch);
        fclose(arch);
    }

}
