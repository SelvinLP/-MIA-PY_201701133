#include "bloquearchivo.h"

BloqueArchivo::BloqueArchivo()
{

}

int BloqueArchivo::Insertar_BloqueArchivo_Contenido(int Posicion_Super,std::string rutabrir, int PosicionStart, char contenido[60]){
    int insertado=0;
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,Posicion_Super,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        Tabla_Inodo Tabla_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
        //hacemos busqueda de donde insertar
        for(int posicion=0;posicion<15;posicion++){
            //bloques directos

            if(posicion<12){
                if(Tabla_AP.i_block[posicion]==-1){
                    //se puede insertar
                    Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo;
                    strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                    //insertamos bloque
                    int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Nodo_AP.s_firts_blo);
                    fseek(arch,posI,SEEK_SET);
                    fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                    //actualizacion de inodo
                    fseek(arch,PosicionStart,SEEK_SET);
                    Tabla_AP.i_block[posicion]=Nodo_AP.s_firts_blo;
                    Tabla_AP.i_size+=64;
                    fwrite(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);

                    //agregamos a bitmap
                    Bitmap *NodoBitMap=new Bitmap();
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                    fclose(arch);
                    insertado=1;
                    break;
                }
            }
            //Simple Indirecto
            if(posicion==12){
                if(Tabla_AP.i_block[posicion]==-1){
                    //creamos nodo puntero
                    Bloque_Apuntador NuevoApun;
                    NuevoApun.ID=Nodo_AP.s_firts_blo;
                    for(int pos=0;pos<15;pos++){
                        NuevoApun.b_pointers[pos]=-1;
                    }
                    NuevoApun.b_pointers[0]=Nodo_AP.s_firts_blo+1;
                    //Insertamos bloque apuntadores
                    int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Nodo_AP.s_firts_blo);
                    fseek(arch,posI,SEEK_SET);
                    fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                    //actualizacion de inodo
                    fseek(arch,PosicionStart,SEEK_SET);
                    Tabla_AP.i_block[posicion]=Nodo_AP.s_firts_blo;
                    Tabla_AP.i_size+=128;
                    fwrite(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);

                    //inserto bloque contenido
                    Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo+1;
                    strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                    //insertamos bloque archivo
                    posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo+1));
                    fseek(arch,posI,SEEK_SET);
                    fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                    //agregamos a bitmap
                    Bitmap *NodoBitMap=new Bitmap();
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                    fclose(arch);
                    insertado=2;
                    break;
                }else{
                    //busca y inserta
                    Bloque_Apuntador NuevoApun;
                    int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_AP.i_block[posicion]);
                    fseek(arch,pos_I,SEEK_SET);
                    fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                    bool band=false;
                    for(int pos=0;pos<15;pos++){
                        if(NuevoApun.b_pointers[pos]==-1){
                            //Actualizamos Bloque
                            NuevoApun.b_pointers[pos]=Nodo_AP.s_firts_blo;
                            fseek(arch,pos_I,SEEK_SET);
                            fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                            //inserto bloque contenido
                            Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo;
                            strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                            //insertamos bloque archivo
                            pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo));
                            fseek(arch,pos_I,SEEK_SET);
                            fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                            //agregamos a bitmap
                            Bitmap *NodoBitMap=new Bitmap();
                            NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                            fclose(arch);
                            band=true;
                            insertado=1;
                            break;
                        }
                    }
                    //si se inserto se sale
                    if(band==true){
                        break;
                    }

                }

            }
            //Doble Indirecto
            if(posicion==13){
                if(Tabla_AP.i_block[posicion]==-1){
                    //creamos nodo puntero
                    for(int ciclo=0;ciclo<2;ciclo++){
                        Bloque_Apuntador NuevoApun;
                        NuevoApun.ID=Nodo_AP.s_firts_blo+ciclo;
                        for(int pos=0;pos<15;pos++){
                            NuevoApun.b_pointers[pos]=-1;
                        }
                        NuevoApun.b_pointers[0]=Nodo_AP.s_firts_blo+1+ciclo;
                        //Insertamos bloque apuntadores
                        int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo+ciclo));
                        fseek(arch,posI,SEEK_SET);
                        fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                    }


                    //actualizacion de inodo
                    fseek(arch,PosicionStart,SEEK_SET);
                    Tabla_AP.i_block[posicion]=Nodo_AP.s_firts_blo;
                    Tabla_AP.i_size+=192;
                    fwrite(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);

                    //inserto bloque contenido
                    Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo+2;
                    strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                    //insertamos bloque archivo
                    int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo+2));
                    fseek(arch,posI,SEEK_SET);
                    fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                    //agregamos a bitmap
                    Bitmap *NodoBitMap=new Bitmap();
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                    fclose(arch);
                    insertado=3;
                    break;
                }else{
                    //busca y inserta
                    bool band=false;
                    for(int pos=0;pos<15;pos++){
                        Bloque_Apuntador NuevoApun;
                        int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_AP.i_block[posicion]);
                        fseek(arch,pos_I,SEEK_SET);
                        fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                        if(NuevoApun.b_pointers[pos]!=-1){
                            //busca y inserta
                            Bloque_Apuntador NuevoApun2;
                            pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos]);
                            fseek(arch,pos_I,SEEK_SET);
                            fread(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);
                            for(int pos2=0;pos2<15;pos2++){
                                if(NuevoApun2.b_pointers[pos2]==-1){
                                    //Actualizamos Bloque
                                    NuevoApun2.b_pointers[pos2]=Nodo_AP.s_firts_blo;
                                    fseek(arch,pos_I,SEEK_SET);
                                    fwrite(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);

                                    //inserto bloque contenido
                                    Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo;
                                    strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                                    //insertamos bloque archivo
                                    pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo));
                                    fseek(arch,pos_I,SEEK_SET);
                                    fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                                    //agregamos a bitmap
                                    Bitmap *NodoBitMap=new Bitmap();
                                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                                    fclose(arch);
                                    band=true;
                                    insertado=1;

                                    break;
                                }
                            }
                            if(band==true){
                                break;
                            }
                        }else{
                            //crea y inserta
                            NuevoApun.b_pointers[pos]=Nodo_AP.s_firts_blo;
                            int pos_I2=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_AP.i_block[posicion]);
                            fseek(arch,pos_I2,SEEK_SET);
                            fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                            //creamos nodo puntero
                            Bloque_Apuntador NuevoApun2;
                            NuevoApun2.ID=Nodo_AP.s_firts_blo;
                            for(int pos2=0;pos2<15;pos2++){
                                NuevoApun2.b_pointers[pos2]=-1;
                            }
                            NuevoApun2.b_pointers[0]=Nodo_AP.s_firts_blo+1;
                            //Insertamos bloque apuntadores
                            int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Nodo_AP.s_firts_blo);
                            fseek(arch,posI,SEEK_SET);
                            fwrite(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);

                            //inserto bloque contenido
                            Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo+1;
                            strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                            //insertamos bloque archivo
                            posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo+1));
                            fseek(arch,posI,SEEK_SET);
                            fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                            //agregamos a bitmap
                            Bitmap *NodoBitMap=new Bitmap();
                            NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                            NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                            fclose(arch);
                            band=true;
                            insertado=2;
                            break;
                        }
                    }
                    //si se inserto se sale
                    if(band==true){
                        break;
                    }

                }

            }
            //Triple Indirecto
            if(posicion==14){
                if(Tabla_AP.i_block[posicion]==-1){
                    //creamos nodo puntero
                    for(int ciclo=0;ciclo<3;ciclo++){
                        Bloque_Apuntador NuevoApun;
                        NuevoApun.ID=Nodo_AP.s_firts_blo+ciclo;
                        for(int pos=0;pos<15;pos++){
                            NuevoApun.b_pointers[pos]=-1;
                        }
                        NuevoApun.b_pointers[0]=Nodo_AP.s_firts_blo+1+ciclo;
                        //Insertamos bloque apuntadores
                        int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo+ciclo));
                        fseek(arch,posI,SEEK_SET);
                        fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                    }


                    //actualizacion de inodo
                    fseek(arch,PosicionStart,SEEK_SET);
                    Tabla_AP.i_block[posicion]=Nodo_AP.s_firts_blo;
                    fwrite(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);

                    //inserto bloque contenido
                    Bloque_Archivo_Nuevo.ID=Nodo_AP.s_firts_blo+3;
                    strcpy(Bloque_Archivo_Nuevo.b_content,contenido);

                    //insertamos bloque archivo
                    int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*(Nodo_AP.s_firts_blo+3));
                    fseek(arch,posI,SEEK_SET);
                    fwrite(&Bloque_Archivo_Nuevo, sizeof(Bloque_Carpeta), 1, arch);

                    //agregamos a bitmap
                    Bitmap *NodoBitMap=new Bitmap();
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);
                    NodoBitMap->InsertarDato(rutabrir,Nodo_AP.s_bm_block_start,Nodo_AP.s_inode_start);

                    fclose(arch);
                    insertado=4;
                    break;
                }
            }

        }
        if(insertado==0){
            std::cout<<"Espacio Insuficiente en el Archivo: "<<std::endl;
        }


    }

    return insertado;
}

