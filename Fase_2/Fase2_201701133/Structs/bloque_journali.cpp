#include "bloque_journali.h"

Bloque_Journali::Bloque_Journali()
{

}
void Bloque_Journali::Insertar_BloqueJour(std::string rutabrir, int ParticionStart, char *ruta, int size, char *tipo, char *Nombre, char *Descripcion){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        //cambio el actual a 0 y el nuevo le ponto 1
        Super_Bloque Nodo_AP;
        fseek(arch,ParticionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
        unsigned long long int poicionInicial=Nodo_AP.s_block_start*Nodo_AP.s_blocks_count;
        int Contador_Limite=0;
        while (true) {
            Contador_Limite++;
            Nodo_Journaling actual;
            fseek(arch,poicionInicial,SEEK_SET);
            fread(&actual, sizeof(Nodo_Journaling), 1, arch);
            if(actual.Ultimo==1){
                if(Contador_Limite<99){
                    //podeos agregar
                    actual.Ultimo=0;
                    fseek(arch,poicionInicial,SEEK_SET);
                    fwrite(&actual, sizeof(Nodo_Journaling), 1, arch);

                    Nodo_Journaling nuevo;
                    nuevo.Ultimo=1;
                    strcpy(nuevo.ruta,ruta);
                    nuevo.size=size;
                    strcpy(nuevo.tipo,tipo);
                    strcpy(nuevo.Nombre,Nombre);
                    //fecha
                    time_t current_time;
                    struct tm * time_info;
                    char timeString[9];
                    time(&current_time);
                    time_info = localtime(&current_time);
                    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
                    strcpy(nuevo.mtime,timeString);
                    strcpy(nuevo.Descripcion,Descripcion);


                    fseek(arch,poicionInicial+sizeof(Nodo_Journaling),SEEK_SET);
                    fwrite(&nuevo, sizeof(Nodo_Journaling), 1, arch);
                }
                break;
            }else{
                poicionInicial+=sizeof(Nodo_Journaling);
            }

        }

        fclose(arch);
    }
}
