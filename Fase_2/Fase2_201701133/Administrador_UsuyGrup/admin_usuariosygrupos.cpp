#include "admin_usuariosygrupos.h"

Admin_UsuariosyGrupos::Admin_UsuariosyGrupos()
{
}
void Admin_UsuariosyGrupos::RecibirParametros(QList <std::string> P){
    Parametros.clear();
    this->Parametros=P;
}

void Admin_UsuariosyGrupos::Login(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    int CantidadObligatoria=0;

    std::string id=Analizador_C->id;
    std::string Usuario=Analizador_C->Usuario;
    std::string Password=Analizador_C->Password;
    //Validaciones
    if(id.length()!=0){CantidadObligatoria++;}
    if(Usuario.length()!=0){CantidadObligatoria++;}
    if(Password.length()!=0){CantidadObligatoria++;}

    if(CantidadObligatoria>=3){
        //buscar nombre de la particion
        std::string NombreParticion;
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id==temporalstring){
                NombreParticion=it2->Nombre;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        //banderas
        bool banderaUsuario=false;
        //busqueda
        std::fstream ficheroEntrada;
        QString frase;std::string linea;
        ficheroEntrada.open ( "teo/"+NombreParticion+"_Users.txt" , std::ios::in);
        while (! ficheroEntrada.eof() ) {
            getline (ficheroEntrada,linea);
            frase=QString::fromStdString(linea);

            //comprobacion si el usuario existe
            QStringList listaDatos =frase.split(',');
            if(listaDatos.count()>3){

                //son ususario
                if(listaDatos[3]==Usuario.c_str()){
                    std::cout<<"USUARIO: "<<Usuario<<std::endl;
                    if(listaDatos[4]==Password.c_str()){
                         std::cout<<"PASSWORD: "<<Password<<std::endl;
                         ID_Grupo=1;
                         ID_Usuario=listaDatos[0].toInt();
                         banderaUsuario=true;
                    }else{
                        std::cout<<"Contraseña Incorrecta"<<std::endl;
                    }
                }
            }else{

            }
        }

        if(banderaUsuario==false){
            std::cout<<"El Usuario no existe "<<Password<<std::endl;
        }else{
            this->UsuarioLog=Usuario.c_str();
            this->Id_Particion=id.c_str();
            std::cout<<"Se ha iniciado sesion Correctamente"<<std::endl;
        }

        ficheroEntrada.close();
        std::cin.get();
        QProcess::execute("clear");
    }else {
        std::cout<<"No Se Cumplieron Campos Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }
}

void Admin_UsuariosyGrupos::Logout(){
    if(UsuarioLog.length()!=0){
        this->UsuarioLog="";
        std::cout<<"Se ha cerrado sesion Correctamente"<<std::endl;
    }else{
        std::cout<<"No hay Sesion Activa"<<std::endl;
    }
    std::cin.get();
    QProcess::execute("clear");
}

void Admin_UsuariosyGrupos::CrearGrupo(){
    bool bandera_Insertar=false;
    int PosicionNuevo_Id=1;
    QString Nombre;
    int CantidadObligatoria=0;
    //Recorrer Lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2;
        s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           if(temporalstring2.length()>10){
               std::cout<<"El Nombre no puede tener mas de 10 Caracteres"<<std::endl;
           }else{
               CantidadObligatoria++;
               Nombre=temporalstring2.c_str();
           }
        }
    }
    if(CantidadObligatoria>=1){
        //comprobacion de sesion activa
        if(UsuarioLog =="root"){
            std::string rutaabrir;
            int PosicionStart;
            //obtener id siguiente y comproacion si ya existe
            //Buscar Nombre del archivo
            std::string NombreParticion;
            QList  <Nodo_Mount> :: iterator it2;
            for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
                std::string temporalstring=it2->Id;
                if(Id_Particion.toStdString()==temporalstring){
                    NombreParticion=it2->Nombre;
                    rutaabrir=it2->Ruta;
                    PosicionStart=it2->Posicion_Start;
                }
            }
            std::fstream ficheroEntrada;
            QString frase;std::string linea;
            ficheroEntrada.open ("teo/"+NombreParticion+"_Users.txt" , std::ios::in | std::ios::app | std::ios::out);
            while (! ficheroEntrada.eof() ) {
                getline (ficheroEntrada,linea);
                frase=QString::fromStdString(linea);

                //comprobacion si el grupo existe
                QStringList listaDatos =frase.split(',');
                if(listaDatos[1]=="G"){
                    if(PosicionNuevo_Id==listaDatos[0].toInt()){
                        PosicionNuevo_Id=listaDatos[0].toInt();
                        PosicionNuevo_Id++;
                    }
                    if(listaDatos[2]==Nombre){
                        bandera_Insertar=true;
                        break;
                    }
                }
            }
            ficheroEntrada.close();

            if(bandera_Insertar==false){;

                std::fstream outfile;
                outfile.open("teo/"+NombreParticion+"_Users.txt" , std::fstream :: app | std::fstream :: out);
                outfile <<"\n"<<PosicionNuevo_Id<<",G,"<<Nombre.toStdString();
                outfile.close();
                std::cout<<"Grupo: "<<Nombre.toStdString()<<std::endl;
                std::cout<<"Se ha Creado Correctamente"<<std::endl;

                //insertamos en el sistema de archivos
                std::string Cont=std::to_string(PosicionNuevo_Id)+",G,"+Nombre.toStdString();
                char con[60];
                strcpy(con,Cont.c_str());
                FILE *arch;
                arch=fopen(rutaabrir.c_str(),"r+b");
                if (arch==NULL){
                }else{
                    Super_Bloque Nodo_AP;
                    fseek(arch,PosicionStart,SEEK_SET);
                    fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
                    int pos_insertar=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo));
                    BloqueArchivo *NuevoBloque=new BloqueArchivo();

                    int bandera=NuevoBloque->Insertar_BloqueArchivo_Contenido(PosicionStart,rutaabrir,pos_insertar,con);
                    Nodo_AP.s_free_blocks_count-=bandera;
                    Nodo_AP.s_firts_blo+=bandera;
                    FILE *archivo;
                    if ((archivo = fopen(rutaabrir.c_str(),"r+b")) == NULL){
                        exit(1);
                    }
                    fseek(archivo,PosicionStart,SEEK_SET);
                    fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
                    fclose(archivo);
                    //insertamos en la bitacora
                    Bloque_Journali *BloqueJ=new Bloque_Journali();
                    char rutaenviar[60]="/Users.txt";
                    char Nombreenvio[11];
                     strcpy(Nombreenvio,Nombre.toStdString().c_str());
                    char tipoenvio[10]="Grupo";
                    char Descripcionenvio[25]="Crear Grupo";
                    BloqueJ->Insertar_BloqueJour(rutaabrir,PosicionStart,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);
               }

            }else{
                std::cout<<"Grupo: "<<Nombre.toStdString()<<std::endl;
                std::cout<<"El Grupo ya existe"<<std::endl;
            }

        }else{
            std::cout<<"No ha iniciado sesion con Usuario root"<<std::endl;
        }
    }else{
        std::cout<<"No se Cumplieron Caracteres Obliatorios"<<std::endl;
    }

    std::cin.get();
    QProcess::execute("clear");
}