void BloqueArchivo::Busqueda_Archivo(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar,int tamanio, std::string cont_ruta, int ID_Usuario){
    int posicionInicio;

    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
        posicionInicio=Nodo_AP.s_inode_start;

        //empezamos los recorridos
        QString qstr = QString::fromStdString(Ruta_Buscar);
        QStringList list1 = qstr.split('/');

        //el for sirve para crear blockes se repetira si se crearn y luego busca insertar
        for(int ciclo_Insercion=0;ciclo_Insercion<1;ciclo_Insercion++){

            //mas de uno entonces debe realizar una busqueda para insertar
            int posicionLectura=posicionInicio;


            for(int posicion_Varios=0;posicion_Varios<list1.size();posicion_Varios++){

                if(posicion_Varios+1==list1.size()){
                    //insertar
                    Tabla_Inodo TablaPrimero;
                    fseek(arch,posicionLectura,SEEK_SET);
                    fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                    for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                        //no igual carpeta y espacio libre
                        //bloques directos
                        if(posicionPrimero<12){
                            if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Carpeta Bloque_CP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                //comproamos si la carpeta
                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                    break;
                                    std::cout<<"El archivo Ya existe"<<std::endl;
                                }else{
                                    //comprobamos i hay espacio en este bloque
                                    if(Bloque_CP.b_inodo1==-1){
                                        //inserta
                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                        const char *c_str2 = ba.data();
                                        strcpy(Bloque_CP.b_name1,c_str2);
                                        Bloque_CP.b_inodo1=Nodo_AP.s_firts_ino;

                                        fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);

                                        //crear Archivo
                                        fclose(arch);
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Archivo(rutabrir,PosicionStart,tamanio,cont_ruta,ID_Usuario);
                                        std::cout<<"Se ha Creado el archivo Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;

                                        break;

                                    }else if(Bloque_CP.b_inodo2==-1){
                                        //inserta
                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                        const char *c_str2 = ba.data();
                                        strcpy(Bloque_CP.b_name2,c_str2);
                                        Bloque_CP.b_inodo2=Nodo_AP.s_firts_ino;

                                        fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                        fclose(arch);
                                        //crear Archivo

                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Archivo(rutabrir,PosicionStart,tamanio,cont_ruta,ID_Usuario);
                                        std::cout<<"Se ha Creado el archivo Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                        break;
                                    }else if(Bloque_CP.b_inodo3==-1){
                                        //inserta
                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                        const char *c_str2 = ba.data();
                                        strcpy(Bloque_CP.b_name3,c_str2);
                                        Bloque_CP.b_inodo3=Nodo_AP.s_firts_ino;

                                        fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                        fclose(arch);
                                        //crear Archivo

                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Archivo(rutabrir,PosicionStart,tamanio,cont_ruta,ID_Usuario);
                                        std::cout<<"Se ha Creado el archivo Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                        break;
                                    }else if(Bloque_CP.b_inodo4==-1){
                                        //inserta
                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                        const char *c_str2 = ba.data();
                                        strcpy(Bloque_CP.b_name4,c_str2);
                                        Bloque_CP.b_inodo4=Nodo_AP.s_firts_ino;

                                        fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                        fclose(arch);
                                        //crear Archivo

                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Archivo(rutabrir,PosicionStart,tamanio,cont_ruta,ID_Usuario);
                                        std::cout<<"Se ha Creado el archivo Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                        break;
                                    }
                                }
                            }else{
                                TablaPrimero.i_block[posicionPrimero]=Nodo_AP.s_firts_blo;
                                //se crea nodo carpeta
                                int posicion_Inicial_Carpeta=Nodo_AP.s_block_start+(Nodo_AP.s_firts_blo*sizeof (Bloque_Carpeta));
                                BloqueCarpeta *nueva_Carpeta=new BloqueCarpeta();
                                nueva_Carpeta->Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carpeta,Nodo_AP.s_firts_blo,".",TablaPrimero.ID," ",-1);

                                //actualizacion de bitmap y superbloque
                                SuperBloque *nuevo_Super=new SuperBloque();
                                nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,1);

                                //acutualizacion de inodo
                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);

                                //Insertar Valor
                                posicion_Varios--;
                                break;
                            }
                        }

                        //bloque simple indirecto
                        if(posicionPrimero==12){
                            if(TablaPrimero.i_block[posicionPrimero]==-1){
//                                //se crea el apuntador
//                                TablaPrimero.i_block[posicionPrimero]=Nodo_AP.s_firts_blo;
//                                //se crea nodo apuntador
//                                int posicion_Inicial_Puntero=Nodo_AP.s_block_start+(Nodo_AP.s_firts_blo*sizeof (Bloque_Apuntador));
//                                BloqueApuntador* Crear_Apunador=new BloqueApuntador();
//                                Crear_Apunador->CrearApuntador(rutabrir,posicion_Inicial_Puntero,Nodo_AP.s_firts_blo);

                            }
                        }

                        //bloque doble indirecto
                        if(posicionPrimero==13){
                        }

                        //bloque triple indirecto
                        if(posicionPrimero==14){
                        }
                    }

                }else{
                    int reconocio=0;//0 no reconocio 1 si reconocio
                    //iterar
                    Tabla_Inodo TablaPrimero;
                    fseek(arch,posicionLectura,SEEK_SET);
                    fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                    for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                        //no igual carpeta y espacio libre
                        //bloques directos

                        if(posicionPrimero<12){
                            if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Carpeta Bloque_CP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                //comproamos si la carpeta existe
                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){

                                    TablaPrimero.i_size+=tamanio;
                                    fseek(arch,posicionLectura,SEEK_SET);
                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                    //cambio de posicion
                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                    reconocio=1;
                                    break;
                                }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){

                                     TablaPrimero.i_size+=tamanio;
                                    fseek(arch,posicionLectura,SEEK_SET);
                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                    //cambio de posicion
                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                    reconocio=1;
                                    break;
                                }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){

                                     TablaPrimero.i_size+=tamanio;
                                    fseek(arch,posicionLectura,SEEK_SET);
                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                    //cambio de posicion
                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                    reconocio=1;
                                    break;
                                }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){

                                     TablaPrimero.i_size+=tamanio;
                                    fseek(arch,posicionLectura,SEEK_SET);
                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                    //cambio de posicion
                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                    reconocio=1;
                                    break;
                                }

                            }
                        }


                        //bloque simple indirecto
                        if(posicionPrimero==12){
                            if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                //comprobamos las posiciones de los bloques
                                for(int Pos_1=0;Pos_1<15;Pos_1++){
                                    int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                    Bloque_Apuntador Bloque_AP;
                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                    fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                    if(Bloque_AP.b_pointers[Pos_1]!=-1){
                                        int posicion_Bloque_Name2=Nodo_AP.s_block_start+(Bloque_AP.b_pointers[Pos_1]*sizeof (Bloque_Carpeta));
                                        Bloque_Carpeta Bloque_CP;
                                        fseek(arch,posicion_Bloque_Name2,SEEK_SET);
                                        fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                        //comproamos si la carpeta existe
                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){

                                            TablaPrimero.i_size+=tamanio;
                                            fseek(arch,posicionLectura,SEEK_SET);
                                            fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                            //cambio de posicion
                                            posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                            reconocio=1;
                                            break;
                                        }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){

                                             TablaPrimero.i_size+=tamanio;
                                            fseek(arch,posicionLectura,SEEK_SET);
                                            fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                            //cambio de posicion
                                            posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                            reconocio=1;
                                            break;
                                        }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){

                                             TablaPrimero.i_size+=tamanio;
                                            fseek(arch,posicionLectura,SEEK_SET);
                                            fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                            //cambio de posicion
                                            posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                            reconocio=1;
                                            break;
                                        }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){

                                             TablaPrimero.i_size+=tamanio;
                                            fseek(arch,posicionLectura,SEEK_SET);
                                            fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                            //cambio de posicion
                                            posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                            reconocio=1;
                                            break;
                                        }
                                    }
                                }
                                if(reconocio==1){
                                    break;
                                }

                            }
                        }

                        //bloque doble indirecto
                        if(posicionPrimero==13){
                            if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                //comprobamos las posiciones de los bloques
                                for(int Pos_1=0;Pos_1<15;Pos_1++){
                                    int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                    Bloque_Apuntador Bloque_AP;
                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                    fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                    if(Bloque_AP.b_pointers[Pos_1]!=-1){
                                        //ciclo del segundo bloque
                                        for(int Pos_2=0;Pos_2<15;Pos_2++){
                                            int posicion_Bloque_Name2=Nodo_AP.s_block_start+(Bloque_AP.b_pointers[Pos_1]*sizeof (Bloque_Carpeta));
                                            Bloque_Apuntador Bloque_AP2;
                                            fseek(arch,posicion_Bloque_Name2,SEEK_SET);
                                            fread(&Bloque_AP2, sizeof(Bloque_Carpeta), 1, arch);
                                            if(Bloque_AP2.b_pointers[Pos_2]!=-1){
                                                //buscamos
                                                int posicion_Bloque_Name3=Nodo_AP.s_block_start+(Bloque_AP2.b_pointers[Pos_2]*sizeof (Bloque_Carpeta));
                                                Bloque_Carpeta Bloque_CP;
                                                fseek(arch,posicion_Bloque_Name3,SEEK_SET);
                                                fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                //comproamos si la carpeta existe
                                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){

                                                     TablaPrimero.i_size+=tamanio;
                                                    fseek(arch,posicionLectura,SEEK_SET);
                                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                    //cambio de posicion
                                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                    reconocio=1;
                                                    break;
                                                }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){

                                                     TablaPrimero.i_size+=tamanio;
                                                    fseek(arch,posicionLectura,SEEK_SET);
                                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                    //cambio de posicion
                                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                    reconocio=1;
                                                    break;
                                                }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){

                                                     TablaPrimero.i_size+=tamanio;
                                                    fseek(arch,posicionLectura,SEEK_SET);
                                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                    //cambio de posicion
                                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                    reconocio=1;
                                                    break;
                                                }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){

                                                     TablaPrimero.i_size+=tamanio;
                                                    fseek(arch,posicionLectura,SEEK_SET);
                                                    fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                    //cambio de posicion
                                                    posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                                    reconocio=1;
                                                    break;
                                                }



                                            }
                                        }

                                        if(reconocio==1){
                                            break;
                                        }
                                    }
                                }

                                if(reconocio==1){
                                    break;
                                }
                            }
                        }


                        //bloque triple indirecto
                        if(posicionPrimero==14){
                        }

                    }
                    //si no reconocio se sale de todo
                    if(reconocio==0){
                        std::cout<<"la Carpeta no existe no se puede insertar: "<<list1[posicion_Varios].toStdString()<<std::endl;
                        break;
                    }


                }


            }

        }


    }
}

