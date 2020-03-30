#include "superbloque.h"

SuperBloque::SuperBloque()
{
}

void SuperBloque::InsertarBloque(std::string ruta, int filesystem,unsigned long long int PosicionStart,unsigned long long int ParticionSize){
    Super_Bloque_Nuevo.s_filesystem_type=filesystem;
    //calculo de cantidad de nodos y bloques
    TablaInodo *inodo=new TablaInodo();
    BloqueArchivo *bloquearchivo =new BloqueArchivo();
    std::cout<<"Tamaño de particion: "<<ParticionSize<<std::endl;
    unsigned long long int  Cantidad;
    unsigned long long int  CantidadFinal;
    if(filesystem==2){
        Cantidad=(unsigned long long int)((ParticionSize-sizeof (Super_Bloque))/(4+ sizeof (Nodo_Journaling) +(3*sizeof (Bloque_Carpeta))));
        CantidadFinal=floor(Cantidad);
        //punteros a bitmap y tablas

    }else{
        //es ext3
        Cantidad=(unsigned long long int)((ParticionSize-sizeof (Super_Bloque))/(4+sizeof (Super_Bloque)+ sizeof (Tabla_Inodo) +(3*sizeof (Bloque_Carpeta))));
        CantidadFinal=floor(Cantidad);
        //punteros a bitmap y tablas
    }

    Super_Bloque_Nuevo.s_inodes_count=CantidadFinal;
    Super_Bloque_Nuevo.s_blocks_count=CantidadFinal*3;
    Super_Bloque_Nuevo.s_free_blocks_count=(CantidadFinal*3);
    Super_Bloque_Nuevo.s_free_inodes_count=CantidadFinal;

    //obtener tiempos
    //fecha
    time_t current_time;
    struct tm * time_info;
    char timeString[9];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
    strcpy(Super_Bloque_Nuevo.mtime,timeString);
    strcpy(Super_Bloque_Nuevo.umtime,"");
    Super_Bloque_Nuevo.s_mnt_count=1;
    strcpy(Super_Bloque_Nuevo.s_magic,"0xEF53");
    //tamaño del inodo y bloque
    Super_Bloque_Nuevo.s_inode_size=sizeof (inodo->Tabla_Inodo_Nuevo);
    Super_Bloque_Nuevo.s_block_size=sizeof (bloquearchivo->Bloque_Archivo_Nuevo);
    //primeros nodos
    Super_Bloque_Nuevo.s_firts_ino=0;
    Super_Bloque_Nuevo.s_firts_blo=0;
    Super_Bloque_Nuevo.s_bm_inode_start=PosicionStart+sizeof (Super_Bloque);
    Super_Bloque_Nuevo.s_bm_block_start=PosicionStart+sizeof (Super_Bloque)+(CantidadFinal*sizeof (NodoBitmap));
    Super_Bloque_Nuevo.s_inode_start=PosicionStart+sizeof (Super_Bloque)+(3*CantidadFinal*sizeof (NodoBitmap));
    Super_Bloque_Nuevo.s_block_start=PosicionStart+sizeof (Super_Bloque)+(3*CantidadFinal)+(CantidadFinal*sizeof (inodo->Tabla_Inodo_Nuevo));
    FILE *archivo;
    if ((archivo = fopen(ruta.c_str(),"r+b")) == NULL){
        exit(1);
    }
    fseek(archivo,PosicionStart,SEEK_SET);
    fwrite(&Super_Bloque_Nuevo, sizeof(Super_Bloque), 1, archivo);
    fclose(archivo);

    //Creacion de Carpeta Raiz
    //bitmap de Inodo
    Crear_Carpeta(ruta,PosicionStart,"/","..",0,1);

}

void SuperBloque::EventoMount(std::string rutabrir,int PosicionStart,int Tipo){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        //si tipo es 0 es mount
        //si es 1 es unmount
        if(Tipo==0){
            Nodo_AP.s_mnt_count=Nodo_AP.s_mnt_count+1;
            //obtener tiempos
            //fecha
            time_t current_time;
            struct tm * time_info;
            char timeString[9];
            time(&current_time);
            time_info = localtime(&current_time);
            strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
            std::cout<<"Hora que se monto: "<<timeString<<std::endl;
            strcpy(Nodo_AP.mtime,timeString);
        }
        if(Tipo==1){
            //fecha
            time_t current_time;
            struct tm * time_info;
            char timeString[9];
            time(&current_time);
            time_info = localtime(&current_time);
            strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
            std::cout<<"Hora que se desmonto: "<<timeString<<std::endl;
            strcpy(Nodo_AP.umtime,timeString);
        }
        FILE *archivo;
        if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
            exit(1);
        }
        fseek(archivo,PosicionStart,SEEK_SET);
        fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
        fclose(archivo);

        fclose(arch);



    }
}

