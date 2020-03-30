#include "graficar_reportes.h"

Graficar_Reportes::Graficar_Reportes()
{

}

void Graficar_Reportes::Graficar_Mbr(std::string rutaarir,std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutaarir=it3->Ruta;
            busc=true;
            break;
        }
    }

    if(busc==true){
        FILE *arch;
        arch=fopen(rutaarir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            MBR_Disco Nodo_AP;
            fread(&Nodo_AP, sizeof(MBR_Disco), 1, arch);
            std::string CadenaImprimir;

            CadenaImprimir="digraph D { \n";
            CadenaImprimir+="node [shape=plaintext] \n";
            CadenaImprimir+="some_node [ \n";
            CadenaImprimir+="label=< \n";
            CadenaImprimir+="<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
            //agregar columnas
            CadenaImprimir+="<tr><td> "+rutaarir+" </td></tr> \n";
            CadenaImprimir+="<tr><td> NOMBRE </td><td> VALOR </td></tr> \n";
            //campos
            CadenaImprimir+="<tr><td> mbr_tamanio </td><td> "+std::to_string(Nodo_AP.mbr_tamanio)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> mbr_fecha_creacion </td><td> ";
            CadenaImprimir.append(Nodo_AP.mbr_fecha_creacion);
            CadenaImprimir+=" </td></tr> \n";
            CadenaImprimir+="<tr><td> mbr_disk_asignature </td><td> "+std::to_string(Nodo_AP.mbr_disk_asignature)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> mbr_fit </td><td> ";
            CadenaImprimir.append(Nodo_AP.fisk_fit);
            CadenaImprimir+=" </td></tr> \n";
            //para particiones
            if(strcmp(Nodo_AP.mbr_partition_1.part_status,"S")== 0){
                CadenaImprimir+="<tr><td> mbr_partition_1";
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> NOMBRE </td><td> VALOR </td></tr> \n";
                //campos
                CadenaImprimir+="<tr><td> part_status </td><td> Activo </td></tr> \n";
                CadenaImprimir+="<tr><td> part_type </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_1.part_type);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_fit </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_1.part_fit);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_start </td><td> "+std::to_string(Nodo_AP.mbr_partition_1.part_start)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_size </td><td> "+std::to_string(Nodo_AP.mbr_partition_1.part_size)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_name </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_1.part_name);
                CadenaImprimir+=" </td></tr> \n";
            }
            if(strcmp(Nodo_AP.mbr_partition_2.part_status,"S")== 0){
                CadenaImprimir+="<tr><td> mbr_partition_2";
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> NOMBRE </td><td> VALOR </td></tr> \n";
                //campos
                CadenaImprimir+="<tr><td> part_status </td><td> Activo </td></tr> \n";
                CadenaImprimir+="<tr><td> part_type </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_2.part_type);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_fit </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_2.part_fit);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_start </td><td> "+std::to_string(Nodo_AP.mbr_partition_2.part_start)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_size </td><td> "+std::to_string(Nodo_AP.mbr_partition_2.part_size)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_name </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_2.part_name);
                CadenaImprimir+=" </td></tr> \n";
            }
            if(strcmp(Nodo_AP.mbr_partition_3.part_status,"S")== 0){
                CadenaImprimir+="<tr><td> mbr_partition_3";
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> NOMBRE </td><td> VALOR </td></tr> \n";
                //campos
                CadenaImprimir+="<tr><td> part_status </td><td> Activo </td></tr> \n";
                CadenaImprimir+="<tr><td> part_type </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_3.part_type);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_fit </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_3.part_fit);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_start </td><td> "+std::to_string(Nodo_AP.mbr_partition_3.part_start)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_size </td><td> "+std::to_string(Nodo_AP.mbr_partition_3.part_size)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_name </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_3.part_name);
                CadenaImprimir+=" </td></tr> \n";
            }
            if(strcmp(Nodo_AP.mbr_partition_4.part_status,"S")== 0){
                CadenaImprimir+="<tr><td> mbr_partition_4";
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> NOMBRE </td><td> VALOR </td></tr> \n";
                //campos
                CadenaImprimir+="<tr><td> part_status </td><td> Activo </td></tr> \n";
                CadenaImprimir+="<tr><td> part_type </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_4.part_type);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_fit </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_4.part_fit);
                CadenaImprimir+=" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_start </td><td> "+std::to_string(Nodo_AP.mbr_partition_4.part_start)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_size </td><td> "+std::to_string(Nodo_AP.mbr_partition_4.part_size)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> part_name </td><td> ";
                CadenaImprimir.append(Nodo_AP.mbr_partition_4.part_name);
                CadenaImprimir+=" </td></tr> \n";
            }
            CadenaImprimir+="</table>>]; \n";

            CadenaImprimir+="}";
            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+id+".dot";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
            std::cout <<"Reporte: "<<rutaparadot<<std::endl;
            char Comandogenerar[100];
            strcpy(Comandogenerar,comando.c_str());
            system(Comandogenerar);
        }
        fclose(arch);
    }else{
        std::cout << "ID NO MONTADO"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_Disk(std::string rutaarir,std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutaarir=it3->Ruta;
            busc=true;
            break;
        }
    }

    if(busc==true){
        std::cout <<rutaarir<<std::endl;
        FILE *arch;
        arch=fopen(rutaarir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            MBR_Disco Nodo_AP;
            fread(&Nodo_AP, sizeof(MBR_Disco), 1, arch);
            std::string CadenaImprimir;
            //guardo las particiones
            MBR_Particion ArrayParticiones[5];
            ArrayParticiones[0]=Nodo_AP.mbr_partition_1;
            ArrayParticiones[1]=Nodo_AP.mbr_partition_2;
            ArrayParticiones[2]=Nodo_AP.mbr_partition_3;
            ArrayParticiones[3]=Nodo_AP.mbr_partition_4;
            int arr[4];
            int n = sizeof(arr)/sizeof(arr[0]);
            arr[3]=Nodo_AP.mbr_partition_4.part_start;
            arr[1]=Nodo_AP.mbr_partition_2.part_start;
            arr[2]=Nodo_AP.mbr_partition_3.part_start;
            arr[0]=Nodo_AP.mbr_partition_1.part_start;
            std::sort(arr, arr+n);



            CadenaImprimir="digraph D { \n";
            CadenaImprimir+="graph [label=\"REPORTE DISK\", labelloc=t, fontsize=20]; rankdir=TB \n";
            CadenaImprimir+="node[shape=record,style=filled] \n";
            CadenaImprimir+="Datos[label =\"MBR ";

            //datos
            bool bandera=false;
            float sumaLibre=0;
            for(int par=0;par<4;par++){
                //Vamos Validando si esta lleno y lo insertamos sino valida hasta que encuentre uno lleno
                if(strcmp(ArrayParticiones[par].part_status,"S")==0){
                    //PRIMERO HACEMOS CALUCLO DE ESPACIO LIBRE
                    if(bandera==true){
                        CadenaImprimir+="| {Libre |";
                        float porcentajeLibre=(sumaLibre/((float)Nodo_AP.mbr_tamanio))*100;
                        std::cout<<"SUMA TOTAL LIBRE "<<sumaLibre<<std::endl;
                        CadenaImprimir+=std::to_string(porcentajeLibre);


                        sumaLibre=0;
                        CadenaImprimir+=" % }";
                        bandera=false;
                    }



                    //insertamos
                    CadenaImprimir+="| {";
                    CadenaImprimir.append(ArrayParticiones[par].part_name);
                    CadenaImprimir+=": ";
                    CadenaImprimir.append(ArrayParticiones[par].part_type);

                    float porcentaje=(float)((float)(ArrayParticiones[par].part_size/(float)Nodo_AP.mbr_tamanio)*100);
                    std::cout<<porcentaje<<std::endl;
                    CadenaImprimir+="|"+std::to_string(porcentaje)+"% }";

                }else{
                    std::cout<<"SUMA Antes LIBE "<<sumaLibre<<std::endl;
                    std::cout<<"SUMA  LIBE "<<(float)(ArrayParticiones[par].part_size)<<std::endl;
                    sumaLibre+=(float)(ArrayParticiones[par].part_size);
                    std::cout<<"SUMA Despues LIBE "<<sumaLibre<<std::endl;
                    bandera=true;


                }
                if(par==3){
                    float posf=((float)Nodo_AP.mbr_tamanio)-((float)ArrayParticiones[par].part_start)-((float)ArrayParticiones[par].part_size);
                    sumaLibre+=posf;

                    CadenaImprimir+="| {Libre |";
                    float porcentajeLibre=(sumaLibre/((float)Nodo_AP.mbr_tamanio))*100;
                    CadenaImprimir+=std::to_string(porcentajeLibre);

                    CadenaImprimir+=" % }";
                }

            }

            CadenaImprimir+="\"]\n";
            CadenaImprimir+="}";


            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+id+".dot";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
            char Comandogenerar[100];
            strcpy(Comandogenerar,comando.c_str());
            system(Comandogenerar);
        }
        fclose(arch);
    }else{
        std::cout << "ID NO MONTADO"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_Sb(std::string rutabrir,std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }
    //busqueda si se realizo un lost
    bool bandera=false;
    for(int pos=0;pos<Id_Loss.size();pos++){
        if(Id_Loss[pos]==id){
            bandera=true;
        }
    }
    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            Super_Bloque Nodo_AP;
            fseek(arch,PosicionStart,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
            std::string CadenaImprimir;
            CadenaImprimir="digraph D { \n";
            CadenaImprimir+="node [shape=plaintext] \n";
            CadenaImprimir+="some_node [ \n";
            CadenaImprimir+="label=< \n";
            CadenaImprimir+="<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
            //agregar columnas
            CadenaImprimir+="<tr><td> "+rutabrir+" </td></tr> \n";
            CadenaImprimir+="<tr><td> NOMBRE </td><td> VALOR </td></tr> \n";

            CadenaImprimir+="<tr><td> s_inodes_count </td><td> "+std::to_string(Nodo_AP.s_inodes_count)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> s_blocks_count </td><td> "+std::to_string(Nodo_AP.s_blocks_count)+" </td></tr> \n";
            if (bandera==false){
                CadenaImprimir+="<tr><td> s_free_inodes_count </td><td> "+std::to_string(Nodo_AP.s_free_inodes_count)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> s_free_blocks_count </td><td> "+std::to_string(Nodo_AP.s_free_blocks_count)+" </td></tr> \n";
            }else{
                //simmula perdida
                CadenaImprimir+="<tr><td> s_free_inodes_count </td><td> "+std::to_string(Nodo_AP.s_inodes_count)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> s_free_blocks_count </td><td> "+std::to_string(Nodo_AP.s_blocks_count)+" </td></tr> \n";
            }

            CadenaImprimir+="<tr><td> s_mtime </td><td> ";
            CadenaImprimir.append(Nodo_AP.mtime);
            CadenaImprimir+=" </td></tr> \n";
            CadenaImprimir+="<tr><td> s_umtime </td><td> ";
            CadenaImprimir.append(Nodo_AP.umtime);
            CadenaImprimir+=" </td></tr> \n";

            CadenaImprimir+="<tr><td> s_mnt_count </td><td> "+std::to_string(Nodo_AP.s_mnt_count)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> s_magic </td><td> ";
            CadenaImprimir.append(Nodo_AP.s_magic);
            CadenaImprimir+="</td></tr> \n";

            CadenaImprimir+="<tr><td> s_inode_size </td><td> "+std::to_string(Nodo_AP.s_inode_size)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> s_block_size </td><td> "+std::to_string(Nodo_AP.s_block_size)+" </td></tr> \n";

            if(bandera==false){
                CadenaImprimir+="<tr><td> s_first_ino </td><td> "+std::to_string(Nodo_AP.s_firts_ino)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> s_first_blo </td><td> "+std::to_string(Nodo_AP.s_firts_blo)+" </td></tr> \n";
            }else{
                CadenaImprimir+="<tr><td> s_first_ino </td><td> "+std::to_string(0)+" </td></tr> \n";
                CadenaImprimir+="<tr><td> s_first_blo </td><td> "+std::to_string(0)+" </td></tr> \n";
            }

            CadenaImprimir+="<tr><td> s_bm_inode_start </td><td> "+std::to_string(Nodo_AP.s_bm_inode_start)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> s_bm_block_start </td><td> "+std::to_string(Nodo_AP.s_bm_block_start)+" </td></tr> \n";

            CadenaImprimir+="<tr><td> s_inode_start </td><td> "+std::to_string(Nodo_AP.s_inode_start)+" </td></tr> \n";
            CadenaImprimir+="<tr><td> s_block_start </td><td> "+std::to_string(Nodo_AP.s_block_start)+" </td></tr> \n";
            CadenaImprimir+="</table>>]; \n";

            CadenaImprimir+="}";



            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+id+".dot";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
            std::cout <<"Reporte: "<<rutaparadot<<std::endl;
            char Comandogenerar[100];
            strcpy(Comandogenerar,comando.c_str());
            system(Comandogenerar);
            fclose(arch);
        }

    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_bm(std::string rutabrir, std::string id, std::string ruta, int tipo){
    //tipo 0 es el de inodos
    //tipo 1 es el de bloques
    //buscarruta
    std::string CadenaImprimir;
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }
    //busqueda de perdida
    bool bandera=false;
    for(int pos=0;pos<Id_Loss.size();pos++){
        if(Id_Loss[pos]==id){
            bandera=true;
        }
    }
    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            //Obtenemos el super bloque
            Super_Bloque Nodo_AP;
            fseek(arch,PosicionStart,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

            //reporte de BM inodos
            if(tipo==0){
                int maximo=0;
                NodoBitmap Nodo_temporal;
                for(int posicionLectura=Nodo_AP.s_bm_inode_start;posicionLectura<Nodo_AP.s_bm_block_start;posicionLectura++){
                    int posleer=(posicionLectura*sizeof (NodoBitmap));
                    fseek(arch,posleer,SEEK_SET);
                    fread(&Nodo_temporal, sizeof(NodoBitmap), 1, arch);
                    maximo++;
                    if(maximo>20){
                        maximo=1;
                        CadenaImprimir+='\n';
                        if(bandera==false){
                            CadenaImprimir+=std::to_string(Nodo_temporal.Dato);
                        }else{CadenaImprimir+="0";}

                        CadenaImprimir+=" ";
                    }else{
                        if(bandera==false){
                            CadenaImprimir+=std::to_string(Nodo_temporal.Dato);
                        }else{CadenaImprimir+="0";}
                        CadenaImprimir+=" ";
                    }
                }
            }
            //reporte de BM de bloques
            if(tipo==1){
                int maximo=0;
                NodoBitmap Nodo_temporal;
                for(int posicionLectura=Nodo_AP.s_bm_block_start;posicionLectura<Nodo_AP.s_inode_start;posicionLectura++){
                    int posleer=(posicionLectura*sizeof (NodoBitmap));
                    fseek(arch,posleer,SEEK_SET);
                    fread(&Nodo_temporal, sizeof(NodoBitmap), 1, arch);
                    maximo++;
                    if(maximo>20){
                        maximo=1;
                        CadenaImprimir+='\n';
                        if(bandera==false){
                            CadenaImprimir+=std::to_string(Nodo_temporal.Dato);
                        }else{CadenaImprimir+="0";}
                        CadenaImprimir+=" ";
                    }else{
                        if(bandera==false){
                            CadenaImprimir+=std::to_string(Nodo_temporal.Dato);
                        }else{CadenaImprimir+="0";}
                        CadenaImprimir+=" ";
                    }
                }
            }

            fclose(arch);
        }
        //creamos una ruta para crear carpetas
        std::ofstream file;
        std::string rutaparadot;
        for(int a=0;a<ruta.size();a++){
            if(int(ruta.at(a))==46){
                break;
            }
            rutaparadot+=ruta.at(a);

        }
        //creo carpetas
        QString qstr = QString::fromStdString(rutaparadot);
        QStringList list1 = qstr.split('/');
        QString s;
        for( int i=0; i<list1.size(); i++ ){
            if(i==list1.size()-1){

            }else{
                s+=list1.at(i);
                QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                s+="/";
            }
        }
        //creo el archivo y le ingreso los valores
        std::string rutanueva=rutaparadot+".txt";
        file.open(rutanueva);
        file <<CadenaImprimir;
        file.close();
        std::cout <<"Reporte: "<<rutaparadot<<std::endl;
    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_tree(std::string rutabrir, std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }
    //busqueda de perdida
    bool bandera=false;
    for(int pos=0;pos<Id_Loss.size();pos++){
        if(Id_Loss[pos]==id){
            bandera=true;
        }
    }
    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            Super_Bloque Nodo_AP;
            fseek(arch,PosicionStart,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
            CadenaImprimir.clear();
            CadenaImprimir+="digraph g {\n rankdir = LR  \n";
            CadenaImprimir+="node [shape = plaintext ]; \n";

            //Agregamos contenido
            if(bandera==false){
                Agregar_Contenido_Inodo_tree(rutabrir,Nodo_AP.s_inode_start,PosicionStart);
            }else{
                Tabla_Inodo Tabla_AP;
                fseek(arch,Nodo_AP.s_inode_start,SEEK_SET);
                fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
                CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\" [";
                CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
                CadenaImprimir+="<tr>\n    <td port=\"f0\"> Inodo "+std::to_string(Tabla_AP.ID)+"</td> \n</tr>\n";
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_iud </td>\n";
                CadenaImprimir+="   <td> "+std::to_string(0)+"</td> \n</tr>\n";

                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_gid </td>\n";
                CadenaImprimir+="   <td> "+std::to_string(0)+"</td> \n</tr>\n";

                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_size </td>\n";
                CadenaImprimir+="   <td> "+std::to_string(0)+"</td> \n</tr>\n";

                CadenaImprimir+="<tr>\n   <td> i_atime </td>\n   <td> ";
                CadenaImprimir+=" </td> \n</tr>\n";

                CadenaImprimir+="<tr>\n   <td> i_ctime </td>\n   <td> ";
                CadenaImprimir+=" </td> \n</tr>\n";

                CadenaImprimir+="<tr>\n   <td> i_mtime </td>\n   <td> ";
                CadenaImprimir+=" </td> \n</tr>\n";

                for(int posicion=0;posicion<15;posicion++){
                    //bloques directos
                    if(posicion<12){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_D </td>\n";
                        if(posicion!=0){
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(-1)+"</td> \n</tr>\n";
                        }else{
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(0)+"</td> \n</tr>\n";
                        }
                    }
                    //bloque simple indirecto
                    if(posicion==12){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_SI </td>\n";
                        CadenaImprimir+="   <td> "+std::to_string(-1)+"</td> \n</tr>\n";
                    }
                    //bloque doble indirecto
                    if(posicion==13){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_DI </td>\n";
                        CadenaImprimir+="   <td> "+std::to_string(-1)+"</td> \n</tr>\n";
                    }
                    //bloque triple indirecto
                    if(posicion==14){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_TI </td>\n";
                        CadenaImprimir+="   <td> "+std::to_string(-1)+"</td> \n</tr>\n";
                    }
                }

                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_type </td>\n";
                CadenaImprimir+="   <td> </td> \n</tr>\n";
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_perm </td>\n";
                CadenaImprimir+="   <td> </td> \n</tr>\n";
                CadenaImprimir+="</table> \n";
                CadenaImprimir+=">];\n";
                //es carpeta
                //agrego contenido
                CadenaImprimir+="\"block0\" [";
                CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td port=\"f0\"> Bloque 0</td> \n</tr>\n";
                //actual
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir.append("/");
                CadenaImprimir+="</td>\n   <td port=\"f1\"> "+std::to_string(0)+"</td> \n</tr>\n";
                //padre
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir.append("..");
                CadenaImprimir+="</td>\n   <td port=\"f2\"> "+std::to_string(0)+"</td> \n</tr>\n";
                //otros
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir+="</td>\n   <td port=\"f3\"> "+std::to_string(-1)+"</td> \n</tr>\n";
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir+="</td>\n   <td port=\"f4\"> "+std::to_string(-1)+"</td> \n</tr>\n";

                CadenaImprimir+="</table> \n";
                CadenaImprimir+=">];\n";
                //creamos relaciones
                CadenaImprimir+="\"inode"+std::to_string(0)+"\":f1 -> \"block0\":f0; \n";

            }



            CadenaImprimir+="}";
            //creamos una ruta para crear carpetas
            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+id+".dot";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
            std::cout <<"Reporte: "<<rutaparadot<<std::endl;
            char Comandogenerar[100];
            strcpy(Comandogenerar,comando.c_str());
            system(Comandogenerar);
            fclose(arch);
        }

    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }
}