void BloqueArchivo::Modificar_Users(int Posicion_Super, std::string rutabrir, int PosicionStart, char *contenido, char *contenidocomparar){
    int insertado=0;
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,Posicion_Super,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

        Tabla_Inodo Tabla_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
        //hacemos busqueda de donde insertar
        for(int posicion=0;posicion<15;posicion++){
            //bloques directos

            if(posicion<12){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //se puede insertar
                    Bloque_Archivo Bloque_AP;
                    int posicion_Bloque=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_AP.i_block[posicion]);
                    fseek(arch,posicion_Bloque,SEEK_SET);
                    fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);

                    if(strcmp(Bloque_AP.b_content,contenidocomparar)==0){
                        strcpy( Bloque_AP.b_content,contenido);
                        fseek(arch,posicion_Bloque,SEEK_SET);
                        fwrite(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                        fclose(arch);
                        insertado=1;
                        break;
                    }
                    //std::cout<<"Debio actualizar"<<contenido<<"--"<<contenidocomparar<<std::endl;

                }
            }
            //Simple Indirecto
            if(posicion==12){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //busca y inserta
                    Bloque_Apuntador NuevoApun;
                    int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_AP.i_block[posicion]);
                    fseek(arch,pos_I,SEEK_SET);
                    fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                    bool band=false;
                    for(int pos=0;pos<15;pos++){
                        if(NuevoApun.b_pointers[pos]!=-1){
                            Bloque_Archivo Bloque_AP;
                            int posicion_Bloque=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos]);
                            fseek(arch,posicion_Bloque,SEEK_SET);
                            fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);

                            if(strcmp(Bloque_AP.b_content,contenidocomparar)==0){
                                strcpy( Bloque_AP.b_content,contenido);
                                fseek(arch,posicion_Bloque,SEEK_SET);
                                fwrite(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                fclose(arch);
                                insertado=1;
                                break;
                            }
                        }
                    }
                    //si se inserto se sale
                    if(band==true){
                        break;
                    }

                }

            }
            //Doble Indirecto
            if(posicion==13){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //busca y inserta
                    bool band=false;
                    for(int pos=0;pos<15;pos++){
                        Bloque_Apuntador NuevoApun;
                        int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_AP.i_block[posicion]);
                        fseek(arch,pos_I,SEEK_SET);
                        fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                        if(NuevoApun.b_pointers[pos]!=-1){
                            //busca y inserta
                            Bloque_Apuntador NuevoApun2;
                            pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos]);
                            fseek(arch,pos_I,SEEK_SET);
                            fread(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);
                            for(int pos2=0;pos2<15;pos2++){
                                if(NuevoApun2.b_pointers[pos2]==-1){
                                    //Actualizamos Bloque
                                    Bloque_Archivo Bloque_AP;
                                    int posicion_Bloque=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun2.b_pointers[pos2]);
                                    fseek(arch,posicion_Bloque,SEEK_SET);
                                    fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);

                                    if(strcmp(Bloque_AP.b_content,contenidocomparar)==0){
                                        strcpy( Bloque_AP.b_content,contenido);
                                        fseek(arch,posicion_Bloque,SEEK_SET);
                                        fwrite(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                        fclose(arch);
                                        insertado=1;
                                        break;
                                    }
                                }
                            }
                            if(band==true){
                                break;
                            }
                        }
                    }
                    //si se inserto se sale
                    if(band==true){
                        break;
                    }

                }

            }


        }

        if(insertado==0){
            std::cout<<"Espacio Insuficiente en el Archivo: "<<std::endl;
        }

    }

}