void SuperBloque::Crear_Carpeta(std::string rutabrir, int PosicionStart,std::string Nombre_Carpeta,std::string Nombre_Padre,int ID_Padre,int ID_Usuario){
    //primero modificamos SUPER BLOQUE
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        //comprobamos si se puede insertar por la cantidad limitada
        if((Nodo_AP.s_free_inodes_count-1)>0 && (Nodo_AP.s_free_blocks_count-1)>0){

            //llamamos al bitmap y insertamos una posicion
            Bitmap *NodoBitMap=new Bitmap();
            //llenamos para inodo
            NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_inode_start,Nodo_AP.s_bm_block_start);
            //llenamos para bloques
            NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

            //crear inodo de carpeta
            TablaInodo *Nuevo_Inodo=new TablaInodo();
            int posicionInicio_Inodo=Nodo_AP.s_inode_start +(Nodo_AP.s_firts_ino*sizeof (Nuevo_Inodo->Tabla_Inodo_Nuevo));
            Nuevo_Inodo->Insertar_Inodo(rutabrir,posicionInicio_Inodo,0,Nodo_AP.s_firts_ino,Nodo_AP.s_firts_blo,ID_Usuario);

            //Crear bloque carpeta
            BloqueCarpeta *Nuevo_BloqueCarpeta=new BloqueCarpeta();
            int posicionInicio_Bloque=Nodo_AP.s_block_start+(Nodo_AP.s_firts_blo*sizeof (Nuevo_BloqueCarpeta->Bloque_Carpeta_Nuevo));
            Nuevo_BloqueCarpeta->Insertar_BloqueCarpeta(rutabrir,posicionInicio_Bloque,Nodo_AP.s_firts_blo,Nombre_Carpeta,Nodo_AP.s_firts_ino,Nombre_Padre,ID_Padre);


            //Cambios del super bloque
            Nodo_AP.s_free_inodes_count--;
            Nodo_AP.s_free_blocks_count--;
            Nodo_AP.s_firts_ino++;
            Nodo_AP.s_firts_blo++;
        }


        FILE *archivo;
        if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
            exit(1);
        }
        fseek(archivo,PosicionStart,SEEK_SET);
        fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
        fclose(archivo);

        fclose(arch);
    }
}