void Graficar_Reportes::Agregar_Contenido_Inodo_tree(std::string rutabrir, int posicionStart,int PosicionSuperB){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{
        Tabla_Inodo Tabla_AP;
        fseek(arch,posicionStart,SEEK_SET);
        fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
        //agregamos tabla
        CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\" [";
        CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
        CadenaImprimir+="<tr>\n    <td port=\"f0\"> Inodo "+std::to_string(Tabla_AP.ID)+"</td> \n</tr>\n";
        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td> i_iud </td>\n";
        CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_uid)+"</td> \n</tr>\n";

        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td> i_gid </td>\n";
        CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_gid)+"</td> \n</tr>\n";

        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td> i_size </td>\n";
        CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_size)+"</td> \n</tr>\n";

        CadenaImprimir+="<tr>\n   <td> i_atime </td>\n   <td> ";
        CadenaImprimir.append(Tabla_AP.i_atime);
        CadenaImprimir+="</td> \n</tr>\n";

        CadenaImprimir+="<tr>\n   <td> i_ctime </td>\n   <td> ";
        CadenaImprimir.append(Tabla_AP.i_ctime);
        CadenaImprimir+="</td> \n</tr>\n";

        CadenaImprimir+="<tr>\n   <td> i_mtime </td>\n   <td> ";
        CadenaImprimir.append(Tabla_AP.i_mtime);
        CadenaImprimir+="</td> \n</tr>\n";

        for(int posicion=0;posicion<15;posicion++){
            //bloques directos
            if(posicion<12){
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> B_D </td>\n";
                CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
            }
            //bloque simple indirecto
            if(posicion==12){
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> B_SI </td>\n";
                CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
            }
            //bloque doble indirecto
            if(posicion==13){
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> B_DI </td>\n";
                CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
            }
            //bloque triple indirecto
            if(posicion==14){
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> B_TI </td>\n";
                CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
            }
        }

        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td> i_type </td>\n";
        CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_type)+"</td> \n</tr>\n";
        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td> i_perm </td>\n";
        CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_perm)+"</td> \n</tr>\n";
        CadenaImprimir+="</table> \n";
        CadenaImprimir+=">];\n";
        //validamos
        for(int posicion=0;posicion<15;posicion++){
            //bloques directos
            if(posicion<12){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //llama al metodo de bloques
                    if(Tabla_AP.i_type==0){
                        //bloque Carpeta
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[posicion]*sizeof (Bloque_Carpeta));
                        Agregar_Contenido_Block_tree(rutabrir,posicion_inicio,0,PosicionSuperB,posicion+1);
                    }else{
                        //bloque Archivo
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);

                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[posicion]*sizeof (Bloque_Carpeta));
                        Agregar_Contenido_Block_tree(rutabrir,posicion_inicio,1,PosicionSuperB,posicion+1);
                        CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Tabla_AP.i_block[posicion])+"\":f0; \n";

                    }
                }
            }
            //bloque simple indirecto
            if(posicion==12){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //bloque Apuntador
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);

                    int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[posicion]*sizeof (Bloque_Carpeta));
                    Agregar_Contenido_Block_tree_Puntero(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,1);
                    CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Tabla_AP.i_block[posicion])+"\":f0; \n";

                }
            }
            //bloque doble indirecto
            if(posicion==13){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //bloque Apuntador
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);

                    int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[posicion]*sizeof (Bloque_Carpeta));
                    Agregar_Contenido_Block_tree_Puntero(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,2);
                    CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Tabla_AP.i_block[posicion])+"\":f0; \n";

                }
            }
            //bloque triple indirecto
            if(posicion==14){
                if(Tabla_AP.i_block[posicion]!=-1){
                    //bloque Apuntador
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);

                    int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[posicion]*sizeof (Bloque_Carpeta));
                    Agregar_Contenido_Block_tree_Puntero(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,3);
                    CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Tabla_AP.i_block[posicion])+"\":f0; \n";

                }
            }
        }


        fclose(arch);


    }

}

