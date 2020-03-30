#include "bloqueapuntador.h"

BloqueApuntador::BloqueApuntador()
{

}
void BloqueApuntador::CrearApuntador(std::string rutabrir, int posicionStart, int ID){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        fseek(arch,posicionStart,SEEK_SET);
        Bloque_Apuntador_Nuevo.ID=ID;

        fwrite(&Bloque_Apuntador_Nuevo, sizeof(Bloque_Apuntador), 1, arch);
        fclose(arch);
    }
}