std::string BloqueArchivo::Mostrar_Contenido(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar){
    std::string Contenido="";
    int posicionInicio;
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
        posicionInicio=Nodo_AP.s_inode_start;

        //empezamos los recorridos
        QString qstr = QString::fromStdString(Ruta_Buscar);
        QStringList list1 = qstr.split('/');

        int posicionLectura=posicionInicio;


        for(int posicion_Varios=0;posicion_Varios<list1.size()+1;posicion_Varios++){

            if(posicion_Varios==list1.size()){
                //insertar
                Tabla_Inodo TablaPrimero;
                fseek(arch,posicionLectura,SEEK_SET);
                fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                //mostraos el contenido dentro la tabla
                for(int pos=0;pos<15;pos++){
                    if(pos<12){
                        if(TablaPrimero.i_block[pos]!=-1){
                            Bloque_Archivo Bloque_AR;
                            int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*TablaPrimero.i_block[pos]);
                            fseek(arch,posI,SEEK_SET);
                            fread(&Bloque_AR, sizeof(Bloque_Carpeta), 1, arch);
                            std::cout<<Bloque_AR.b_content<<std::endl;
                            Contenido+=Bloque_AR.b_content;
                            Contenido+="\n";

                        }
                    }
                    if(pos==12){
                        if(TablaPrimero.i_block[pos]!=-1){
                            //busca y inserta
                            Bloque_Apuntador NuevoApun;
                            int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*TablaPrimero.i_block[pos]);
                            fseek(arch,pos_I,SEEK_SET);
                            fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                            bool band=false;
                            for(int pos2=0;pos2<15;pos2++){
                                if(NuevoApun.b_pointers[pos2]!=-1){
                                    Bloque_Archivo Bloque_AR;
                                    int posI=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos2]);
                                    fseek(arch,posI,SEEK_SET);
                                    fread(&Bloque_AR, sizeof(Bloque_Carpeta), 1, arch);
                                    std::cout<<Bloque_AR.b_content<<std::endl;
                                    Contenido+=Bloque_AR.b_content;
                                    Contenido+="\n";

                                }
                            }
                            //si se inserto se sale
                            if(band==true){
                                break;
                            }

                        }
                    }
                    if(pos==13){
                        if(TablaPrimero.i_block[pos]!=-1){
                            std::cout<<"Doble"<<std::endl;
                            for(int pos2=0;pos2<15;pos2++){
                                Bloque_Apuntador NuevoApun;
                                int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*TablaPrimero.i_block[pos]);
                                fseek(arch,pos_I,SEEK_SET);
                                fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                                if(NuevoApun.b_pointers[pos2]!=-1){
                                    //busca y inserta
                                    Bloque_Apuntador NuevoApun2;
                                    pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos2]);
                                    fseek(arch,pos_I,SEEK_SET);
                                    fread(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);
                                    for(int pos3=0;pos3<15;pos3++){
                                        if(NuevoApun2.b_pointers[pos3]!=-1){
                                            //Actualizamos Bloque
                                            Bloque_Archivo Bloque_AR;
                                            int posI2=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun2.b_pointers[pos2]);
                                            fseek(arch,posI2,SEEK_SET);
                                            fread(&Bloque_AR, sizeof(Bloque_Carpeta), 1, arch);
                                            std::cout<<Bloque_AR.b_content<<std::endl;
                                            Contenido+=Bloque_AR.b_content;
                                            Contenido+="\n";
                                        }
                                    }

                                }
                            }

                        }

                    }
                }

            }else{
                int reconocio=0;//0 no reconocio 1 si reconocio
                //iterar
                Tabla_Inodo TablaPrimero;
                fseek(arch,posicionLectura,SEEK_SET);
                fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                    //no igual carpeta y espacio libre
                    //bloques directos

                    if(posicionPrimero<12){
                        if(TablaPrimero.i_block[posicionPrimero]!=-1){
                            int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                            Bloque_Carpeta Bloque_CP;
                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                            //comproamos si la carpeta existe
                            if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                reconocio=1;
                                break;
                            }

                        }
                    }

                    //bloque simple indirecto
                    if(posicionPrimero==12){
                        if(TablaPrimero.i_block[posicionPrimero]!=-1){
                            //comprobamos las posiciones de los bloques
                            for(int Pos_1=0;Pos_1<15;Pos_1++){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Apuntador Bloque_AP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                if(Bloque_AP.b_pointers[Pos_1]!=-1){
                                    int posicion_Bloque_Name2=Nodo_AP.s_block_start+(Bloque_AP.b_pointers[Pos_1]*sizeof (Bloque_Carpeta));
                                    Bloque_Carpeta Bloque_CP;
                                    fseek(arch,posicion_Bloque_Name2,SEEK_SET);
                                    fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                    //comproamos si la carpeta existe
                                    if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                        reconocio=1;
                                        break;
                                    }
                                }
                            }
                            if(reconocio==1){
                                break;
                            }

                        }
                    }

                    //bloque doble indirecto
                    if(posicionPrimero==13){
                        if(TablaPrimero.i_block[posicionPrimero]!=-1){
                            //comprobamos las posiciones de los bloques
                            for(int Pos_1=0;Pos_1<15;Pos_1++){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Apuntador Bloque_AP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                if(Bloque_AP.b_pointers[Pos_1]!=-1){
                                    //ciclo del segundo bloque
                                    for(int Pos_2=0;Pos_2<15;Pos_2++){
                                        int posicion_Bloque_Name2=Nodo_AP.s_block_start+(Bloque_AP.b_pointers[Pos_1]*sizeof (Bloque_Carpeta));
                                        Bloque_Apuntador Bloque_AP2;
                                        fseek(arch,posicion_Bloque_Name2,SEEK_SET);
                                        fread(&Bloque_AP2, sizeof(Bloque_Carpeta), 1, arch);
                                        if(Bloque_AP2.b_pointers[Pos_2]!=-1){
                                            //buscamos
                                            int posicion_Bloque_Name3=Nodo_AP.s_block_start+(Bloque_AP2.b_pointers[Pos_2]*sizeof (Bloque_Carpeta));
                                            Bloque_Carpeta Bloque_CP;
                                            fseek(arch,posicion_Bloque_Name3,SEEK_SET);
                                            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            //comproamos si la carpeta existe
                                            if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                                reconocio=1;
                                                break;
                                            }



                                        }
                                    }

                                    if(reconocio==1){
                                        break;
                                    }
                                }
                            }

                            if(reconocio==1){
                                break;
                            }
                        }
                    }

                    //bloque triple indirecto
                    if(posicionPrimero==14){
                    }

                }
                //si no reconocio se sale de todo
                if(reconocio==0){
                    std::cout<<"la Carpeta no existe no se puede insertar: "<<list1[posicion_Varios].toStdString()<<std::endl;
                    break;
                }


            }


        }


    }

    return Contenido;
}