void Graficar_Reportes::Agregar_Contenido_Block_tree(std::string rutabrir, int posicionStart, int tipo, int PosicionSuperB,int PosicionCuadroInode){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{

        if(tipo==1){
            //el bloque es de archivo
            Bloque_Archivo Bloque_AR;
            fseek(arch,posicionStart,SEEK_SET);
            fread(&Bloque_AR, sizeof(Bloque_Carpeta), 1, arch);
            //agrego contenido
            CadenaImprimir+="\"block"+std::to_string(Bloque_AR.ID)+"\" [";
            CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
            CadenaImprimir+="<tr>\n";
            CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_AR.ID)+"</td> \n</tr>\n";
            //contenido
            CadenaImprimir+="<tr>\n  <td> ";
            CadenaImprimir.append(Bloque_AR.b_content);
            CadenaImprimir+="</td>\n </tr> \n";

            CadenaImprimir+="</table> \n";
            CadenaImprimir+=">];\n";

        }else if(tipo==0){
            //es carpeta
            Bloque_Carpeta Bloque_CP;
            fseek(arch,posicionStart,SEEK_SET);
            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
            //agrego contenido
            CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\" [";
            CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
            CadenaImprimir+="<tr>\n";
            CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_CP.ID)+"</td> \n</tr>\n";
            //actual
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name1);
            CadenaImprimir+="</td>\n   <td port=\"f1\"> "+std::to_string(Bloque_CP.b_inodo1)+"</td> \n</tr>\n";
            //padre
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name2);
            CadenaImprimir+="</td>\n   <td port=\"f2\"> "+std::to_string(Bloque_CP.b_inodo2)+"</td> \n</tr>\n";
            //otros
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name3);
            CadenaImprimir+="</td>\n   <td port=\"f3\"> "+std::to_string(Bloque_CP.b_inodo3)+"</td> \n</tr>\n";
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name4);
            CadenaImprimir+="</td>\n   <td port=\"f4\"> "+std::to_string(Bloque_CP.b_inodo4)+"</td> \n</tr>\n";

            CadenaImprimir+="</table> \n";
            CadenaImprimir+=">];\n";
            //creamos relaciones
            CadenaImprimir+="\"inode"+std::to_string(Bloque_CP.b_inodo1)+"\":f"+std::to_string(PosicionCuadroInode)+" -> \"block"+std::to_string(Bloque_CP.ID)+"\":f0; \n";

            //comprobacion si hay mas relaciones
            if(strcmp(Bloque_CP.b_name2,"..")!=0){
                //comprobamos las primeras dos posiciones
                if(Bloque_CP.b_inodo1!=-1 && strcmp(Bloque_CP.b_name1,".")!=0){
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                    int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo1*sizeof (Tabla_Inodo));

                    Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                    //creamos transicion                    
                    CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f1 -> \"inode"+std::to_string(Bloque_CP.b_inodo1)+"\":f0; \n";
                }
                if(Bloque_CP.b_inodo2!=-1){
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                    int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo2*sizeof (Tabla_Inodo));

                    Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                    //Creamos transicion
                    CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f2 -> \"inode"+std::to_string(Bloque_CP.b_inodo2)+"\":f0; \n";
                }
            }
            if(Bloque_CP.b_inodo3!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo3*sizeof (Tabla_Inodo));

                Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                //creamos transicion
                CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f3 -> \"inode"+std::to_string(Bloque_CP.b_inodo3)+"\":f0; \n";
            }
            if(Bloque_CP.b_inodo4!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo4*sizeof (Tabla_Inodo));

                Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                //Creamos transicion
                CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f4 -> \"inode"+std::to_string(Bloque_CP.b_inodo4)+"\":f0; \n";
            }

            fclose(arch);
        }

    }


}

