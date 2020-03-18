#include "admin_disco.h"

Admin_Disco::Admin_Disco()
{
    this->AdminParticion=new Admin_Particiones();
}
void Admin_Disco::RecibirParametros(QList <std::string> P){
    Parametros.clear();
    this->Parametros=P;
    QList  <std::string> :: iterator it;
//    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
//        std::string temporalstring=*it;
//        std::cout <<temporalstring<<" Cantidad de Caracteres: "<<temporalstring.size()<<std::endl;
//    }
}
void Admin_Disco::CrearArchivo(){
    //cadena para crear disco
    std::string CadenaComando=" dd if=/dev/zero of=";
    std::string CadenaComandoRAID=" dd if=/dev/zero of=";
    std::string ruta;
    std::string rutaRAID;
    //datos default en el struct mbr disco
    char fit[3]="FF";
    int Asignaturamdom = rand() % 100;
    int tamaniobytes=1048576;
    int tamanio=1;

    //fecha
    char tiempo[9];
    time_t current_time;
    struct tm * time_info;
    char timeString[9];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
    strcpy(tiempo,timeString);


    //validaciones
    int cantObliatoria=0;
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        //CREACION DEL DISCO

        std::string s2;
        s2 = "SIZE";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObliatoria++;

           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           int valor=std::stoi(temporalstring2);
           if(valor>0){
               std::cout << "Valor "<<valor<<std::endl;
               tamanio=valor;
           }else{
               cantObliatoria--;
               std::cout << "TAMANIO MENOR A 0: "<<temporalstring2<<std::endl;
           }
        }

        s2 = "PATH";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObliatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           ruta=*it2;
        }

        s2 = "FIT";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           if(temporalstring2=="FF"||temporalstring2=="BF"||temporalstring2=="WF"){
               strcpy(fit,temporalstring2.c_str());
           }else{
               std::cout << "NO SE ACEPTO FIT "<<temporalstring2<<std::endl;
           }
        }

        s2 = "UNIT";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;

           if(temporalstring2=="k" || temporalstring2=="K"){
               tamaniobytes=tamaniobytes/1024;
           }else{
               if(temporalstring2=="m" || temporalstring2=="M"){
               }else{
                   if(temporalstring2=="b" || temporalstring2=="B"){
                       tamaniobytes=tamaniobytes/1048576;
                   }else{
                       std::cout << "ERROR FORMATO INCORRECTO UNIT"<<temporalstring2<<std::endl;
                   }
               }
           }
        }


    }
    if(cantObliatoria>=2){
        //creacion de ruta
        QString qstr = QString::fromStdString(ruta);
        QStringList list1 = qstr.split('/');
        QString s;
        for( int i=0; i<list1.size(); i++ ){
            if(i!=list1.size()-1){
                s+=list1.at(i);
                QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
                s+="/";
            }
        }

        std::string rutacomando="";
        for(int a=0;a<ruta.size();a++){
            if(int(ruta.at(a))==32){
                rutacomando+="\\ ";
                ruta.at(a);
                //para raid
                rutaRAID+="\\ ";
                rutaRAID.at(a);
            }else{
                if(int(ruta.at(a))==46){
                    rutaRAID+="_ra1";
                }
                rutaRAID+=ruta.at(a);
                rutacomando+=ruta.at(a);
            }

        }
        CadenaComando+=rutacomando;
        CadenaComando+=" bs=";
        CadenaComando+=std::to_string(tamaniobytes*tamanio);
        CadenaComando+=" count=1";
        //para raid
        CadenaComandoRAID+=rutaRAID;
        CadenaComandoRAID+=" bs=";
        CadenaComandoRAID+=std::to_string(tamaniobytes*tamanio);
        CadenaComandoRAID+=" count=1";


        //Insertar Struct
        strcpy(this->nuevo.fisk_fit,fit);
        strcpy(this->nuevo.mbr_fecha_creacion,tiempo);
        this->nuevo.mbr_tamanio=tamaniobytes*tamanio;
        this->nuevo.mbr_disk_asignature=Asignaturamdom;
        std::cout<<this->nuevo.fisk_fit<<std::endl;
        std::cout<<this->nuevo.mbr_fecha_creacion<<std::endl;
        std::cout<<tamaniobytes*tamanio<<std::endl;
        std::cout<<Asignaturamdom<<std::endl;
        strcpy( this->nuevo.mbr_partition_1.part_status,"N");
        strcpy( this->nuevo.mbr_partition_2.part_status,"N");
        strcpy( this->nuevo.mbr_partition_3.part_status,"N");
        strcpy( this->nuevo.mbr_partition_4.part_status,"N");
        //creacion .disk
        system(CadenaComando.c_str());
        system(CadenaComandoRAID.c_str());
        FILE *archivo;
        char nameruta[100];
        strcpy(nameruta,ruta.c_str());
        if ((archivo = fopen(nameruta,"r+b")) == NULL){
            exit(1);
        }else{
            fseek(archivo,0,SEEK_SET);
            fwrite(&this->nuevo, sizeof(MBR_Disco), 1, archivo);
            fclose(archivo);
            std::cout << "SE CREO ARCHIVO CORRECTAMENTE: "<< nameruta<<std::endl;
            std::cin.get();
            QProcess::execute("clear");
        }

    }else{
        std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS--CREACION ARCHIVO"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }


}

