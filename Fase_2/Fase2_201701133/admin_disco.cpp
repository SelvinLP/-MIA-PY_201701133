#include "admin_disco.h"

Admin_Disco::Admin_Disco()
{
    this->AdminParticion=new Admin_Particiones();
}
void Admin_Disco::RecibirParametros(QList <std::string> P){
    Parametros.clear();
    this->Parametros=P;
}
void Admin_Disco::CrearArchivo(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    //cadena para crear disco
    std::string CadenaComando=" dd if=/dev/zero of=";
    std::string CadenaComandoRAID=" dd if=/dev/zero of=";
    std::string ruta=Analizador_C->ruta;
    std::string rutaRAID;
    //datos default en el struct mbr disco
    char fit[3]; strcpy(fit, Analizador_C->fit);
    int Asignaturamdom = rand() % 100;
    int tamaniobytes=Analizador_C->tamaniobytes;
    int tamanio=Analizador_C->tamanio;
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
    if(tamanio>0){cantObliatoria++;}
    if(ruta.length()!=0){cantObliatoria++;}

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
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    //comprobacion de ruta
    int cantObligatoria=0;
    std::string ruta=Analizador_C->ruta;
    //validaciones
    if(ruta.length()!=0){cantObligatoria++;}

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
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    //datos reporte
    std::string tiponombre=Analizador_C->tiponombre;
    std::string ruta=Analizador_C->ruta;
    std::string id=Analizador_C->id;
    std::string rutabuscar=Analizador_C->rutaReporte;
    int cantObligatoria=0;
    //Validaciones
    if(ruta.length()!=0){cantObligatoria++;}
    if(tiponombre.length()!=0){cantObligatoria++;}
    if(id.length()!=0){cantObligatoria++;}

    if(cantObligatoria>=3){
        std::string rutaarir;
        Graficar_Reportes *reportes=new Graficar_Reportes();
        reportes->Lista_Montaje=this->Lista_Montaje;
        reportes->Id_Loss=Id_Loss;
        if(tiponombre=="mbr"){
            reportes->Graficar_Mbr(rutaarir,id,ruta);
        }
        if(tiponombre=="disk"){
            reportes->Graficar_Disk(rutaarir,id,ruta);
        }
        if(tiponombre=="sb"){
            reportes->Graficar_Sb(rutaarir,id,ruta);
        }
        if(tiponombre=="bm_inode"){
            reportes->Graficar_bm(rutaarir,id,ruta,0);
        }
        if(tiponombre=="bm_block"){
            reportes->Graficar_bm(rutaarir,id,ruta,1);
        }
        if(tiponombre=="tree"){
            reportes->Graficar_tree(rutaarir,id,ruta);
        }
        if(tiponombre=="inode"){
            reportes->Graficar_inode(rutaarir,id,ruta);
        }
        if(tiponombre=="block"){
            reportes->Graficar_block(rutaarir,id,ruta);
        }
        if(tiponombre=="file"){
            reportes->Graficar_file(rutaarir,id,ruta,rutabuscar);
        }
        if(tiponombre=="journaling"){
            reportes->Graficar_Journaling(rutaarir,id,ruta);
        }
        if(tiponombre=="ls"){
            reportes->Graficar_Ls(rutaarir,id,rutabuscar);
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
        unsigned long long int  Posicion_Start;
        unsigned long long int  Particion_Size;
        nuevoruta->Ruta=ruta;
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
            if(strcmp(Nodo_AP.mbr_partition_1.part_name,&validacion_part_name)== 0 ){
                Encontrar_Particion=true;
                Posicion_Start=Nodo_AP.mbr_partition_1.part_start;
                Particion_Size=Nodo_AP.mbr_partition_1.part_size;
            }else if( strcmp(Nodo_AP.mbr_partition_2.part_name,&validacion_part_name)== 0){
                Encontrar_Particion=true;
                Posicion_Start=Nodo_AP.mbr_partition_2.part_start;
                Particion_Size=Nodo_AP.mbr_partition_2.part_size;
            }else if(strcmp(Nodo_AP.mbr_partition_3.part_name,&validacion_part_name)== 0){
                Encontrar_Particion=true;
                Posicion_Start=Nodo_AP.mbr_partition_3.part_start;
                Particion_Size=Nodo_AP.mbr_partition_3.part_size;
            }else if(strcmp(Nodo_AP.mbr_partition_4.part_name,&validacion_part_name)== 0){
                Encontrar_Particion=true;
                Posicion_Start=Nodo_AP.mbr_partition_4.part_start;
                Particion_Size=Nodo_AP.mbr_partition_4.part_size;
            }

        }
        if(rutaexiste==false){

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
                nuevo->Posicion_Start=Posicion_Start;
                nuevo->Particion_Size=Particion_Size;
                this->Lista_Montaje.append(*nuevo);
                //modificamos el superbloque
                SuperBloque *bloque =new SuperBloque();
                bloque->EventoMount(ruta,Posicion_Start,0);
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
                        if(it3->cantidad==posicion){
                            posicion=(it3->cantidad)+1;
                        }
                    }
                }
            }
            //encontrar poicion del disco y tamaño
            if(Encontrado==false){
                std::string nuevonodo="vd";
                char car = char(caracter);
                nuevonodo+=car;
                nuevonodo+=std::to_string(posicion);
                Nodo_Mount *nuevo=new Nodo_Mount();
                nuevo->cantidad=posicion;
                nuevo->Id=nuevonodo;
                nuevo->Ruta=ruta;
                nuevo->Nombre=name;
                nuevo->Posicion_Start=Posicion_Start;
                nuevo->Particion_Size=Particion_Size;
                this->Lista_Montaje.append(*nuevo);
                //modificamos el superbloque
                SuperBloque *bloque =new SuperBloque();
                bloque->EventoMount(ruta,Posicion_Start,0);
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
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    std::string id=Analizador_C->id;
    int CantidadObligatoria=0;
    //Validaciones
    if(id.length()!=0){CantidadObligatoria++;}

    if(CantidadObligatoria>=1){
        //comprobamos si existe
        bool bandera=false;
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            std::string temruta=it2->Ruta;

            if(id==temporalstring){
                bandera=true;
                std::cout<<"DESEA DESMONTAR "<<temporalstring<<std::endl;
                std::cout<<"1.SI"<<std::endl;
                std::cout<<"2.NO"<<std::endl;
                int opcion;
                std::cin >>opcion;
                if(opcion==1){
                    it2 = Lista_Montaje.erase(it2);
                    //modificamos el superbloque
                    SuperBloque *bloque =new SuperBloque();
                    bloque->EventoMount(it2->Ruta,it2->Posicion_Start,1);
                    //recorremos si el dato montado solo es uno en caso de que sea se borra la ruta en la otra lista
                    QList  <Nodo_Mount> :: iterator it3;
                    bool Encontrado=false;
                    for(it3 = this->Lista_Montaje.begin(); it3 != this->Lista_Montaje.end(); ++it3){
                        //si la ruta no exite se elimina de la lista de rutas
                        std::string temporalRuta=it2->Ruta;
                        if(temruta==temporalRuta){
                            Encontrado=true;
                            break;
                        }

                    }
                    //eliminacion
                    if(Encontrado==false){
                        QList  <Nodo_Mount> :: iterator it4;
                        for(it4 = this->RutaCantidad.begin(); it4 != this->RutaCantidad.end(); ++it4){
                            std::string teRuta=it4->Ruta;
                            if(teRuta==temruta){
                                it4 = Lista_Montaje.erase(it4);
                                break;
                            }
                        }

                    }
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

void Admin_Disco::FormateoEXT(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    std::string id=Analizador_C->id;
    std::string Tipo_Formateo="full";
    QString FormatoFS="2";
    int CantidadObligatoria=0;
    //Validaciones
    if(id.length()!=0){CantidadObligatoria++;}
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "TYPE";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           if(case_insensitive_match(temporalstring2,"fast")){
               Tipo_Formateo="fast";
           }else if(case_insensitive_match(temporalstring2,"full")){
               Tipo_Formateo="full";
           }else{
               std::cout<<"Formato TYPE Incorrecto"<<std::endl;
           }

        }
        s2 = "FS";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           if(case_insensitive_match(temporalstring2,"2fs") || temporalstring2=="2"){
               FormatoFS="2";
           }else if(case_insensitive_match(temporalstring2,"3fs") || temporalstring2=="3"){
               FormatoFS="3";
           }else{
               std::cout<<"Formato FS Incorrecto"<<std::endl;
           }
        }

    }
    if(CantidadObligatoria>=1){
        //Creacion Carpeta Users
        QString s="teo";
        unsigned long long int  Posicion_Start;
        unsigned long long int  Posicion_Size;
        QDir dir(s); if (!dir.exists()) { dir.mkpath("."); }
        std::string ruta;
        QString nombre;
        if(case_insensitive_match(Tipo_Formateo, "FAST")||case_insensitive_match(Tipo_Formateo, "FULL")) {
            //Busca el id y obtiene la ruta
            QList  <Nodo_Mount> :: iterator it;
            for(it = this->Lista_Montaje.begin(); it != this->Lista_Montaje.end(); ++it){
                std::string tempotalString=it->Id;
                if(tempotalString==id){
                   ruta=it->Ruta;
                   std::cout<<"ruta: "+ruta<<std::endl;
                   nombre=it->Nombre.c_str();
                   it->Fs=FormatoFS.toStdString();
                   Posicion_Start=it->Posicion_Start;
                   Posicion_Size=it->Particion_Size;
                }
            }

            //Creacion del archivo Users.txt
            std::ofstream file;
            file.open("teo/"+nombre.toStdString()+"_Users.txt");
            file <<"1,G,root\n";
            file <<"1,U,root,root,123";
            file.close();

            //insertamos Super Bloqe en disk
            SuperBloque *SuperB=new SuperBloque();
            SuperB->InsertarBloque(ruta,FormatoFS.toInt(),Posicion_Start,Posicion_Size);
            //insertar carpeta user.txt
            BloqueArchivo *Bloque_nuevo=new BloqueArchivo();
            Bloque_nuevo->Busqueda_Archivo(ruta,Posicion_Start,"Users.txt",20,"teo/"+nombre.toStdString()+"_Users.txt",0);
            //si es ext3 crear en bitacora
            if(FormatoFS.toInt()==3){
                //tipo si es 0 es Carpeta
                //1 es Archivo
                FILE *arch;
                arch=fopen(ruta.c_str(),"r+b");
                if (arch==NULL){
                }else{
                    //cambio el actual a 0 y el nuevo le ponto 1
                    Super_Bloque Nodo_AP;
                    fseek(arch,Posicion_Start,SEEK_SET);
                    fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);

                    Nodo_Journaling nuevo;
                    nuevo.Ultimo=1;
                    strcpy(nuevo.ruta,"/Users.txt");
                    nuevo.size=64;
                    strcpy(nuevo.tipo,"Grupo");
                    strcpy(nuevo.Nombre,"root");
                    //fecha
                    time_t current_time;
                    struct tm * time_info;
                    char timeString[9];
                    time(&current_time);
                    time_info = localtime(&current_time);
                    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
                    strcpy(nuevo.mtime,timeString);
                    strcpy(nuevo.Descripcion,"Crear Grupo");
                    fseek(arch,Nodo_AP.s_block_start*Nodo_AP.s_blocks_count,SEEK_SET);
                    fwrite(&nuevo, sizeof(Nodo_Journaling), 1, arch);
                    fclose(arch);
                }
                //segundo dato
                Bloque_Journali *BloqueJ=new Bloque_Journali();
                char rutaenviar[60]="/Users.txt";
                char tipoenvio[10]="Usuario";
                char Nombreenvio[11]="root";
                char Descripcionenvio[25]="Crear Usuario";
                BloqueJ->Insertar_BloqueJour(ruta,Posicion_Start,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);
            }
            std::cout<<"Creado Archivo User.txt de:"<<id<<std::endl;
            std::cout<<"Insertado Super Bloque en Particion: "+nombre.toStdString()<<std::endl;
            std::cin.get();
            QProcess::execute("clear");
        }
    }else{
        std::cout<<"No Cumple con requisitos Minimos"<<std::endl;
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