void Graficar_Reportes::Agregar_Contenido_Block_tree_Puntero(std::string rutabrir, int posicionStart, int tipo,int PosicionSuperB ,int NumerodeApuuntadores){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{

        //busca apuntadore nuevo
        //el bloque es de archivo
        Bloque_Apuntador Bloque_AP;
        fseek(arch,posicionStart,SEEK_SET);
        fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
        //agrego contenido
        CadenaImprimir+="\"block"+std::to_string(Bloque_AP.ID)+"\" [";
        CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_AP.ID)+"</td> \n</tr>\n";
        //contenido
        for(int posicion=0;posicion<15;posicion++){
            CadenaImprimir+="<tr>\n  <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Bloque_AP.b_pointers[posicion])+"</td>\n </tr> \n";
        }

        CadenaImprimir+="</table> \n";
        CadenaImprimir+=">];\n";
        //creacion de relacion
        NumerodeApuuntadores--;
        for(int posicion=0;posicion<15;posicion++){
            if(Bloque_AP.b_pointers[posicion]!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_block_start+(Bloque_AP.b_pointers[posicion]*sizeof (Bloque_Carpeta));

                if(NumerodeApuuntadores>0){
                    Agregar_Contenido_Block_tree_Puntero(rutabrir,posicion_inicio,tipo,PosicionSuperB,NumerodeApuuntadores);
                    CadenaImprimir+="\"block"+std::to_string(Bloque_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Bloque_AP.b_pointers[posicion])+"\":f0; \n";
                }else{
                    if(tipo==1){
                        Agregar_Contenido_Block_tree(rutabrir,posicion_inicio,tipo,PosicionSuperB,posicion+1);
                        CadenaImprimir+="\"block"+std::to_string(Bloque_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Bloque_AP.b_pointers[posicion])+"\":f0; \n";
                    }else if(tipo==0){
                        //es carpeta
                        Bloque_Carpeta Bloque_CP;
                        fseek(arch,posicion_inicio,SEEK_SET);
                        fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
                        //agrego contenido
                        CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\" [";
                        CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_CP.ID)+"</td> \n</tr>\n";
                        //actual
                        CadenaImprimir+="<tr>\n   <td> ";
                        CadenaImprimir.append(Bloque_CP.b_name1);
                        CadenaImprimir+="</td>\n   <td port=\"f1\"> "+std::to_string(Bloque_CP.b_inodo1)+"</td> \n</tr>\n";
                        //padre
                        CadenaImprimir+="<tr>\n   <td> ";
                        CadenaImprimir.append(Bloque_CP.b_name2);
                        CadenaImprimir+="</td>\n   <td port=\"f2\"> "+std::to_string(Bloque_CP.b_inodo2)+"</td> \n</tr>\n";
                        //otros
                        CadenaImprimir+="<tr>\n   <td> ";
                        CadenaImprimir.append(Bloque_CP.b_name3);
                        CadenaImprimir+="</td>\n   <td port=\"f3\"> "+std::to_string(Bloque_CP.b_inodo3)+"</td> \n</tr>\n";
                        CadenaImprimir+="<tr>\n   <td> ";
                        CadenaImprimir.append(Bloque_CP.b_name4);
                        CadenaImprimir+="</td>\n   <td port=\"f4\"> "+std::to_string(Bloque_CP.b_inodo4)+"</td> \n</tr>\n";

                        CadenaImprimir+="</table> \n";
                        CadenaImprimir+=">];\n";
                        CadenaImprimir+="\"block"+std::to_string(Bloque_AP.ID)+"\":f"+std::to_string(posicion+1)+" -> \"block"+std::to_string(Bloque_AP.b_pointers[posicion])+"\":f0; \n";


                        //creamos relaciones
                        if(strcmp(Bloque_CP.b_name2,"..")!=0){
                            //comprobamos las primeras dos posiciones
                            if(Bloque_CP.b_inodo1!=-1 && strcmp(Bloque_CP.b_name1,".")!=0){
                                Super_Bloque Super_B;
                                fseek(arch,PosicionSuperB,SEEK_SET);
                                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo1*sizeof (Tabla_Inodo));

                                Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                                //creamos transicion
                                CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f1 -> \"inode"+std::to_string(Bloque_CP.b_inodo1)+"\":f0; \n";
                            }
                            if(Bloque_CP.b_inodo2!=-1){
                                Super_Bloque Super_B;
                                fseek(arch,PosicionSuperB,SEEK_SET);
                                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo2*sizeof (Tabla_Inodo));

                                Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                                //Creamos transicion
                                CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f2 -> \"inode"+std::to_string(Bloque_CP.b_inodo2)+"\":f0; \n";
                            }
                        }
                        if(Bloque_CP.b_inodo3!=-1){
                            Super_Bloque Super_B;
                            fseek(arch,PosicionSuperB,SEEK_SET);
                            fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                            int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo3*sizeof (Tabla_Inodo));

                            Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                            //creamos transicion
                            CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f3 -> \"inode"+std::to_string(Bloque_CP.b_inodo3)+"\":f0; \n";
                        }
                        if(Bloque_CP.b_inodo4!=-1){
                            Super_Bloque Super_B;
                            fseek(arch,PosicionSuperB,SEEK_SET);
                            fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                            int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo4*sizeof (Tabla_Inodo));

                            Agregar_Contenido_Inodo_tree(rutabrir,posicion_inicio,PosicionSuperB);
                            //Creamos transicion
                            CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\":f4 -> \"inode"+std::to_string(Bloque_CP.b_inodo4)+"\":f0; \n";
                        }


                    }

                    //fin de apuntadores
                }

            }
        }
    }
}