void Admin_UsuariosyGrupos::EliminarGrupo(){
    bool bandera_Insertar=false;
    QString Nombre;
    int CantidadObligatoria=0;
    //Recorrer Lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2;
        s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           CantidadObligatoria++;
           Nombre=temporalstring2.c_str();
        }
    }
    if(CantidadObligatoria>=1){
        //Busqueda de nombre de la particion
        std::string ruta;
        int PosicionStart;
        std::string NombreParticion;
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(Id_Particion.toStdString()==temporalstring){
                NombreParticion=it2->Nombre;
                ruta=it2->Ruta;
                PosicionStart=it2->Posicion_Start;
            }
        }
        QString Contenido="";
        //comprobacion de sesion activa
        if(Nombre=="root"){
            std::cout<<"No se puede eliminar el Grupo root"<<std::endl;
        }else if(UsuarioLog =="root"){
            //obtener id siguiente y comproacion si ya existe
            std::fstream ficheroEntrada;
            QString frase;std::string linea;
            ficheroEntrada.open ("teo/"+NombreParticion+"_Users.txt" , std::ios::in | std::ios::app | std::ios::out);
            bool primerdato=true;
            while (! ficheroEntrada.eof() ) {
                getline (ficheroEntrada,linea);
                frase=QString::fromStdString(linea);
                //comprobacion si el usuario existe
                QStringList listaDatos =frase.split(',');
                if(listaDatos[1]=="G" || listaDatos[1]=="U"){
                    if(listaDatos[2]==Nombre){
                        if(listaDatos[1]=="G" ){
                            bandera_Insertar=true;
                            frase="0,G,"+Nombre;
                        }else{
                            frase="0,U,"+Nombre+","+listaDatos[3]+","+listaDatos[4];
                        }
                    }
                }


                if(primerdato){
                    primerdato=false;
                    Contenido.append(frase);
                }else{
                    Contenido.append("\n"+frase);
                }
                //para actualizar sistema de archivos
                char con[60];
                char anterior[60];
                QByteArray ba = frase.toLocal8Bit();
                const char *c_str2 = ba.data();
                strcpy(con,c_str2);
                strcpy(anterior,linea.c_str());

                FILE *arch;
                arch=fopen(ruta.c_str(),"r+b");
                if (arch==NULL){
                }else{
                    Super_Bloque Nodo_AP;
                    fseek(arch,PosicionStart,SEEK_SET);
                    fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
                    int pos_insertar=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo));
                    BloqueArchivo *NuevoBloque=new BloqueArchivo();
                    std::cout<<"Envio "<<linea<<std::endl;
                    NuevoBloque->Modificar_Users(PosicionStart,ruta,pos_insertar,con,anterior);
               }

            }
            ficheroEntrada.close();

            if(bandera_Insertar==false){;
                std::cout<<"Grupo: "<<Nombre.toStdString()<<std::endl;
                std::cout<<"El Grupo No Existe"<<std::endl;
            }else{
                std::fstream outfile;
                outfile.open("teo/"+NombreParticion+"_Users.txt" , std::fstream :: out);
                outfile <<Contenido.toStdString();
                outfile.close();
                //insertamos en la bitacora
                Bloque_Journali *BloqueJ=new Bloque_Journali();
                char rutaenviar[60]="/Users.txt";
                char Nombreenvio[11];
                 strcpy(Nombreenvio,Nombre.toStdString().c_str());
                char tipoenvio[10]="Grupo";
                char Descripcionenvio[25]="Eliminar Grupo";
                BloqueJ->Insertar_BloqueJour(ruta,PosicionStart,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);
                std::cout<<"Grupo: "<<Nombre.toStdString()<<std::endl;
                std::cout<<"Se ha Eliminado Correctamente"<<std::endl;
            }

        }else{
            std::cout<<"No ha iniciado sesion con Usuario root"<<std::endl;
        }
    }else{
        std::cout<<"No se Cumplieron Caracteres Obliatorios"<<std::endl;
    }

    std::cin.get();
    QProcess::execute("clear");
}

