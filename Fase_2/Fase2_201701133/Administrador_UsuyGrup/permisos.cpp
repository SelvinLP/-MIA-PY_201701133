#include "permisos.h"

Permisos::Permisos()
{

}

void Permisos::Cambio_Permisos(std::string rutabrir, int posicionStart,std::string ruta, int ID_Log, int Ugo){
    int posicionInicio;

    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,posicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
        posicionInicio=Nodo_AP.s_inode_start;

        //empezamos los recorridos
        QString qstr = QString::fromStdString(ruta);
        QStringList list1 = qstr.split('/');

        //mas de uno entonces debe realizar una busqueda para insertar
        int posicionLectura=posicionInicio;


        for(int posicion_Varios=0;posicion_Varios<list1.size()+1;posicion_Varios++){

            if(posicion_Varios==list1.size()){
                //Cambio de permisos
                Tabla_Inodo TablaPrimero;
                fseek(arch,posicionLectura,SEEK_SET);
                fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                if(ID_Log==TablaPrimero.i_uid || TablaPrimero.i_uid==1){
                    TablaPrimero.i_perm=Ugo;
                    std::cout<<"El Cambio de Permisos se ha hecho Correctamente"<<std::endl;
                }
                fseek(arch,posicionLectura,SEEK_SET);
                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                fclose(arch);
                break;
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


                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){


                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){


                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){


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


                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){


                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){


                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){


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


                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){


                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){


                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){


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

void Permisos::Cambio_Propetario(std::string rutabrir, int posicionStart, std::string ruta, int ID_Log, int Id_Nueva){
    int posicionInicio;

    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
    }else{
        Super_Bloque Nodo_AP;
        fseek(arch,posicionStart,SEEK_SET);
        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
        posicionInicio=Nodo_AP.s_inode_start;

        //empezamos los recorridos
        QString qstr = QString::fromStdString(ruta);
        QStringList list1 = qstr.split('/');

        //mas de uno entonces debe realizar una busqueda para insertar
        int posicionLectura=posicionInicio;


        for(int posicion_Varios=0;posicion_Varios<list1.size();posicion_Varios++){

            if(posicion_Varios+1==list1.size()){
                //Cambio de permisos
                Tabla_Inodo TablaPrimero;
                fseek(arch,posicionLectura,SEEK_SET);
                fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                if(ID_Log==TablaPrimero.i_uid || TablaPrimero.i_uid==1){
                    TablaPrimero.i_uid=Id_Nueva;
                    std::cout<<"El Cambio de Usuario se ha hecho Correctamente"<<std::endl;
                }
                fseek(arch,posicionLectura,SEEK_SET);
                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                fclose(arch);
                break;

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


                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){


                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){


                                fseek(arch,posicionLectura,SEEK_SET);
                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                //cambio de posicion
                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                reconocio=1;
                                break;
                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){


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


                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){


                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){


                                        fseek(arch,posicionLectura,SEEK_SET);
                                        fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                        //cambio de posicion
                                        posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                        reconocio=1;
                                        break;
                                    }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){


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


                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo1);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name2)){


                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo2);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name3)){


                                                fseek(arch,posicionLectura,SEEK_SET);
                                                fwrite(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                                                //cambio de posicion
                                                posicionLectura=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo)*Bloque_CP.b_inodo3);
                                                reconocio=1;
                                                break;
                                            }else if(list1[posicion_Varios]==QLatin1String(Bloque_CP.b_name4)){


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
