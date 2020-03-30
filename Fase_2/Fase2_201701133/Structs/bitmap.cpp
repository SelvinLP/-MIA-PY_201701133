#include "bitmap.h"

Bitmap::Bitmap()
{

}
void Bitmap::InsertarDato(std::string rutabrir, int posicionStart, int PosicionFinal){
    //primero modificamos SUPER BLOQUE
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{
        NodoBitmap Nodo_temporal;
        int posicion_Insertar=0;
        for(int posicionLectura=posicionStart;posicionLectura<PosicionFinal;posicionLectura++){
            fseek(arch,posicionLectura,SEEK_SET);
            fread(&Nodo_temporal, sizeof(NodoBitmap), 1, arch);
            if(std::to_string(Nodo_temporal.Dato)=="0"){
                posicion_Insertar=posicionLectura;
                break;
            }
        }
        fclose(arch);
        if(posicion_Insertar!=0){
            FILE *archivo;
            if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
            }else{
                fseek(archivo,posicion_Insertar,SEEK_SET);
                Nodo_Nuevo.Dato=1;
                fwrite(&Nodo_Nuevo, sizeof(NodoBitmap), 1, archivo);
                fclose(archivo);
            }

        }

    }
}