void BloqueArchivo::Editar_Contenido(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar, char *contenido){
    int posicionInicio;

    int insertado=0;
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,PosicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
        posicionInicio=Nodo_AP.s_inode_start;

        //empezamos los recorridos
        QString qstr = QString::fromStdString(Ruta_Buscar);
        QStringList list1 = qstr.split('/');

        int posicionLectura=posicionInicio;


        for(int posicion_Varios=0;posicion_Varios<list1.size()+1;posicion_Varios++){

            if(posicion_Varios==list1.size()){
                //insertar
                Tabla_Inodo TablaPrimero;
                fseek(arch,posicionLectura,SEEK_SET);
                fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                //mostraos el contenido dentro la tabla
                for(int pos=0;pos<15;pos++){
                    if(pos<12){
                        if(TablaPrimero.i_block[pos]!=-1){
                            Bloque_Archivo Bloque_AP;
                            int posicion_Bloque=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*TablaPrimero.i_block[pos]);
                            fseek(arch,posicion_Bloque,SEEK_SET);
                            fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);

                            strcpy( Bloque_AP.b_content,contenido);
                            fseek(arch,posicion_Bloque,SEEK_SET);
                            fwrite(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                            fclose(arch);
                            std::cout<<"Archivo: "<<Ruta_Buscar<<std::endl;
                            std::cout<<"Se ha Editado Correctamente"<<std::endl;
                            insertado=1;
                            break;


                        }
                    }
                }
                if(insertado==1){
                    break;
                }

            }else{
                int reconocio=0;//0 no reconocio 1 si reconocio
                //iterar
                Tabla_Inodo TablaPrimero;
                fseek(arch,posicionLectura,SEEK_SET);
                fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                    //no igual carpeta y espacio libre
                    //bloques directos

                    if(posicionPrimero<12){
                        if(TablaPrimero.i_block[posicionPrimero]!=-1){
                            int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                            Bloque_Carpeta Bloque_CP;
                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                            //comproamos si la carpeta existe
                            if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                reconocio=1;
                                break;
                            }

                        }
                    }

                    //bloque simple indirecto
                    if(posicionPrimero==12){
                        if(TablaPrimero.i_block[posicionPrimero]!=-1){
                            //comprobamos las posiciones de los bloques
                            for(int Pos_1=0;Pos_1<15;Pos_1++){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Apuntador Bloque_AP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                if(Bloque_AP.b_pointers[Pos_1]!=-1){
                                    int posicion_Bloque_Name2=Nodo_AP.s_block_start+(Bloque_AP.b_pointers[Pos_1]*sizeof (Bloque_Carpeta));
                                    Bloque_Carpeta Bloque_CP;
                                    fseek(arch,posicion_Bloque_Name2,SEEK_SET);
                                    fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                    //comproamos si la carpeta existe
                                    if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                        reconocio=1;
                                        break;
                                    }
                                }
                            }
                            if(reconocio==1){
                                break;
                            }

                        }
                    }

                    //bloque doble indirecto
                    if(posicionPrimero==13){
                        if(TablaPrimero.i_block[posicionPrimero]!=-1){
                            //comprobamos las posiciones de los bloques
                            for(int Pos_1=0;Pos_1<15;Pos_1++){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Apuntador Bloque_AP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
                                if(Bloque_AP.b_pointers[Pos_1]!=-1){
                                    //ciclo del segundo bloque
                                    for(int Pos_2=0;Pos_2<15;Pos_2++){
                                        int posicion_Bloque_Name2=Nodo_AP.s_block_start+(Bloque_AP.b_pointers[Pos_1]*sizeof (Bloque_Carpeta));
                                        Bloque_Apuntador Bloque_AP2;
                                        fseek(arch,posicion_Bloque_Name2,SEEK_SET);
                                        fread(&Bloque_AP2, sizeof(Bloque_Carpeta), 1, arch);
                                        if(Bloque_AP2.b_pointers[Pos_2]!=-1){
                                            //buscamos
                                            int posicion_Bloque_Name3=Nodo_AP.s_block_start+(Bloque_AP2.b_pointers[Pos_2]*sizeof (Bloque_Carpeta));
                                            Bloque_Carpeta Bloque_CP;
                                            fseek(arch,posicion_Bloque_Name3,SEEK_SET);
                                            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            //comproamos si la carpeta existe
                                            if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                                reconocio=1;
                                                break;
                                            }



                                        }
                                    }

                                    if(reconocio==1){
                                        break;
                                    }
                                }
                            }

                            if(reconocio==1){
                                break;
                            }
                        }
                    }

                    //bloque triple indirecto
                    if(posicionPrimero==14){
                    }

                }
                //si no reconocio se sale de todo
                if(reconocio==0){
                    std::cout<<"la Carpeta no existe no se puede insertar: "<<list1[posicion_Varios].toStdString()<<std::endl;
                    break;
                }


            }

        }

        if(insertado==0){
            std::cout<<"Archivo: "<<Ruta_Buscar<<std::endl;
            std::cout<<"El archivo no existe"<<std::endl;
        }
    }

}