void Admin_UsuariosyGrupos::CrearUsuario(){
    std::string rutaabrir;
    int PosicionStart;
    //busqueda nombre particion
    std::string NombreParticion;
    QList  <Nodo_Mount> :: iterator it2;
    for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
        std::string temporalstring=it2->Id;
        if(Id_Particion.toStdString()==temporalstring){
            NombreParticion=it2->Nombre;
            rutaabrir=it2->Ruta;
            PosicionStart=it2->Posicion_Start;
        }
    }
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    bool BanderaGrupo=false;
    bool BanderaInsertar=false;
    int CantidadObligatoria=0;
    int PosicionNuevo_Id=1;
    std::string Grupo=Analizador_C->Grupo;
    std::string Usuario=Analizador_C->Usuario;
    std::string Password=Analizador_C->Password;
    //Validaciones
    if(Grupo.length()!=0){CantidadObligatoria++;}
    if(Usuario.length()!=0){CantidadObligatoria++;}
    if(Password.length()!=0){CantidadObligatoria++;}

    if(CantidadObligatoria>=3){
        //comprobacion de sesion activa
        if(UsuarioLog =="root"){

            //obtener id siguiente y comproacion si ya existe
            std::fstream ficheroEntrada;
            QString frase;std::string linea;
            ficheroEntrada.open ( "teo/"+NombreParticion+"_Users.txt" , std::ios::in | std::ios::app | std::ios::out);
            while (! ficheroEntrada.eof() ) {
                getline (ficheroEntrada,linea);
                frase=QString::fromStdString(linea);

                //comprobacion si el usuario existe
                QStringList listaDatos =frase.split(',');
                if(listaDatos[1]=="G"){
                    if(listaDatos[2]==Grupo.c_str() && listaDatos[0]!="0"){
                        BanderaGrupo=true;
                    }
                }else {
                    if(listaDatos[0]!="0"){
                        if(PosicionNuevo_Id==listaDatos[0].toInt()){
                            PosicionNuevo_Id=listaDatos[0].toInt();
                            PosicionNuevo_Id++;
                        }
                    }
                }
                //comprobacion si el usuario existe
                if(listaDatos.size()>3){
                    if(listaDatos[3]==Usuario.c_str()){
                        BanderaInsertar=true;
                    }
                }
            }
            ficheroEntrada.close();

            if(BanderaGrupo==true){
                if(BanderaInsertar==false){;

                    std::fstream outfile;
                    outfile.open("teo/"+NombreParticion+"_Users.txt" , std::fstream :: app | std::fstream :: out);  // does nothing
                    outfile <<"\n"<<PosicionNuevo_Id<<",U,"+Grupo+","+Usuario+","+Password;
                    outfile.close();
                    std::cout<<"Usuario: "+Usuario<<std::endl;
                    std::cout<<"Se ha Creado Correctamente"<<std::endl;
                    //insertamos en el sistema de archivos
                    std::string Cont=std::to_string(PosicionNuevo_Id)+",U,"+Grupo+","+Usuario+","+Password;
                    char con[60];
                    strcpy(con,Cont.c_str());
                    FILE *arch;
                    arch=fopen(rutaabrir.c_str(),"r+b");
                    if (arch==NULL){
                    }else{
                        Super_Bloque Nodo_AP;
                        fseek(arch,PosicionStart,SEEK_SET);
                        fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
                        int pos_insertar=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo));
                        BloqueArchivo *NuevoBloque=new BloqueArchivo();

                        int bandera=NuevoBloque->Insertar_BloqueArchivo_Contenido(PosicionStart,rutaabrir,pos_insertar,con);
                        Nodo_AP.s_free_blocks_count-=bandera;
                        Nodo_AP.s_firts_blo+=bandera;
                        FILE *archivo;
                        if ((archivo = fopen(rutaabrir.c_str(),"r+b")) == NULL){
                            exit(1);
                        }
                        fseek(archivo,PosicionStart,SEEK_SET);
                        fwrite(&Nodo_AP, sizeof(Super_Bloque), 1, archivo);
                        fclose(archivo);
                        //insertamos en la bitacora
                        Bloque_Journali *BloqueJ=new Bloque_Journali();
                        char rutaenviar[60]="/Users.txt";
                        char Nombreenvio[11];
                         strcpy(Nombreenvio,Usuario.c_str());
                        char tipoenvio[10]="Usuario";
                        char Descripcionenvio[25]="Crear Usuario";
                        BloqueJ->Insertar_BloqueJour(rutaabrir,PosicionStart,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

                   }

                }else{
                    std::cout<<"Usuario: "<<Usuario<<std::endl;
                    std::cout<<"El Usuario Ya Existe"<<std::endl;
                }
            }else{
                std::cout<<"Grupo: "<<Grupo<<std::endl;
                std::cout<<"El Grupo No existe"<<std::endl;
            }

        }else{
            std::cout<<"No ha iniciado sesion con Usuario root"<<std::endl;
        }
    }else{
        std::cout<<"No se Cumplieron Caracteres Obliatorios"<<std::endl;
    }

    std::cin.get();
    QProcess::execute("clear");
}