void Graficar_Reportes::Graficar_inode(std::string rutabrir, std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }
    //busqueda de perdida
    bool bandera=false;
    for(int pos=0;pos<Id_Loss.size();pos++){
        if(Id_Loss[pos]==id){
            bandera=true;
        }
    }
    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            Super_Bloque Nodo_AP;
            fseek(arch,PosicionStart,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
            CadenaImprimir.clear();
            CadenaImprimir+="digraph g {\n rankdir = LR  \n";
            CadenaImprimir+="node [shape = plaintext ]; \n";

            //Agregamos contenido
            if(bandera==false){
                for(int posicion=0;posicion<Nodo_AP.s_firts_ino;posicion++){
                    int posicion_Start_ciclo=Nodo_AP.s_inode_start+(posicion*sizeof (Tabla_Inodo));
                    Tabla_Inodo Tabla_AP;
                    fseek(arch,posicion_Start_ciclo,SEEK_SET);
                    fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
                    //agregamos tabla
                    CadenaImprimir+="\"inode"+std::to_string(Tabla_AP.ID)+"\" [";
                    CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
                    CadenaImprimir+="<tr>\n    <td port=\"f0\"> Inodo "+std::to_string(Tabla_AP.ID)+"</td> \n</tr>\n";
                    CadenaImprimir+="<tr>\n";
                    CadenaImprimir+="   <td> i_iud </td>\n";
                    CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_uid)+"</td> \n</tr>\n";

                    CadenaImprimir+="<tr>\n";
                    CadenaImprimir+="   <td> i_gid </td>\n";
                    CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_gid)+"</td> \n</tr>\n";

                    CadenaImprimir+="<tr>\n";
                    CadenaImprimir+="   <td> i_size </td>\n";
                    CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_size)+"</td> \n</tr>\n";

                    CadenaImprimir+="<tr>\n   <td> i_atime </td>\n   <td> ";
                    CadenaImprimir.append(Tabla_AP.i_atime);
                    CadenaImprimir+="</td> \n</tr>\n";

                    CadenaImprimir+="<tr>\n   <td> i_ctime </td>\n   <td> ";
                    CadenaImprimir.append(Tabla_AP.i_ctime);
                    CadenaImprimir+="</td> \n</tr>\n";

                    CadenaImprimir+="<tr>\n   <td> i_mtime </td>\n   <td> ";
                    CadenaImprimir.append(Tabla_AP.i_mtime);
                    CadenaImprimir+="</td> \n</tr>\n";

                    for(int posicion=0;posicion<15;posicion++){
                        //bloques directos
                        if(posicion<12){
                            CadenaImprimir+="<tr>\n";
                            CadenaImprimir+="   <td> B_D </td>\n";
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
                        }
                        //bloque simple indirecto
                        if(posicion==12){
                            CadenaImprimir+="<tr>\n";
                            CadenaImprimir+="   <td> B_SI </td>\n";
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
                        }
                        //bloque doble indirecto
                        if(posicion==13){
                            CadenaImprimir+="<tr>\n";
                            CadenaImprimir+="   <td> B_DI </td>\n";
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
                        }
                        //bloque triple indirecto
                        if(posicion==14){
                            CadenaImprimir+="<tr>\n";
                            CadenaImprimir+="   <td> B_TI </td>\n";
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Tabla_AP.i_block[posicion])+"</td> \n</tr>\n";
                        }
                    }

                    CadenaImprimir+="<tr>\n";
                    CadenaImprimir+="   <td> i_type </td>\n";
                    CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_type)+"</td> \n</tr>\n";
                    CadenaImprimir+="<tr>\n";
                    CadenaImprimir+="   <td> i_perm </td>\n";
                    CadenaImprimir+="   <td> "+std::to_string(Tabla_AP.i_perm)+"</td> \n</tr>\n";
                    CadenaImprimir+="</table> \n";
                    CadenaImprimir+=">];\n";
                }

                //transiciones
                for(int posicion=0;posicion<Nodo_AP.s_firts_ino-1;posicion++){
                    CadenaImprimir+="\"inode"+std::to_string(posicion)+"\":f0 -> \"inode"+std::to_string(posicion+1)+"\":f0; \n";

                }


            }else{
                //hay perdida
                Tabla_Inodo Tabla_AP;
                fseek(arch,Nodo_AP.s_inode_start,SEEK_SET);
                fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
                CadenaImprimir+="\"inode0\" [";
                CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
                CadenaImprimir+="<tr>\n    <td port=\"f0\"> Inodo 0</td> \n</tr>\n";
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_iud </td>\n";
                CadenaImprimir+="   <td> "+std::to_string(0)+"</td> \n</tr>\n";

                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_gid </td>\n";
                CadenaImprimir+="   <td> "+std::to_string(0)+"</td> \n</tr>\n";

                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_size </td>\n";
                CadenaImprimir+="   <td> "+std::to_string(0)+"</td> \n</tr>\n";

                CadenaImprimir+="<tr>\n   <td> i_atime </td>\n   <td> ";
                CadenaImprimir+=" </td> \n</tr>\n";

                CadenaImprimir+="<tr>\n   <td> i_ctime </td>\n   <td> ";
                CadenaImprimir+=" </td> \n</tr>\n";

                CadenaImprimir+="<tr>\n   <td> i_mtime </td>\n   <td> ";
                CadenaImprimir+=" </td> \n</tr>\n";

                for(int posicion=0;posicion<15;posicion++){
                    //bloques directos
                    if(posicion<12){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_D </td>\n";
                        if(posicion!=0){
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(-1)+"</td> \n</tr>\n";
                        }else{
                            CadenaImprimir+="   <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(0)+"</td> \n</tr>\n";
                        }
                    }
                    //bloque simple indirecto
                    if(posicion==12){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_SI </td>\n";
                        CadenaImprimir+="   <td> "+std::to_string(-1)+"</td> \n</tr>\n";
                    }
                    //bloque doble indirecto
                    if(posicion==13){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_DI </td>\n";
                        CadenaImprimir+="   <td> "+std::to_string(-1)+"</td> \n</tr>\n";
                    }
                    //bloque triple indirecto
                    if(posicion==14){
                        CadenaImprimir+="<tr>\n";
                        CadenaImprimir+="   <td> B_TI </td>\n";
                        CadenaImprimir+="   <td> "+std::to_string(-1)+"</td> \n</tr>\n";
                    }
                }

                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_type </td>\n";
                CadenaImprimir+="   <td> </td> \n</tr>\n";
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td> i_perm </td>\n";
                CadenaImprimir+="   <td> </td> \n</tr>\n";
                CadenaImprimir+="</table> \n";
                CadenaImprimir+=">];\n";
            }

            CadenaImprimir+="}";
            //creamos una ruta para crear carpetas
            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+id+".dot";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
            std::cout <<"Reporte: "<<rutaparadot<<std::endl;
            char Comandogenerar[100];
            strcpy(Comandogenerar,comando.c_str());
            system(Comandogenerar);
            fclose(arch);
        }

    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_block(std::string rutabrir, std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }
    //busqueda de perdida
    bool bandera=false;
    for(int pos=0;pos<Id_Loss.size();pos++){
        if(Id_Loss[pos]==id){
            bandera=true;
        }
    }
    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            Super_Bloque Nodo_AP;
            fseek(arch,PosicionStart,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
            CadenaImprimir.clear();
            CadenaImprimir+="digraph g {\n rankdir = LR  \n";
            CadenaImprimir+="node [shape = plaintext ]; \n";

            //Agregar Contenido
            if(bandera==false){
                temporal.clear();
                Graficar_NodoBlock(rutabrir,PosicionStart,3,Nodo_AP.s_inode_start);
                //creamos relaciones
                for(int pos=0;pos<temporal.size()-1;pos++){
                    CadenaImprimir+="\"block"+std::to_string(temporal[pos])+"\":f0 -> \"block"+std::to_string(temporal[pos+1])+"\":f0; \n";
                }
            }else{
                //hubo perdida
                //agrego contenido
                CadenaImprimir+="\"block0\" [";
                CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
                CadenaImprimir+="<tr>\n";
                CadenaImprimir+="   <td port=\"f0\"> Bloque 0</td> \n</tr>\n";
                //actual
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir.append("/");
                CadenaImprimir+="</td>\n   <td port=\"f1\"> "+std::to_string(0)+"</td> \n</tr>\n";
                //padre
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir.append("..");
                CadenaImprimir+="</td>\n   <td port=\"f2\"> "+std::to_string(0)+"</td> \n</tr>\n";
                //otros
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir+="</td>\n   <td port=\"f3\"> "+std::to_string(-1)+"</td> \n</tr>\n";
                CadenaImprimir+="<tr>\n   <td> ";
                CadenaImprimir+="</td>\n   <td port=\"f4\"> "+std::to_string(-1)+"</td> \n</tr>\n";

                CadenaImprimir+="</table> \n";
                CadenaImprimir+=">];\n";
            }



            CadenaImprimir+="}";
            //creamos una ruta para crear carpetas
            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+id+".dot";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
            std::cout <<"Reporte: "<<rutaparadot<<std::endl;
            char Comandogenerar[100];
            strcpy(Comandogenerar,comando.c_str());
            system(Comandogenerar);
            fclose(arch);
        }

    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_NodoBlock(std::string rutabrir,int PosicionSuperB, int tipo, int posicion){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{
        if(tipo==0){
            //carpeta
            Bloque_Carpeta Bloque_CP;
            fseek(arch,posicion,SEEK_SET);
            fread(&Bloque_CP, sizeof(Bloque_Carpeta), 1, arch);
            //agrego contenido
            temporal.append(Bloque_CP.ID);
            CadenaImprimir+="\"block"+std::to_string(Bloque_CP.ID)+"\" [";
            CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
            CadenaImprimir+="<tr>\n";
            CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_CP.ID)+"</td> \n</tr>\n";
            //actual
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name1);
            CadenaImprimir+="</td>\n   <td port=\"f1\"> "+std::to_string(Bloque_CP.b_inodo1)+"</td> \n</tr>\n";
            //padre
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name2);
            CadenaImprimir+="</td>\n   <td port=\"f2\"> "+std::to_string(Bloque_CP.b_inodo2)+"</td> \n</tr>\n";
            //otros
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name3);
            CadenaImprimir+="</td>\n   <td port=\"f3\"> "+std::to_string(Bloque_CP.b_inodo3)+"</td> \n</tr>\n";
            CadenaImprimir+="<tr>\n   <td> ";
            CadenaImprimir.append(Bloque_CP.b_name4);
            CadenaImprimir+="</td>\n   <td port=\"f4\"> "+std::to_string(Bloque_CP.b_inodo4)+"</td> \n</tr>\n";

            CadenaImprimir+="</table> \n";
            CadenaImprimir+=">];\n";
            //Creamos las relaciones

            //comprobacion si hay mas relaciones
            if(strcmp(Bloque_CP.b_name2,"..")!=0){
                //comprobamos las primeras dos posiciones
                if(Bloque_CP.b_inodo1!=-1 && strcmp(Bloque_CP.b_name1,".")!=0){
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                    int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo1*sizeof (Tabla_Inodo));

                    Graficar_NodoBlock(rutabrir,PosicionSuperB,3,posicion_inicio);

                }
                if(Bloque_CP.b_inodo2!=-1){
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                    int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo2*sizeof (Tabla_Inodo));

                    Graficar_NodoBlock(rutabrir,PosicionSuperB,3,posicion_inicio);

                }
            }
            if(Bloque_CP.b_inodo3!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo3*sizeof (Tabla_Inodo));

                Graficar_NodoBlock(rutabrir,PosicionSuperB,3,posicion_inicio);

            }
            if(Bloque_CP.b_inodo4!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo4*sizeof (Tabla_Inodo));

                Graficar_NodoBlock(rutabrir,PosicionSuperB,3,posicion_inicio);

            }

        }
        if(tipo==1){
            //Archivo
            Bloque_Archivo Bloque_AR;
            fseek(arch,posicion,SEEK_SET);
            fread(&Bloque_AR, sizeof(Bloque_Carpeta), 1, arch);
            //agrego contenido
            temporal.append(Bloque_AR.ID);
            CadenaImprimir+="\"block"+std::to_string(Bloque_AR.ID)+"\" [";
            CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
            CadenaImprimir+="<tr>\n";
            CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_AR.ID)+"</td> \n</tr>\n";
            //contenido
            CadenaImprimir+="<tr>\n  <td> ";
            CadenaImprimir.append(Bloque_AR.b_content);
            CadenaImprimir+="</td>\n </tr> \n";

            CadenaImprimir+="</table> \n";
            CadenaImprimir+=">];\n";
        }
        if(tipo==3){
            //inodo
            Tabla_Inodo Tabla_AP;
            fseek(arch,posicion,SEEK_SET);
            fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
            for(int pos=0;pos<15;pos++){
                if(pos<12){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Graficar_NodoBlock(rutabrir,PosicionSuperB,Tabla_AP.i_type,posicion_inicio);
                    }
                }
                if(pos==12){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Punteros(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,1);
                    }
                }
                if(pos==13){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Punteros(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,2);
                    }
                }
                if(pos==14){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Punteros(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,3);
                    }
                }
            }
        }

    }
}

