#include "bloquecarpeta.h"

BloqueCarpeta::BloqueCarpeta()
{

}

void BloqueCarpeta::Insertar_BloqueCarpeta(std::string rutabrir,int posicionStart,int ID,std::string Nombre_Carpeta,int Id_Inodo,std::string Nombre_Padre,int Id_Padre){
    //tipo si es 0 es Carpeta
    //1 es Archivo
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        fseek(arch,posicionStart,SEEK_SET);
        Bloque_Carpeta_Nuevo.ID=ID;
        //Actual
        strcpy(Bloque_Carpeta_Nuevo.b_name1, Nombre_Carpeta.c_str());
        Bloque_Carpeta_Nuevo.b_inodo1=Id_Inodo;
        //Padre
        strcpy(Bloque_Carpeta_Nuevo.b_name2, Nombre_Padre.c_str());
        Bloque_Carpeta_Nuevo.b_inodo2=Id_Padre;
        //otros
        strcpy(Bloque_Carpeta_Nuevo.b_name3," ");
        Bloque_Carpeta_Nuevo.b_inodo3=-1;
        strcpy(Bloque_Carpeta_Nuevo.b_name4, " ");
        Bloque_Carpeta_Nuevo.b_inodo4=-1;
        fwrite(&Bloque_Carpeta_Nuevo, sizeof(Bloque_Carpeta), 1, arch);
        fclose(arch);
    }
}