void Admin_Disco::EliminarArchivo(){
    //comprobacion de ruta
    int cantObligatoria=0;
    std::string ruta;
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "PATH";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           ruta=*it2;
        }
    }
    if(cantObligatoria>=1){
        std::cout<<"DESEA ELIMINAR EL ARCHIVO "<<ruta<<std::endl;
        std::cout<<"1.SI"<<std::endl;
        std::cout<<"2.NO"<<std::endl;
        int opcion;
        std::cin >>opcion;
        if(opcion==1){
            if( std::remove( ruta.c_str() )!=0 ){
                std::cout<<"El Disco no existe "<<std::endl;
            }else{
                std::cout<<"Disco Eliminado"<<std::endl;
            }
        }
        std::cin.get();
    }else{
        std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }
}

void Admin_Disco::Reporte(){

    //datos reporte
    std::string tiponombre="";
    std::string ruta;
    std::string id;
    int cantObligatoria=0;
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           if(case_insensitive_match(temnombre, "mbr") ){
               cantObligatoria++;
               tiponombre="mbr";
           }else{
               if(case_insensitive_match(temnombre, "disk") ){
                   cantObligatoria++;
                   tiponombre="disk";
               }else{
                   std::cout <<"Nombre Incorrecto debe ser disk o mbr"<<std::endl;
               }
           }
        }

         s2 = "PATH";
         if(case_insensitive_match(temporalstring, s2)) {
            cantObligatoria++;
            //insertamos contenido
            QList  <std::string> :: iterator it2=std::next(it);
            ruta=*it2;
         }

        s2 = "ID";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           id=temnombre;
        }
    }
    if(cantObligatoria>=3){
        std::string rutaarir;
        if(tiponombre=="mbr"){
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

        if(tiponombre=="disk"){
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
    }else{
        std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS"<<std::endl;
    }
}

void Admin_Disco::EventoParticion(){
    AdminParticion->RecibirParametros(Parametros);
    this->TamanioMBRDisco=sizeof (MBR_Disco);
    AdminParticion->TamanioMBRDisk=this->TamanioMBRDisco;

    std::string ruta;
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "PATH";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           ruta=it2->c_str();
        }
    }
    FILE *arch;
    arch=fopen(ruta.c_str(),"r+b");
    if (arch==NULL){
        exit(1);
    }else{
        //abrir archivo para raid
        std::string rutaraid;
        for(int u=0;u<ruta.size();u++){
            if(int(ruta.at(u))==46){
                rutaraid+="_ra1";
            }
            rutaraid+=ruta.at(u);

        }

        FILE *archRAID;
        archRAID=fopen(rutaraid.c_str(),"r+b");
        if (archRAID==NULL){
            exit(1);
        }
        MBR_Disco Nodo_AP;
        fread(&Nodo_AP, sizeof(MBR_Disco), 1, arch);
        AdminParticion->ArregloMBR[0]=Nodo_AP.mbr_partition_1;
        AdminParticion->ArregloMBR[1]=Nodo_AP.mbr_partition_2;
        AdminParticion->ArregloMBR[2]=Nodo_AP.mbr_partition_3;
        AdminParticion->ArregloMBR[3]=Nodo_AP.mbr_partition_4;
        strcpy(AdminParticion->fitdisk,Nodo_AP.fisk_fit);
        AdminParticion->EventoParticion();
        MBR_Particion carga=AdminParticion->RetornarParticionInsertada();
        int pos=AdminParticion->Retornopos();
        //no insertar
        //-1 no insertar
        //0,1,2,3 insertar
        //-2(3) -3(2) -4(1) -5(0)


        if(pos==-1){
        }else{
            if(pos==0){
                Nodo_AP.mbr_partition_1=carga;
            }
            if(pos==1){
                Nodo_AP.mbr_partition_2=carga;
            }
            if(pos==2){
                Nodo_AP.mbr_partition_3=carga;
            }
            if(pos==3){
                Nodo_AP.mbr_partition_4=carga;
            }
            //los de eliminar fast
            if(pos==-5){
                Nodo_AP.mbr_partition_1=carga;
            }
            if(pos==-4){
                Nodo_AP.mbr_partition_2=carga;
            }
            if(pos==-3){
                Nodo_AP.mbr_partition_3=carga;
            }
            if(pos==-2){
                Nodo_AP.mbr_partition_4=carga;
            }


            int posi=ftell(arch)-sizeof(MBR_Disco);
            fseek(arch,posi,SEEK_SET);
            fwrite(&Nodo_AP, sizeof(MBR_Disco), 1, arch);
            //para RAID
            fseek(archRAID,posi,SEEK_SET);
            fwrite(&Nodo_AP, sizeof(MBR_Disco), 1, archRAID);

        }
        fclose(arch);
        fclose(archRAID);

    }


}