void Admin_UsuariosyGrupos::EliminarUsuario(){
    //busqeuda de nombre de la particion
    std::string NombreParticion;
    std::string ruta;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it2;
    for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
        std::string temporalstring=it2->Id;
        if(Id_Particion.toStdString()==temporalstring){
            NombreParticion=it2->Nombre;
            ruta=it2->Ruta;
            PosicionStart=it2->Posicion_Start;
        }
    }
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    bool BanderaInsertar=false;
    int CantidadObligatoria=0;
    std::string Usuario=Analizador_C->Usuario;
    //Validaciones
    if(Usuario.length()!=0){CantidadObligatoria++;}

    if(CantidadObligatoria>=1){
        //comprobacion de sesion activa
        if(Usuario=="root"){
            std::cout<<"No se puede eliminar el Usuario root"<<std::endl;
        }else if(UsuarioLog =="root"){
            //obtener id siguiente y comproacion si ya existe
            QString Contenido="";
            bool primerdato=true;
            std::fstream ficheroEntrada;
            QString frase;std::string linea;
            ficheroEntrada.open ("teo/"+NombreParticion+"_Users.txt" , std::ios::in | std::ios::app | std::ios::out);
            while (! ficheroEntrada.eof() ) {
                getline (ficheroEntrada,linea);
                frase=QString::fromStdString(linea);

                //comprobacion si el usuario existe
                QStringList listaDatos =frase.split(',');
                if(listaDatos.size()>3){
                    if(listaDatos[3]==Usuario.c_str() && listaDatos[0]!="0"){
                        BanderaInsertar=true;
                        frase="0,U,"+listaDatos[2]+","+listaDatos[3]+","+listaDatos[4];
                    }
                }

                if(primerdato){
                    primerdato=false;
                    Contenido.append(frase);
                }else{
                    Contenido.append("\n"+frase);
                }
                //para actualizar sistema de archivos
                char con[60];
                char anterior[60];
                QByteArray ba = frase.toLocal8Bit();
                const char *c_str2 = ba.data();
                strcpy(con,c_str2);
                strcpy(anterior,linea.c_str());

                FILE *arch;
                arch=fopen(ruta.c_str(),"r+b");
                if (arch==NULL){
                }else{
                    Super_Bloque Nodo_AP;
                    fseek(arch,PosicionStart,SEEK_SET);
                    fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
                    int pos_insertar=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo));
                    BloqueArchivo *NuevoBloque=new BloqueArchivo();
                    std::cout<<"Envio "<<linea<<std::endl;
                    NuevoBloque->Modificar_Users(PosicionStart,ruta,pos_insertar,con,anterior);
               }

            }
            ficheroEntrada.close();

            if(BanderaInsertar==true){;

                std::fstream outfile;
                outfile.open("teo/"+NombreParticion+"_Users.txt" , std::fstream :: out);
                outfile <<Contenido.toStdString();
                outfile.close();
                std::cout<<"Usuario: "+Usuario<<std::endl;
                std::cout<<"Se ha Eliminado Correctamente"<<std::endl;
                //insertamos en la bitacora
                Bloque_Journali *BloqueJ=new Bloque_Journali();
                char rutaenviar[60]="/Users.txt";
                char Nombreenvio[11];
                 strcpy(Nombreenvio,Usuario.c_str());
                char tipoenvio[10]="Usuario";
                char Descripcionenvio[25]="Eliminar Usuario";
                BloqueJ->Insertar_BloqueJour(ruta,PosicionStart,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

            }else{
                std::cout<<"Usuario: "<<Usuario<<std::endl;
                std::cout<<"El Usuario No Existe"<<std::endl;
            }
        }else{
            std::cout<<"No ha iniciado sesion con Usuario root"<<std::endl;
        }
    }else{
        std::cout<<"No se Cumplieron Caracteres Obliatorios"<<std::endl;
    }

    std::cin.get();
    QProcess::execute("clear");
}