void Graficar_Reportes::Punteros(std::string rutabrir, int posicionStart, int tipo,int PosicionSuperB ,int NumerodeApuuntadores){
    FILE *arch;
    arch=fopen(rutabrir.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{

        //busca apuntadore nuevo
        //el bloque es de archivo
        Bloque_Apuntador Bloque_AP;
        fseek(arch,posicionStart,SEEK_SET);
        fread(&Bloque_AP, sizeof(Bloque_Carpeta), 1, arch);
        //agrego contenido
        temporal.append(Bloque_AP.ID);
        CadenaImprimir+="\"block"+std::to_string(Bloque_AP.ID)+"\" [";
        CadenaImprimir+="label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" >\n";
        CadenaImprimir+="<tr>\n";
        CadenaImprimir+="   <td port=\"f0\"> Bloque "+std::to_string(Bloque_AP.ID)+"</td> \n</tr>\n";
        //contenido
        for(int posicion=0;posicion<15;posicion++){
            CadenaImprimir+="<tr>\n  <td port=\"f"+std::to_string(posicion+1)+"\"> "+std::to_string(Bloque_AP.b_pointers[posicion])+"</td>\n </tr> \n";
        }

        CadenaImprimir+="</table> \n";
        CadenaImprimir+=">];\n";
        //creacion de relacion
        NumerodeApuuntadores--;
        for(int posicion=0;posicion<15;posicion++){
            if(Bloque_AP.b_pointers[posicion]!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_block_start+(Bloque_AP.b_pointers[posicion]*sizeof (Bloque_Carpeta));

                if(NumerodeApuuntadores>0){
                    Punteros(rutabrir,posicion_inicio,tipo,PosicionSuperB,NumerodeApuuntadores);
                }else{
                    Graficar_NodoBlock(rutabrir,PosicionSuperB,tipo,posicion_inicio);
                    //fin de apuntadores
                }

            }
        }
    }
}

void Graficar_Reportes::Graficar_file(std::string rutabrir, std::string id, std::string ruta,std::string rutaBuscar){
    //buscarruta
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }

    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            //Agregamos Contenido
            std::string Contenido;
            BloqueArchivo *Bloq_Archiv=new BloqueArchivo();
            Contenido=Bloq_Archiv->Mostrar_Contenido(rutabrir,PosicionStart,rutaBuscar);
            CadenaImprimir.clear();
            CadenaImprimir+=Contenido;

            std::ofstream file;
            std::string rutaparadot;
            for(int a=0;a<ruta.size();a++){
                if(int(ruta.at(a))==46){
                    break;
                }
                rutaparadot+=ruta.at(a);

            }
            QString qstr = QString::fromStdString(rutaparadot);
            QStringList list1 = qstr.split('/');
            QString s;
            for( int i=0; i<list1.size(); i++ ){
                if(i==list1.size()-1){

                }else{
                    s+=list1.at(i);
                    QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                    s+="/";
                }
            }
            std::string rutanueva=rutaparadot+".txt";
            file.open(rutanueva);
            file <<CadenaImprimir;
            file.close();
            fclose(arch);
        }

    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }
}