void Admin_Disco::Montar(){
    int cantObligatoria=0;
    std::string ruta;
    std::string rutainsertar=ruta;
    std::string name;
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;
        std::string s2 = "PATH";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           ruta=*it2;
           FILE *archivo;
           if ((archivo = fopen(ruta.c_str(),"r+b")) == NULL){
              cantObligatoria--;
              exit(1);
              std::cout<<"El archivo no existe"<<std::endl;
           }
        }
        s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           name=*it2;
        }
    }
    if(cantObligatoria>=2){
        std::cout<<name<<std::endl;
        bool Encontrado=false;
        int caracter=97;
        int posicion=1;
        QList  <Nodo_Mount> :: iterator it2;

        //encontrar ruta
        bool rutaexiste=false;
        for(it2 = this->RutaCantidad.begin(); it2 != this->RutaCantidad.end(); ++it2){

            //comproacion si ya hay una ruta
            std::string temporalstring2=it2->Ruta;
            if(ruta==temporalstring2){
                rutaexiste=true;
                break;
            }else{
                caracter++;
            }
        }

        Nodo_Mount *nuevoruta=new Nodo_Mount();
        nuevoruta->Ruta=ruta;
        if(rutaexiste==false){

            //comprobamos si contiene la particion
            bool Encontrar_Particion=false;
            FILE *arch;
            arch=fopen(ruta.c_str(),"r+b");
            if (arch==NULL){
                exit(1);
            }else{
                MBR_Disco Nodo_AP;
                fread(&Nodo_AP, sizeof(MBR_Disco), 1, arch);
                char validacion_part_name;
                strcpy(&validacion_part_name, name.c_str());
                if(strcmp(Nodo_AP.mbr_partition_1.part_name,&validacion_part_name)== 0 || strcmp(Nodo_AP.mbr_partition_2.part_name,&validacion_part_name)== 0 || strcmp(Nodo_AP.mbr_partition_3.part_name,&validacion_part_name)== 0 ||strcmp(Nodo_AP.mbr_partition_4.part_name,&validacion_part_name)== 0){
                    Encontrar_Particion=true;
                }
            }


            if(Encontrar_Particion==true){
                //agregar ruta
                this->RutaCantidad.append(*nuevoruta);
                //insertamos
                posicion=1;
                std::string nuevonodo="vd";
                char car = char(caracter);
                nuevonodo+=car;
                nuevonodo+=std::to_string(posicion);
                Nodo_Mount *nuevo=new Nodo_Mount();
                nuevo->Id=nuevonodo;
                nuevo->cantidad=posicion;
                nuevo->Ruta=ruta;
                nuevo->Nombre=name;
                this->Lista_Montaje.append(*nuevo);
                std::cout <<"Insertado: "<<nuevonodo<<std::endl;

            }else{
               std::cout <<"La Particion no existe: "<<name<<std::endl;
            }

        }else{
            QList  <Nodo_Mount> :: iterator it3;
            //encontrar id y cantidad
            for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){

                std::string temporalstring2=it3->Nombre;
                std::string temruta=it3->Ruta;
                //comprobamos si ya esta montado
                if(temruta==ruta){
                    //comprobacion de posicion
                    if(temporalstring2==name){
                        Encontrado=true;
                        break;
                    }else{
                        //comprobacion de posicion
                        if(it3->cantidad>posicion){
                            posicion=it3->cantidad;
                        }
                    }
                }
            }
            if(Encontrado==false){
                posicion++;
                std::string nuevonodo="vd";
                char car = char(caracter);
                nuevonodo+=car;
                nuevonodo+=std::to_string(posicion);
                Nodo_Mount *nuevo=new Nodo_Mount();
                nuevo->cantidad=posicion;
                nuevo->Id=nuevonodo;
                nuevo->Ruta=ruta;
                nuevo->Nombre=name;
                this->Lista_Montaje.append(*nuevo);
                std::cout <<"Insertado: "<<nuevonodo<<std::endl;


            }else{
                 std::cout <<"La particion ya se encuentra montada"<<std::endl;
            }
        }


    }
    //MUESTRA LISTADO DE MONTADOS
    QList  <Nodo_Mount> :: iterator it9;
    //encontrar id y cantidad
    std::cout<<"PARTICIONES Y DISCOS MONTADO"<<std::endl;
    for(it9 = this->Lista_Montaje.begin(); it9 != this->Lista_Montaje.end(); ++it9){
        std::string datomontado=it9->Id;
        std::cout<<datomontado<<" Nombre: "<< it9->Nombre<<std::endl;

    }
    std::cin.get();
    QProcess::execute("clear");
}