void Admin_UsuariosyGrupos::Cambiar_Grupo(){
    //busqeuda de nombre de la particion
    std::string NombreParticion;
    std::string ruta;
    int PosicionStart;
    QList  <Nodo_Mount> :: iterator it2;
    for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
        std::string temporalstring=it2->Id;
        if(Id_Particion.toStdString()==temporalstring){
            NombreParticion=it2->Nombre;
            ruta=it2->Ruta;
            PosicionStart=it2->Posicion_Start;
        }
    }
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    bool BanderaInsertar=false;
    int CantidadObligatoria=0;
    std::string Usuario=Analizador_C->Usuario;
    std::string Grupo=Analizador_C->Grupo;
    //Validaciones
    if(Usuario.length()!=0){CantidadObligatoria++;}
    if(Grupo.length()!=0){CantidadObligatoria++;}
    if(CantidadObligatoria>=2){
        //comprobacion de sesion activa
        if(Usuario=="root"){
            std::cout<<"No se puede Cambiar el Usuario root"<<std::endl;
        }else if(UsuarioLog =="root"){
            //obtener id siguiente y comproacion si ya existe
            QString Contenido="";
            bool primerdato=true;
            std::fstream ficheroEntrada;
            QString frase;std::string linea;
            ficheroEntrada.open ("teo/"+NombreParticion+"_Users.txt" , std::ios::in | std::ios::app | std::ios::out);
            while (! ficheroEntrada.eof() ) {
                getline (ficheroEntrada,linea);
                frase=QString::fromStdString(linea);

                //comprobacion si el usuario existe
                QStringList listaDatos =frase.split(',');
                if(listaDatos.size()>3){
                    if(listaDatos[3]==Usuario.c_str() && listaDatos[0]!="0"){
                        BanderaInsertar=true;
                        frase=listaDatos[0]+",U,"+Grupo.c_str()+","+listaDatos[3]+","+listaDatos[4];
                    }
                }

                if(primerdato){
                    primerdato=false;
                    Contenido.append(frase);
                }else{
                    Contenido.append("\n"+frase);
                }
                //para actualizar sistema de archivos
                char con[60];
                char anterior[60];
                QByteArray ba = frase.toLocal8Bit();
                const char *c_str2 = ba.data();
                strcpy(con,c_str2);
                strcpy(anterior,linea.c_str());

                FILE *arch;
                arch=fopen(ruta.c_str(),"r+b");
                if (arch==NULL){
                }else{
                    Super_Bloque Nodo_AP;
                    fseek(arch,PosicionStart,SEEK_SET);
                    fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
                    int pos_insertar=Nodo_AP.s_inode_start+(sizeof (Tabla_Inodo));
                    BloqueArchivo *NuevoBloque=new BloqueArchivo();
                    std::cout<<"Envio "<<linea<<std::endl;
                    NuevoBloque->Modificar_Users(PosicionStart,ruta,pos_insertar,con,anterior);
               }

            }
            ficheroEntrada.close();

            if(BanderaInsertar==true){;

                std::fstream outfile;
                outfile.open("teo/"+NombreParticion+"_Users.txt" , std::fstream :: out);
                outfile <<Contenido.toStdString();
                outfile.close();
                std::cout<<"Usuario: "+Usuario<<std::endl;
                std::cout<<"Se ha Cambiado Correctamente"<<std::endl;
                //insertamos en la bitacora
                Bloque_Journali *BloqueJ=new Bloque_Journali();
                char rutaenviar[60]="/Users.txt";
                char Nombreenvio[11];
                 strcpy(Nombreenvio,Usuario.c_str());
                char tipoenvio[10]="Usuario";
                char Descripcionenvio[25]="Cambiar Grupo";
                BloqueJ->Insertar_BloqueJour(ruta,PosicionStart,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

            }else{
                std::cout<<"Usuario: "<<Usuario<<std::endl;
                std::cout<<"El Usuario No Existe"<<std::endl;
            }
        }else{
            std::cout<<"No ha iniciado sesion con Usuario root"<<std::endl;
        }
    }else{
        std::cout<<"No se Cumplieron Caracteres Obliatorios"<<std::endl;
    }

    std::cin.get();
    QProcess::execute("clear");
}
//comparador
int Admin_UsuariosyGrupos::case_insensitive_match(std::string s1, std::string s2) {
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings son iguales
   return 0; //no son iguales
}