void Graficar_Reportes::Graficar_Journaling(std::string rutabrir, std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }

    if(busc==true){
        FILE *arch;
        arch=fopen(rutabrir.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            Super_Bloque Nodo_AP;
            fseek(arch,PosicionStart,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
            if(Nodo_AP.s_filesystem_type==3){
                unsigned long long int poicionInicial=Nodo_AP.s_block_start*Nodo_AP.s_blocks_count;
                std::string CadenaImprimir;
                CadenaImprimir="digraph D { \n";
                CadenaImprimir+="node [shape=plaintext] \n";
                CadenaImprimir+="some_node [ \n";
                CadenaImprimir+="label=< \n";
                CadenaImprimir+="<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
                //agregar columnas
                CadenaImprimir+="<tr><td> "+rutabrir+" </td></tr> \n";
                CadenaImprimir+="<tr><td> NOMBRE </td><td> TIPO </td><td> DESCRIPCION </td><td> FECHA </td><td> TAMANIO </td><td> RUTA </td></tr> \n";
                while (true) {
                    Nodo_Journaling actual;
                    fseek(arch,poicionInicial,SEEK_SET);
                    fread(&actual, sizeof(Nodo_Journaling), 1, arch);

                    CadenaImprimir+="<tr><td> ";
                    CadenaImprimir.append(actual.Nombre);
                    CadenaImprimir+=" </td>";
                    CadenaImprimir+="<td> ";
                    CadenaImprimir.append(actual.tipo);
                    CadenaImprimir+=" </td>";
                    CadenaImprimir+="<td> ";
                    CadenaImprimir.append(actual.Descripcion);
                    CadenaImprimir+=" </td>";
                    CadenaImprimir+="<td> ";
                    CadenaImprimir.append(actual.mtime);
                    CadenaImprimir+=" </td>";
                    CadenaImprimir+="<td> ";
                    CadenaImprimir.append(std::to_string(actual.size));
                    CadenaImprimir+=" </td>";
                    CadenaImprimir+="<td> ";
                    CadenaImprimir.append(actual.ruta);
                    CadenaImprimir+=" </td>";
                    CadenaImprimir+="</tr> \n";
                    if(actual.Ultimo==1){
                        break;
                    }else{
                        poicionInicial+=sizeof(Nodo_Journaling);
                    }
                }
                CadenaImprimir+="</table>>]; \n";
                CadenaImprimir+="}";
                //creamos una ruta para crear carpetas
                std::ofstream file;
                std::string rutaparadot;
                for(int a=0;a<ruta.size();a++){
                    if(int(ruta.at(a))==46){
                        break;
                    }
                    rutaparadot+=ruta.at(a);

                }
                QString qstr = QString::fromStdString(rutaparadot);
                QStringList list1 = qstr.split('/');
                QString s;
                for( int i=0; i<list1.size(); i++ ){
                    if(i==list1.size()-1){

                    }else{
                        s+=list1.at(i);
                        QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                        s+="/";
                    }
                }
                std::string rutanueva=rutaparadot+id+".dot";
                file.open(rutanueva);
                file <<CadenaImprimir;
                file.close();
                std::string comando="dot -Tpng "+rutanueva+" -o "+rutaparadot+".png";
                std::cout <<"Reporte: "<<rutaparadot<<std::endl;
                char Comandogenerar[100];
                strcpy(Comandogenerar,comando.c_str());
                system(Comandogenerar);
                fclose(arch);
            }else{
                std::cout<<"El sistema no es EXT3"<<std::endl;
            }
        }

    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }

}