void Admin_Disco::Desmontar(){
    std::string id;
    int CantidadObligatoria=0;
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;
        std::string s2 = "ID";
        if(case_insensitive_match(temporalstring, s2)) {
            CantidadObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           id=*it2;
        }

    }

    if(CantidadObligatoria>=1){
        //comprobamos si existe
        bool bandera=false;
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id==temporalstring){
                bandera=true;
                std::cout<<"DESEA DESMONTAR "<<temporalstring<<std::endl;
                std::cout<<"1.SI"<<std::endl;
                std::cout<<"2.NO"<<std::endl;
                int opcion;
                std::cin >>opcion;
                if(opcion==1){
                    it2 = Lista_Montaje.erase(it2);
                }
                break;
            }
        }

        if(bandera==false){
            std::cout<<"El ID No Existe"<<std::endl;
        }
        //MUESTRA LISTADO DE MONTADOS
        QList  <Nodo_Mount> :: iterator it9;
        //encontrar id y cantidad
        std::cout<<"PARTICIONES Y DISCOS MONTADO"<<std::endl;
        for(it9 = this->Lista_Montaje.begin(); it9 != this->Lista_Montaje.end(); ++it9){
            std::string datomontado=it9->Id;
            std::cout<<datomontado<<" Nombre: "<< it9->Nombre<<std::endl;

        }
        std::cin.get();
        QProcess::execute("clear");
    }else{
        std::cout<<"No Se Cumplieron Campos Obligatorios"<<std::endl;
    }
}

//comparador
int Admin_Disco::case_insensitive_match(std::string s1, std::string s2) {
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings son iguales
   return 0; //no son iguales
}