void BloqueCarpeta::Busqueda_Carpeta(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar,int ID_Usuario,int ID_Grupo){
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
                                    std::cout<<"La Carpeta Ya existe"<<std::endl;
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
                                        fclose(arch);
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);
                                        std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
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
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name2,"..",TablaPrimero.ID,ID_Usuario);
                                        std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
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
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name3,"..",TablaPrimero.ID,ID_Usuario);
                                        std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
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
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name4,"..",TablaPrimero.ID,ID_Usuario);
                                        std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                        break;
                                    }
                                }
                            }else{
                                TablaPrimero.i_block[posicionPrimero]=Nodo_AP.s_firts_blo;
                                //se crea nodo carpeta
                                int posicion_Inicial_Carpeta=Nodo_AP.s_block_start+(Nodo_AP.s_firts_blo*sizeof (Bloque_Carpeta));
                                Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carpeta,Nodo_AP.s_firts_blo,".",TablaPrimero.ID," ",-1);

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
                                //Actualizar inodo
                                TablaPrimero.i_block[posicionPrimero]=Nodo_AP.s_firts_blo;
                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);

                                //se crea nodo apuntador
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

                                //insertamos bloque Carpeta
                                Bloque_Carpeta Bloque_CP;
                                int posicion_Inicial_Carp=Nodo_AP.s_block_start+((Nodo_AP.s_firts_blo +1)*sizeof (Bloque_Carpeta));
                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                const char *c_str2 = ba.data();
                                strcpy(Bloque_CP.b_name1,c_str2);
                                fclose(arch);
                                Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carp,Nodo_AP.s_firts_blo+1,list1[posicion_Varios].toStdString(),Nodo_AP.s_firts_ino," ",-1);

                                //actualizacion de bitmap y superbloque
                                SuperBloque *nuevo_Super=new SuperBloque();
                                nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,2);

                                //creacion de inodo y su hijo
                                SuperBloque *nuevo=new SuperBloque();
                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);

                                std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                break;

                            }else{
                                //Busca y inserta
                                bool band=false;
                                for(int pos=0;pos<15;pos++){
                                    Bloque_Apuntador NuevoApun;
                                    int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*TablaPrimero.i_block[posicionPrimero]);
                                    fseek(arch,pos_I,SEEK_SET);
                                    fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                                    if(NuevoApun.b_pointers[pos]!=-1){
                                        //comprueba si hay espacio dentro del bloque carpeta
                                        for(int dentro=1;dentro<4;dentro++){
                                            //Actualizamos Bloque Carpeta
                                            Bloque_Carpeta Bloque_CP;
                                            int pos_In=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos]);
                                            fseek(arch,pos_In,SEEK_SET);
                                            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                band=true;
                                                break;
                                                std::cout<<"La Carpeta Ya existe"<<std::endl;
                                            }else{
                                                if(dentro==1){
                                                    if(Bloque_CP.b_inodo2==-1){
                                                        Bloque_CP.b_inodo2=Nodo_AP.s_firts_ino;
                                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                        const char *c_str2 = ba.data();
                                                        strcpy(Bloque_CP.b_name2,c_str2);

                                                        //Actualizaos
                                                        fseek(arch,pos_In,SEEK_SET);
                                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                        fclose(arch);
                                                        //creacion de inodo y su hijo
                                                        SuperBloque *nuevo=new SuperBloque();
                                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,list1[posicion_Varios].toStdString(),"..",TablaPrimero.ID,ID_Usuario);

                                                        band=true;
                                                        break;
                                                    }
                                                }
                                                if(dentro==2){
                                                    if(Bloque_CP.b_inodo3==-1){
                                                        Bloque_CP.b_inodo3=Nodo_AP.s_firts_ino;
                                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                        const char *c_str2 = ba.data();
                                                        strcpy(Bloque_CP.b_name3,c_str2);

                                                        //Actualizaos
                                                        fseek(arch,pos_In,SEEK_SET);
                                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                        fclose(arch);
                                                        //creacion de inodo y su hijo
                                                        SuperBloque *nuevo=new SuperBloque();
                                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,list1[posicion_Varios].toStdString(),"..",TablaPrimero.ID,ID_Usuario);

                                                        band=true;
                                                        break;
                                                    }
                                                }
                                                if(dentro==3){
                                                    if(Bloque_CP.b_inodo4==-1){
                                                        Bloque_CP.b_inodo4=Nodo_AP.s_firts_ino;
                                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                        const char *c_str2 = ba.data();
                                                        strcpy(Bloque_CP.b_name4,c_str2);
                                                        //Actualizaos
                                                        fseek(arch,pos_In,SEEK_SET);
                                                        fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);

                                                        fclose(arch);
                                                        //creacion de inodo y su hijo
                                                        SuperBloque *nuevo=new SuperBloque();
                                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,list1[posicion_Varios].toStdString(),"..",TablaPrimero.ID,ID_Usuario);

                                                        band=true;
                                                        break;
                                                    }
                                                }
                                            }


                                        }
                                    }else{
                                        std::cout<<"Llego aqui"<<std::endl;
                                        //Actualizamos Bloque
                                        NuevoApun.b_pointers[pos]=Nodo_AP.s_firts_blo;
                                        fseek(arch,pos_I,SEEK_SET);
                                        fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                                        //insertamos bloque Carpeta
                                        Bloque_Carpeta Bloque_CP;
                                        int posicion_Inicial_Carp=Nodo_AP.s_block_start+((Nodo_AP.s_firts_blo)*sizeof (Bloque_Carpeta));
                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                        const char *c_str2 = ba.data();
                                        strcpy(Bloque_CP.b_name1,c_str2);

                                        Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carp,Nodo_AP.s_firts_blo,list1[posicion_Varios].toStdString(),Nodo_AP.s_firts_ino," ",-1);

                                        //actualizacion de bitmap y superbloque
                                        SuperBloque *nuevo_Super=new SuperBloque();
                                        nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,1);

                                        //creacion de inodo y su hijo
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);
                                        fclose(arch);
                                        band=true;
                                        break;
                                    }

                                    //si se inserto se sale
                                    if(band==true){
                                        break;
                                    }
                                }

                                //si se inserto se sale
                                if(band==true){
                                    break;
                                }


                            }
                        }

                        //bloque doble indirecto
                        if(posicionPrimero==13){
                            if(TablaPrimero.i_block[posicionPrimero]==-1){
                                //Actualizar inodo
                                TablaPrimero.i_block[posicionPrimero]=Nodo_AP.s_firts_blo;
                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);

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

                                //insertamos bloque Carpeta
                                Bloque_Carpeta Bloque_CP;
                                int posicion_Inicial_Carp=Nodo_AP.s_block_start+((Nodo_AP.s_firts_blo +2)*sizeof (Bloque_Carpeta));
                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                const char *c_str2 = ba.data();
                                strcpy(Bloque_CP.b_name1,c_str2);
                                fclose(arch);
                                Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carp,Nodo_AP.s_firts_blo+2,list1[posicion_Varios].toStdString(),Nodo_AP.s_firts_ino," ",-1);

                                //actualizacion de bitmap y superbloque
                                SuperBloque *nuevo_Super=new SuperBloque();
                                nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,3);

                                //creacion de inodo y su hijo
                                SuperBloque *nuevo=new SuperBloque();
                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);

                                std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                break;

                            }else{
                                //busca y inserta
                                bool band=false;
                                for(int pos=0;pos<15;pos++){
                                    Bloque_Apuntador NuevoApun;
                                    int pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*TablaPrimero.i_block[posicionPrimero]);
                                    fseek(arch,pos_I,SEEK_SET);
                                    fread(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);

                                    if(NuevoApun.b_pointers[pos]!=-1){
                                        //busca y inserta

                                        for(int pos2=0;pos2<15;pos2++){
                                            Bloque_Apuntador NuevoApun2;
                                            pos_I=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun.b_pointers[pos]);
                                            fseek(arch,pos_I,SEEK_SET);
                                            fread(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);
                                            if(NuevoApun2.b_pointers[pos2]!=-1){
                                                //comprueba si hay espacio dentro del bloque carpeta
                                                for(int dentro=1;dentro<4;dentro++){
                                                    //Actualizamos Bloque Carpeta
                                                    Bloque_Carpeta Bloque_CP;
                                                    int pos_In=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*NuevoApun2.b_pointers[pos2]);
                                                    fseek(arch,pos_In,SEEK_SET);
                                                    fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);

                                                    if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3) || list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                        band=true;
                                                        break;
                                                        std::cout<<"La Carpeta Ya existe"<<std::endl;
                                                    }else{
                                                        if(dentro==1){
                                                            if(Bloque_CP.b_inodo2==-1){
                                                                Bloque_CP.b_inodo2=Nodo_AP.s_firts_ino;
                                                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                                const char *c_str2 = ba.data();
                                                                strcpy(Bloque_CP.b_name2,c_str2);

                                                                //Actualizaos
                                                                fseek(arch,pos_In,SEEK_SET);
                                                                fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                                fclose(arch);
                                                                //creacion de inodo y su hijo
                                                                SuperBloque *nuevo=new SuperBloque();
                                                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,list1[posicion_Varios].toStdString(),"..",TablaPrimero.ID,ID_Usuario);

                                                                band=true;
                                                                break;
                                                            }
                                                        }
                                                        if(dentro==2){
                                                            if(Bloque_CP.b_inodo3==-1){
                                                                Bloque_CP.b_inodo3=Nodo_AP.s_firts_ino;
                                                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                                const char *c_str2 = ba.data();
                                                                strcpy(Bloque_CP.b_name3,c_str2);

                                                                //Actualizaos
                                                                fseek(arch,pos_In,SEEK_SET);
                                                                fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                                fclose(arch);
                                                                //creacion de inodo y su hijo
                                                                SuperBloque *nuevo=new SuperBloque();
                                                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,list1[posicion_Varios].toStdString(),"..",TablaPrimero.ID,ID_Usuario);

                                                                band=true;
                                                                break;
                                                            }
                                                        }
                                                        if(dentro==3){
                                                            if(Bloque_CP.b_inodo4==-1){
                                                                Bloque_CP.b_inodo4=Nodo_AP.s_firts_ino;
                                                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                                const char *c_str2 = ba.data();
                                                                strcpy(Bloque_CP.b_name4,c_str2);
                                                                //Actualizaos
                                                                fseek(arch,pos_In,SEEK_SET);
                                                                fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);

                                                                fclose(arch);
                                                                //creacion de inodo y su hijo
                                                                SuperBloque *nuevo=new SuperBloque();
                                                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,list1[posicion_Varios].toStdString(),"..",TablaPrimero.ID,ID_Usuario);

                                                                band=true;
                                                                break;
                                                            }
                                                        }
                                                    }


                                                }
                                            }else{
                                                //Actualizamos Bloque
                                                NuevoApun2.b_pointers[pos2]=Nodo_AP.s_firts_blo;
                                                fseek(arch,pos_I,SEEK_SET);
                                                fwrite(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);

                                                //insertamos bloque Carpeta
                                                Bloque_Carpeta Bloque_CP;
                                                int posicion_Inicial_Carp=Nodo_AP.s_block_start+((Nodo_AP.s_firts_blo)*sizeof (Bloque_Carpeta));
                                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                                const char *c_str2 = ba.data();
                                                strcpy(Bloque_CP.b_name1,c_str2);

                                                Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carp,Nodo_AP.s_firts_blo,list1[posicion_Varios].toStdString(),Nodo_AP.s_firts_ino," ",-1);

                                                //actualizacion de bitmap y superbloque
                                                SuperBloque *nuevo_Super=new SuperBloque();
                                                nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,1);

                                                //creacion de inodo y su hijo
                                                SuperBloque *nuevo=new SuperBloque();
                                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);
                                                fclose(arch);
                                                band=true;
                                                break;
                                            }

                                            //si se inserto se sale
                                            if(band==true){
                                                break;
                                            }
                                        }
                                        if(band==true){
                                            break;
                                        }
                                    }else{
                                        //crea y inserta
                                        NuevoApun.b_pointers[pos]=Nodo_AP.s_firts_blo;
                                        fseek(arch,pos_I,SEEK_SET);
                                        fwrite(&NuevoApun, sizeof(Bloque_Carpeta), 1, arch);
                                        //creamos nodo puntero
                                        Bloque_Apuntador NuevoApun2;
                                        NuevoApun2.ID=Nodo_AP.s_firts_blo;
                                        for(int pos2=0;pos2<15;pos2++){
                                            NuevoApun2.b_pointers[pos2]=-1;
                                        }
                                        NuevoApun2.b_pointers[0]=Nodo_AP.s_firts_blo+1;
                                        //Insertamos bloque apuntadores
                                        int posI5=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Nodo_AP.s_firts_blo);
                                        fseek(arch,posI5,SEEK_SET);
                                        fwrite(&NuevoApun2, sizeof(Bloque_Carpeta), 1, arch);

                                        fclose(arch);
                                        //insertamos bloque Carpeta
                                        Bloque_Carpeta Bloque_CP;
                                        int posicion_Inicial_Carp=Nodo_AP.s_block_start+((Nodo_AP.s_firts_blo+1)*sizeof (Bloque_Carpeta));
                                        QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                        const char *c_str2 = ba.data();
                                        strcpy(Bloque_CP.b_name1,c_str2);

                                        Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carp,Nodo_AP.s_firts_blo+1,list1[posicion_Varios].toStdString(),Nodo_AP.s_firts_ino," ",-1);

                                        //actualizacion de bitmap y superbloque
                                        SuperBloque *nuevo_Super=new SuperBloque();
                                        nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,2);

                                        //creacion de inodo y su hijo
                                        SuperBloque *nuevo=new SuperBloque();
                                        nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);

                                        std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;

                                        band=true;
                                        break;
                                    }
                                }
                                //si se inserto se sale
                                if(band==true){
                                    break;
                                }


                            }
                        }

                        //bloque triple indirecto
                        if(posicionPrimero==14){
                            if(TablaPrimero.i_block[posicionPrimero]==-1){
                                //Actualizar inodo
                                TablaPrimero.i_block[posicionPrimero]=Nodo_AP.s_firts_blo;
                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);

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

                                //insertamos bloque Carpeta
                                Bloque_Carpeta Bloque_CP;
                                int posicion_Inicial_Carp=Nodo_AP.s_block_start+((Nodo_AP.s_firts_blo +3)*sizeof (Bloque_Carpeta));
                                QByteArray ba = list1[posicion_Varios].toLocal8Bit();
                                const char *c_str2 = ba.data();
                                strcpy(Bloque_CP.b_name1,c_str2);
                                fclose(arch);
                                Insertar_BloqueCarpeta(rutabrir,posicion_Inicial_Carp,Nodo_AP.s_firts_blo+3,list1[posicion_Varios].toStdString(),Nodo_AP.s_firts_ino," ",-1);

                                //actualizacion de bitmap y superbloque
                                SuperBloque *nuevo_Super=new SuperBloque();
                                nuevo_Super->Actualizar_Cantidades(rutabrir,PosicionStart,0,4);

                                //creacion de inodo y su hijo
                                SuperBloque *nuevo=new SuperBloque();
                                nuevo->Crear_Carpeta(rutabrir,PosicionStart,Bloque_CP.b_name1,"..",TablaPrimero.ID,ID_Usuario);

                                std::cout<<"Se ha Creado la Carpeta Correctamente: "<<list1[posicion_Varios].toStdString()<<std::endl;
                                break;

                            }
                        }
                    }

                }else{
                    int reconocio=0;//0 no reconocio 1 si reconocio
                    //iterar
                    Tabla_Inodo TablaPrimero;
                    fseek(arch,posicionLectura,SEEK_SET);
                    fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                    //if para buscar solo en carpetas
                    if(TablaPrimero.i_type==0){
                        for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                            //bloques directos
                            if(posicionPrimero<12){
                                if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                    int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                    Bloque_Carpeta Bloque_CP;
                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                    fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                    //comproamos si la carpeta existe
                                    if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                        //actualizo size
                                        TablaPrimero.i_size+=64;
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                        //actualizo size
                                        TablaPrimero.i_size+=64;
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                        //actualizo size
                                        TablaPrimero.i_size+=64;
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicino
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                        //actualizo size
                                        TablaPrimero.i_size+=64;
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
                                                //actualizo size
                                                TablaPrimero.i_size+=64;
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                //actualizo size
                                                TablaPrimero.i_size+=64;
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                //actualizo size
                                                TablaPrimero.i_size+=64;
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                //actualizo size
                                                TablaPrimero.i_size+=64;
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
                                                        //actualizo size
                                                        TablaPrimero.i_size+=64;
                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                        //actualizo size
                                                        TablaPrimero.i_size+=64;
                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                        //actualizo size
                                                        TablaPrimero.i_size+=64;
                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                        //actualizo size
                                                        TablaPrimero.i_size+=64;
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

void BloqueCarpeta::Renombrar(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar, char *nombre){
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
                                if(nombre==QLatin1String(Bloque_CP.b_name1) || nombre==QLatin1String(Bloque_CP.b_name2) || nombre==QLatin1String(Bloque_CP.b_name3) || nombre==QLatin1String(Bloque_CP.b_name4)){
                                    break;
                                    std::cout<<"La Carpeta Ya existe"<<std::endl;
                                }else{
                                    //comprobamos i hay espacio en este bloque
                                    if(Bloque_CP.b_inodo1!=-1){
                                        //inserta
                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                            strcpy(Bloque_CP.b_name1,nombre);
                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            //comprobamos si el inodo es carpeta o archivo
                                            Tabla_Inodo Tabla_Comprobacion;
                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                            fseek(arch,posic,SEEK_SET);
                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                            if(Tabla_Comprobacion.i_type==0){
                                                Bloque_Carpeta camabio;
                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                strcpy(camabio.b_name1,nombre);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                            }
                                            fclose(arch);
                                            std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                            insertado=1;
                                            break;
                                        }

                                    }
                                    if(Bloque_CP.b_inodo2!=-1){
                                        //inserta
                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                            strcpy(Bloque_CP.b_name2,nombre);
                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            //comprobamos si el inodo es carpeta o archivo
                                            Tabla_Inodo Tabla_Comprobacion;
                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                            fseek(arch,posic,SEEK_SET);
                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                            if(Tabla_Comprobacion.i_type==0){
                                                Bloque_Carpeta camabio;
                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                strcpy(camabio.b_name1,nombre);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                            }
                                            fclose(arch);
                                            std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                            insertado=1;
                                            break;
                                        }

                                    }
                                    if(Bloque_CP.b_inodo3!=-1){
                                        //inserta
                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                            strcpy(Bloque_CP.b_name3,nombre);
                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            //comprobamos si el inodo es carpeta o archivo
                                            Tabla_Inodo Tabla_Comprobacion;
                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                            fseek(arch,posic,SEEK_SET);
                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                            if(Tabla_Comprobacion.i_type==0){
                                                Bloque_Carpeta camabio;
                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                strcpy(camabio.b_name1,nombre);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                            }
                                            fclose(arch);
                                            std::cout<<"Se ha cambiado Nombre Correctamente: "<<nombre<<std::endl;
                                            insertado=1;
                                            break;
                                        }
                                    }
                                    if(Bloque_CP.b_inodo4!=-1){
                                        //inserta
                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                            strcpy(Bloque_CP.b_name4,nombre);
                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                            //comprobamos si el inodo es carpeta o archivo
                                            Tabla_Inodo Tabla_Comprobacion;
                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                            fseek(arch,posic,SEEK_SET);
                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                            if(Tabla_Comprobacion.i_type==0){
                                                Bloque_Carpeta camabio;
                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                strcpy(camabio.b_name1,nombre);
                                                fseek(arch,poscambio,SEEK_SET);
                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                            }
                                            fclose(arch);
                                            std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                            insertado=1;
                                            break;
                                        }

                                    }
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
                                        if(nombre==QLatin1String(Bloque_CP.b_name1) || nombre==QLatin1String(Bloque_CP.b_name2) || nombre==QLatin1String(Bloque_CP.b_name3) || nombre==QLatin1String(Bloque_CP.b_name4)){
                                            break;
                                            std::cout<<"La Carpeta Ya existe"<<std::endl;
                                        }else{
                                            //comprobamos i hay espacio en este bloque
                                            if(Bloque_CP.b_inodo1!=-1){
                                                //inserta
                                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                                    strcpy(Bloque_CP.b_name1,nombre);
                                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                    fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                    //comprobamos si el inodo es carpeta o archivo
                                                    Tabla_Inodo Tabla_Comprobacion;
                                                    int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                    fseek(arch,posic,SEEK_SET);
                                                    fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                    if(Tabla_Comprobacion.i_type==0){
                                                        Bloque_Carpeta camabio;
                                                        int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                        strcpy(camabio.b_name1,nombre);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                    }
                                                    fclose(arch);
                                                    std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                                    insertado=1;
                                                    break;
                                                }

                                            }
                                            if(Bloque_CP.b_inodo2!=-1){
                                                //inserta
                                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                    strcpy(Bloque_CP.b_name2,nombre);
                                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                    fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                    //comprobamos si el inodo es carpeta o archivo
                                                    Tabla_Inodo Tabla_Comprobacion;
                                                    int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                    fseek(arch,posic,SEEK_SET);
                                                    fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                    if(Tabla_Comprobacion.i_type==0){
                                                        Bloque_Carpeta camabio;
                                                        int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                        strcpy(camabio.b_name1,nombre);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                    }
                                                    fclose(arch);
                                                    std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                                    insertado=1;
                                                    break;
                                                }

                                            }
                                            if(Bloque_CP.b_inodo3!=-1){
                                                //inserta
                                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                    strcpy(Bloque_CP.b_name3,nombre);
                                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                    fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                    //comprobamos si el inodo es carpeta o archivo
                                                    Tabla_Inodo Tabla_Comprobacion;
                                                    int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                    fseek(arch,posic,SEEK_SET);
                                                    fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                    if(Tabla_Comprobacion.i_type==0){
                                                        Bloque_Carpeta camabio;
                                                        int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                        strcpy(camabio.b_name1,nombre);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                    }
                                                    fclose(arch);
                                                    std::cout<<"Se ha cambiado Nombre Correctamente: "<<nombre<<std::endl;
                                                    insertado=1;
                                                    break;
                                                }
                                            }
                                            if(Bloque_CP.b_inodo4!=-1){
                                                //inserta
                                                if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                    strcpy(Bloque_CP.b_name4,nombre);
                                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                    fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                    //comprobamos si el inodo es carpeta o archivo
                                                    Tabla_Inodo Tabla_Comprobacion;
                                                    int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                                    fseek(arch,posic,SEEK_SET);
                                                    fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                    if(Tabla_Comprobacion.i_type==0){
                                                        Bloque_Carpeta camabio;
                                                        int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                        strcpy(camabio.b_name1,nombre);
                                                        fseek(arch,poscambio,SEEK_SET);
                                                        fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                    }
                                                    fclose(arch);
                                                    std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                                    insertado=1;
                                                    break;
                                                }

                                            }
                                        }
                                    }
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
                                                if(nombre==QLatin1String(Bloque_CP.b_name1) || nombre==QLatin1String(Bloque_CP.b_name2) || nombre==QLatin1String(Bloque_CP.b_name3) || nombre==QLatin1String(Bloque_CP.b_name4)){
                                                    break;
                                                    std::cout<<"La Carpeta Ya existe"<<std::endl;
                                                }else{
                                                    //comprobamos i hay espacio en este bloque
                                                    if(Bloque_CP.b_inodo1!=-1){
                                                        //inserta
                                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                                            strcpy(Bloque_CP.b_name1,nombre);
                                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                            //comprobamos si el inodo es carpeta o archivo
                                                            Tabla_Inodo Tabla_Comprobacion;
                                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                            fseek(arch,posic,SEEK_SET);
                                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                            if(Tabla_Comprobacion.i_type==0){
                                                                Bloque_Carpeta camabio;
                                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                                strcpy(camabio.b_name1,nombre);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                            }
                                                            fclose(arch);
                                                            std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                                            insertado=1;
                                                            break;
                                                        }

                                                    }
                                                    if(Bloque_CP.b_inodo2!=-1){
                                                        //inserta
                                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                            strcpy(Bloque_CP.b_name2,nombre);
                                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                            //comprobamos si el inodo es carpeta o archivo
                                                            Tabla_Inodo Tabla_Comprobacion;
                                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                            fseek(arch,posic,SEEK_SET);
                                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                            if(Tabla_Comprobacion.i_type==0){
                                                                Bloque_Carpeta camabio;
                                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                                strcpy(camabio.b_name1,nombre);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                            }
                                                            fclose(arch);
                                                            std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                                            insertado=1;
                                                            break;
                                                        }

                                                    }
                                                    if(Bloque_CP.b_inodo3!=-1){
                                                        //inserta
                                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                            strcpy(Bloque_CP.b_name3,nombre);
                                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                            //comprobamos si el inodo es carpeta o archivo
                                                            Tabla_Inodo Tabla_Comprobacion;
                                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                            fseek(arch,posic,SEEK_SET);
                                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                            if(Tabla_Comprobacion.i_type==0){
                                                                Bloque_Carpeta camabio;
                                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                                strcpy(camabio.b_name1,nombre);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                            }
                                                            fclose(arch);
                                                            std::cout<<"Se ha cambiado Nombre Correctamente: "<<nombre<<std::endl;
                                                            insertado=1;
                                                            break;
                                                        }
                                                    }
                                                    if(Bloque_CP.b_inodo4!=-1){
                                                        //inserta
                                                        if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                            strcpy(Bloque_CP.b_name4,nombre);
                                                            fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                                            fwrite(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                                            //comprobamos si el inodo es carpeta o archivo
                                                            Tabla_Inodo Tabla_Comprobacion;
                                                            int posic=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo4);
                                                            fseek(arch,posic,SEEK_SET);
                                                            fread(&Tabla_Comprobacion, sizeof(Tabla_Inodo), 1, arch);
                                                            if(Tabla_Comprobacion.i_type==0){
                                                                Bloque_Carpeta camabio;
                                                                int poscambio=Nodo_AP.s_block_start+(sizeof (Bloque_Carpeta)*Tabla_Comprobacion.i_block[0]);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fread(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                                strcpy(camabio.b_name1,nombre);
                                                                fseek(arch,poscambio,SEEK_SET);
                                                                fwrite(&camabio, sizeof(Bloque_Carpeta), 1, arch);
                                                            }
                                                            fclose(arch);
                                                            std::cout<<"Se ha cambiado Nombre Correctamente"<<nombre<<std::endl;
                                                            insertado=1;
                                                            break;
                                                        }

                                                    }
                                                }
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
                    //if para buscar solo en carpetas
                    if(TablaPrimero.i_type==0){
                        for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                            //bloques directos
                            if(posicionPrimero<12){
                                if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                    int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                    Bloque_Carpeta Bloque_CP;
                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                    fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                    //comproamos si la carpeta existe
                                    if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                        //actualizo size
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                        //actualizo size
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                        //actualizo size
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicino
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                        //actualizo size
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
                                                //actualizo size
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                //actualizo size
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                //actualizo size

                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                //actualizo size

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
                                                        //actualizo size

                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                        //actualizo size

                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                        //actualizo size

                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                        //actualizo size

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

void BloqueCarpeta::Copiar_Contenido(std::string rutabrir, int PosicionStart, std::string Ruta_Buscar, std::string ruta_copiar,int ID_Usuario){
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
                            if(TablaPrimero.i_block[posicionPrimero]!=-1 && TablaPrimero.i_type==0){
                                int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                Bloque_Carpeta Bloque_CP;
                                fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                //comproamos si la carpeta existe
                                //creamos relaciones
                                if(strcmp(Bloque_CP.b_name2,"..")!=0){
                                    //comprobamos las primeras dos posiciones
                                    if(Bloque_CP.b_inodo1!=-1 && strcmp(Bloque_CP.b_name1,".")!=0){
                                        int posicion_inicio=Nodo_AP.s_inode_start+(Bloque_CP.b_inodo1*sizeof (Tabla_Inodo));
                                        Tabla_Inodo prueba;
                                        fseek(arch,posicion_inicio,SEEK_SET);
                                        fread(&prueba, sizeof(Tabla_Inodo), 1, arch);
                                        if(prueba.i_type==0){
                                            //creamos carpeta
                                            Busqueda_Carpeta(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario,2);
                                        }else{
                                            //Creo archivo
                                            BloqueArchivo *BA=new BloqueArchivo();
                                            BA->Busqueda_Archivo(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),20,"",ID_Usuario);
                                        }
                                        Copiar_Contenido(rutabrir,PosicionStart,Ruta_Buscar+"/"+Bloque_CP.b_name1,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario);
                                    }
                                    if(Bloque_CP.b_inodo2!=-1){
                                        int posicion_inicio=Nodo_AP.s_inode_start+(Bloque_CP.b_inodo2*sizeof (Tabla_Inodo));
                                        Tabla_Inodo prueba;
                                        fseek(arch,posicion_inicio,SEEK_SET);
                                        fread(&prueba, sizeof(Tabla_Inodo), 1, arch);
                                        if(prueba.i_type==0){
                                            //creamos carpeta
                                            Busqueda_Carpeta(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario,2);
                                        }else{
                                            //Creo archivo
                                            BloqueArchivo *BA=new BloqueArchivo();
                                            BA->Busqueda_Archivo(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),20,"",ID_Usuario);
                                        }
                                        Copiar_Contenido(rutabrir,PosicionStart,Ruta_Buscar+"/"+Bloque_CP.b_name2,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario);
                                    }
                                }
                                if(Bloque_CP.b_inodo3!=-1){
                                    int posicion_inicio=Nodo_AP.s_inode_start+(Bloque_CP.b_inodo3*sizeof (Tabla_Inodo));
                                    Tabla_Inodo prueba;
                                    fseek(arch,posicion_inicio,SEEK_SET);
                                    fread(&prueba, sizeof(Tabla_Inodo), 1, arch);
                                    if(prueba.i_type==0){
                                        //creamos carpeta
                                        Busqueda_Carpeta(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario,2);
                                    }else{
                                        //Creo archivo
                                        BloqueArchivo *BA=new BloqueArchivo();
                                        BA->Busqueda_Archivo(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),20,"",ID_Usuario);
                                    }
                                    Copiar_Contenido(rutabrir,PosicionStart,Ruta_Buscar+"/"+Bloque_CP.b_name3,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario);
                                }
                                if(Bloque_CP.b_inodo4!=-1){
                                    int posicion_inicio=Nodo_AP.s_inode_start+(Bloque_CP.b_inodo4*sizeof (Tabla_Inodo));
                                    Tabla_Inodo prueba;
                                    fseek(arch,posicion_inicio,SEEK_SET);
                                    fread(&prueba, sizeof(Tabla_Inodo), 1, arch);
                                    if(prueba.i_type==0){
                                        //creamos carpeta
                                        Busqueda_Carpeta(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario,2);
                                    }else{
                                        //Creo archivo
                                        BloqueArchivo *BA=new BloqueArchivo();
                                        BA->Busqueda_Archivo(rutabrir,PosicionStart,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),20,"",ID_Usuario);

                                    }
                                    Copiar_Contenido(rutabrir,PosicionStart,Ruta_Buscar+"/"+Bloque_CP.b_name4,ruta_copiar+"/"+list1[posicion_Varios].toStdString(),ID_Usuario);
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
                    //if para buscar solo en carpetas
                    if(TablaPrimero.i_type==0){
                        for(int posicionPrimero=0;posicionPrimero<15;posicionPrimero++){
                            //bloques directos
                            if(posicionPrimero<12){
                                if(TablaPrimero.i_block[posicionPrimero]!=-1){
                                    int posicion_Bloque_Name=Nodo_AP.s_block_start+(TablaPrimero.i_block[posicionPrimero]*sizeof (Bloque_Carpeta));
                                    Bloque_Carpeta Bloque_CP;
                                    fseek(arch,posicion_Bloque_Name,SEEK_SET);
                                    fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                                    //comproamos si la carpeta existe
                                    if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name1)){
                                        //actualizo size
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                        //actualizo size
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                        //actualizo size
                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicino
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                        //actualizo size
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
                                                //actualizo size
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                //actualizo size
                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                //actualizo size

                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                //actualizo size

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
                                                        //actualizo size

                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){
                                                        //actualizo size

                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){
                                                        //actualizo size

                                                        fseek(arch,posicionLectura,SEEK_SET);
                                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                        //cambio de posicion
                                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                        reconocio=1;
                                                        break;
                                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){
                                                        //actualizo size

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