void SuperBloque::Crear_Archivo(std::string rutabrir, int PosicionStart, int Tamanio, std::string cont_ruta,int ID_Usuario){
    //primero modificamos SUPER BLOQUE
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        //comprobamos si se puede insertar por la cantidad limitada
        if((Nodo_AP.s_free_inodes_count-1)>0 && (Nodo_AP.s_free_blocks_count-1)>0){

            //llamamos al bitmap y insertamos una posicion
            Bitmap *NodoBitMap=new Bitmap();
            //llenamos para inodo
            NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_inode_start,Nodo_AP.s_bm_block_start);

            //crear inodo de Archivo
            TablaInodo *Nuevo_Inodo=new TablaInodo();
            int posicionInicio_Inodo=Nodo_AP.s_inode_start +(Nodo_AP.s_firts_ino*sizeof (Nuevo_Inodo->Tabla_Inodo_Nuevo));
            Nuevo_Inodo->Insertar_Inodo(rutabrir,posicionInicio_Inodo,1,Nodo_AP.s_firts_ino,-1,ID_Usuario);

            //Crear bloque archivo
            //verificacion de contenido
            if(cont_ruta.length()!=0){
                std::fstream archivo(cont_ruta);
                if(archivo.fail()){
                    printf("El archivo cont no se logro abrir \n");
                }else{

                    for (std::string linea; std::getline(archivo, linea); ){
                        QString Contenido;
                        char tem_Contenido [60];

                        Contenido.append(QString::fromStdString(linea));
                        QByteArray ba = Contenido.toLocal8Bit();
                        const char *c_str2 = ba.data();
                        strcpy(tem_Contenido,c_str2);

                        std::cout<<"Se Inserto un Bloque de archivo"<<std::endl;
                        BloqueArchivo *Nuevo_Bloque=new BloqueArchivo();
                        int bandera=Nuevo_Bloque->Insertar_BloqueArchivo_Contenido(PosicionStart,rutabrir,posicionInicio_Inodo,tem_Contenido);

                        //actualizar
                        Nodo_AP.s_free_blocks_count-=bandera;
                        Nodo_AP.s_firts_blo+=bandera;
                        FILE *archivo;
                        if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
                            exit(1);
                        }
                        fseek(archivo,PosicionStart,SEEK_SET);
                        fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
                        fclose(archivo);

                    }
                }
            }else{
                if(Tamanio!=0){
                    //depende del tamaño
                    int restante=Tamanio;
                    //iteradores
                    int posicionchar=0;
                    int numero0a9=0;
                    char tem_Contenido [60]="";
                    QString hola;
                    while (restante>0) {
                        hola.append(QString::number(numero0a9));
                        if(numero0a9==9){
                            numero0a9=-1;
                        }
                        if(posicionchar==59){
                            QByteArray ba = hola.toLocal8Bit();
                            const char *c_str2 = ba.data();
                            strcpy(tem_Contenido,c_str2);
                            posicionchar=-1;

                            BloqueArchivo *Nuevo_Bloque=new BloqueArchivo();
                            int bandera=Nuevo_Bloque->Insertar_BloqueArchivo_Contenido(PosicionStart,rutabrir,posicionInicio_Inodo,tem_Contenido);
                            hola.clear();

                            //actualizar
                            Nodo_AP.s_free_blocks_count-=bandera;
                            Nodo_AP.s_firts_blo+=bandera;
                            FILE *archivo;
                            if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
                                exit(1);
                            }
                            fseek(archivo,PosicionStart,SEEK_SET);
                            fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
                            fclose(archivo);



                        }
                        restante--;
                        posicionchar++;
                        numero0a9++;

                        if(restante==0){
                            if(hola.length()!=0){
                                QByteArray ba = hola.toLocal8Bit();
                                const char *c_str2 = ba.data();
                                strcpy(tem_Contenido,c_str2);
                                BloqueArchivo *Nuevo_Bloque=new BloqueArchivo();
                                int bandera=Nuevo_Bloque->Insertar_BloqueArchivo_Contenido(PosicionStart,rutabrir,posicionInicio_Inodo,tem_Contenido);
                                hola.clear();

                                //actualizar
                                Nodo_AP.s_free_blocks_count-=bandera;
                                Nodo_AP.s_firts_blo+=bandera;
                                FILE *archivo;
                                if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
                                    exit(1);
                                }
                                fseek(archivo,PosicionStart,SEEK_SET);
                                fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
                                fclose(archivo);

                            }

                        }
                    }

                }

            }

            //Cambios del super bloque
            Nodo_AP.s_free_inodes_count--;
            Nodo_AP.s_firts_ino++;
        }


        FILE *archivo;
        if ((archivo = fopen(rutabrir.c_str(),"r+b")) == NULL){
            exit(1);
        }
        fseek(archivo,PosicionStart,SEEK_SET);
        fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
        fclose(archivo);

        fclose(arch);
    }
}

void SuperBloque::Actualizar_Cantidades(std::string rutabrir, int PosicionStart, int Cantidad_Inodos, int Cantidad_Bloques){
    //primero modificamos SUPER BLOQUE
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        //comprobamos si se puede insertar por la cantidad limitada
        if((Nodo_AP.s_free_inodes_count-Cantidad_Inodos)>0 && (Nodo_AP.s_free_blocks_count-Cantidad_Bloques)>0){
            //llamamos al bitmap y insertamos una posicion
            Bitmap *NodoBitMap=new Bitmap();
            //llenamos para inodo
            for(int repeticion=0;repeticion<Cantidad_Inodos;repeticion++){
               NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_inode_start,Nodo_AP.s_bm_block_start);
            }
            //llenamos para bloques
            for(int repeticion=0;repeticion<Cantidad_Bloques;repeticion++){
                NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
            }

            //Cambios del super bloque
            Nodo_AP.s_free_inodes_count=Nodo_AP.s_free_inodes_count-Cantidad_Inodos;
            Nodo_AP.s_free_blocks_count=Nodo_AP.s_free_blocks_count-Cantidad_Bloques;
            Nodo_AP.s_firts_ino=Nodo_AP.s_firts_ino+Cantidad_Inodos;
            Nodo_AP.s_firts_blo=Nodo_AP.s_firts_blo+Cantidad_Bloques;
        }


        fseek(arch,PosicionStart,SEEK_SET);
        fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        fclose(arch);
    }
}