void Graficar_Reportes::Graficar_Ls(std::string rutabrir, std::string id, std::string ruta){
    //buscarruta
    bool busc=false;
    int Ugo=0;
    int id_usuario;
    std::string fecha;
    std::string tipo;
    std::string Nombre;
    std::string NombreParticion;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it3;
    //encontrar id y cantidad
    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
        std::string temporalstring2=it3->Id;
        //comprobamos si ya esta montado
        if(temporalstring2==id){
            rutabrir=it3->Ruta;
            NombreParticion=it3->Nombre;
            PosicionStart=it3->Posicion_Start;
            busc=true;
            break;
        }
    }

    if(busc==true){
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
            QString qstr = QString::fromStdString(ruta);
            QStringList list1 = qstr.split('/');

            //mas de uno entonces debe realizar una busqueda para insertar
            int posicionLectura=posicionInicio;

            for(int posicion_Varios=0;posicion_Varios<list1.size()+1;posicion_Varios++){

                if(posicion_Varios==list1.size()){
                    //obtenemos Ugo
                    Tabla_Inodo TablaPrimero;
                    fseek(arch,posicionLectura,SEEK_SET);
                    fread(&TablaPrimero, sizeof(Tabla_Inodo), 1, arch);
                    Ugo=TablaPrimero.i_perm;
                    id_usuario=TablaPrimero.i_uid;
                    fecha=TablaPrimero.i_atime;
                    if(TablaPrimero.i_type==0){
                        tipo="Carpeta";
                    }else{tipo="Archivo";}
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
                    }
                    //si no reconocio se sale de todo
                    if(reconocio==0){
                        std::cout<<"la Carpeta no existe no se puede insertar: "<<list1[posicion_Varios].toStdString()<<std::endl;
                        break;
                    }
                }
            }
        }

        //recorremos los usuario para ver sus permisos
        std::string StringUgo=std::to_string(Ugo);
        std::string Id_G="";
        std::string CadenaImprimir;
        std::cout << std::setw( 120 ) << std::setfill( '-' ) << '\n' << std::setfill( ' ' );
        std::cout << "| "<< std::left << std::setw(9) << "Lectura"
            << "| "<< std::left << std::setw(9) << "Escritura"
            << "| "<< std::left << std::setw(9) << "Ejecucion"
            << "|"<< std::left << std::setw(15) << "Usuario"
            << "|"<< std::left << std::setw(15) << "Grupo"
            << "|"<< std::left << std::setw(10) << "Hora"
            << "|"<< std::left << std::setw(9) << "Tipo"
            << "|"<< std::left << std::setw(13) << "Nombre"
            << "|"<<std::endl;
        std::cout << std::setw( 120 ) << std::setfill( '-' ) << '\n' << std::setfill( ' ' ) << '\n';
        std::fstream ficheroEntrada;
        QString frase;std::string linea;
        ficheroEntrada.open ( "teo/"+NombreParticion+"_Users.txt" , std::ios::in);
        while (! ficheroEntrada.eof() ) {
            getline (ficheroEntrada,linea);
            frase=QString::fromStdString(linea);
            //comprobacion si el usuario existe
            QStringList listaDatos =frase.split(',');
            if(listaDatos.count()>3){
                std::string lectura;
                std::string escritura;
                std::string ejecucion;
                //son usuarios empezamos a imprimir
                if(id_usuario==listaDatos[0].toInt()){
                    //permisos
                    std::cout<<"valdio"<<std::endl;
                    Id_G=listaDatos[2].toStdString();
                    if(StringUgo.compare(0, 1, "7")==0){
                        lectura="true";escritura="true";ejecucion="true";
                    }else if(StringUgo.compare(0, 1, "6")==0){
                        lectura="true";escritura="true";ejecucion="false";
                    }else if(StringUgo.compare(0, 1, "5")==0){
                        lectura="true";escritura="false";ejecucion="true";
                    }else if(StringUgo.compare(0, 1, "4")==0){
                        lectura="true";escritura="false";ejecucion="false";
                    }else if(StringUgo.compare(0, 1, "3")==0){
                        lectura="false";escritura="true";ejecucion="true";
                    }else if(StringUgo.compare(0, 1, "2")==0){
                        lectura="false";escritura="true";ejecucion="false";
                    }else if(StringUgo.compare(0, 1, "1")==0){
                        lectura="false";escritura="false";ejecucion="true";
                    }else if(StringUgo.compare(0, 1, "0")==0){
                        lectura="false";escritura="false";ejecucion="false";
                    }

                }else{
                    //si pertenecen la mismo grupo
                    if(Id_G.compare(listaDatos[2].toStdString())==0){
                        if(StringUgo.compare(1, 1, "7")==0){
                            lectura="true";escritura="true";ejecucion="true";
                        }else if(StringUgo.compare(1, 1, "6")==0){
                            lectura="true";escritura="true";ejecucion="false";
                        }else if(StringUgo.compare(1, 1, "5")==0){
                            lectura="true";escritura="false";ejecucion="true";
                        }else if(StringUgo.compare(1, 1, "4")==0){
                            lectura="true";escritura="false";ejecucion="false";
                        }else if(StringUgo.compare(1, 1, "3")==0){
                            lectura="false";escritura="true";ejecucion="true";
                        }else if(StringUgo.compare(1, 1, "2")==0){
                            lectura="false";escritura="true";ejecucion="false";
                        }else if(StringUgo.compare(1, 1, "1")==0){
                            lectura="false";escritura="false";ejecucion="true";
                        }else if(StringUgo.compare(1, 1, "0")==0){
                            lectura="false";escritura="false";ejecucion="false";
                        }
                    }else{
                         if(StringUgo.compare(2, 1, "7")==0){
                             lectura="true";escritura="true";ejecucion="true";
                         }else if(StringUgo.compare(2, 1, "6")==0){
                             lectura="true";escritura="true";ejecucion="false";
                         }else if(StringUgo.compare(2, 1, "5")==0){
                             lectura="true";escritura="false";ejecucion="true";
                         }else if(StringUgo.compare(2, 1, "4")==0){
                             lectura="true";escritura="false";ejecucion="false";
                         }else if(StringUgo.compare(2, 1, "3")==0){
                             lectura="false";escritura="true";ejecucion="true";
                         }else if(StringUgo.compare(2, 1, "2")==0){
                             lectura="false";escritura="true";ejecucion="false";
                         }else if(StringUgo.compare(2, 1, "1")==0){
                             lectura="false";escritura="false";ejecucion="true";
                         }else if(StringUgo.compare(2, 1, "0")==0){
                             lectura="false";escritura="false";ejecucion="false";
                         }
                    }
                }
                QString frase2=QString::fromStdString(ruta);
                //comprobacion si el usuario existe
                QStringList listaDatos2 =frase2.split('/');
                //imprimimos
                if(listaDatos[0].toInt()==1){
                    std::cout << "| "<< std::left << std::setw(9) << "true"
                        << "| "<< std::left << std::setw(9) << "true"
                        << "| "<< std::left << std::setw(9) << "true"
                        << "|"<< std::left << std::setw(15) << listaDatos[3].toStdString()
                        << "|"<< std::left << std::setw(15) << listaDatos[2].toStdString()
                        << "|"<< std::left << std::setw(10) << fecha
                        << "|"<< std::left << std::setw(9) <<tipo
                        << "|"<< std::left << std::setw(13) << listaDatos2[listaDatos2.size()-1].toStdString()
                        << "|"<<std::endl;
                }else{
                    if(listaDatos[0].compare("0")){
                        std::cout << "| "<< std::left << std::setw(9) << lectura
                            << "| "<< std::left << std::setw(9) << escritura
                            << "| "<< std::left << std::setw(9) << ejecucion
                            << "|"<< std::left << std::setw(15) << listaDatos[3].toStdString()
                            << "|"<< std::left << std::setw(15) << listaDatos[2].toStdString()
                            << "|"<< std::left << std::setw(10) << fecha
                            << "|"<< std::left << std::setw(9) <<tipo
                            << "|"<< std::left << std::setw(13) << listaDatos2[listaDatos2.size()-1].toStdString()
                            << "|"<<std::endl;
                    }
                }
            }
        }
        ficheroEntrada.close();


    }else{
        std::cout<<"La Particion No Existte"<<std::endl;
    }


}
