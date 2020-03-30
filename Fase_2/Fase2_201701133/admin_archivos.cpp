#include "admin_archivos.h"

Admin_Archivos::Admin_Archivos()
{

}
void Admin_Archivos::RecibirParametros(QList <std::string> P){
    Parametros.clear();
    this->Parametros=P;
}
void Admin_Archivos::Ejecutar_CHMOD(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    //comprobacion de ruta
    int cantObligatoria=0;
    int ugo=Analizador_C->ugo;
    std::string path=Analizador_C->ruta;
    std::string R=Analizador_C->R;
    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;

    if(path.length()!=0){cantObligatoria++;}
    if(ugo!=0){cantObligatoria++;}
    if(cantObligatoria>=2){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        if(R.length()!=0){
            //es recursivo
            QString qstr = QString::fromStdString(path);
            QStringList list1 = qstr.split('/');
            QString Contenido;
            for(int posicion=0;posicion<list1.size();posicion++){

                Contenido.append(list1[posicion]);
                Permisos *Nuevo_Permiso=new Permisos();
                Nuevo_Permiso->Cambio_Permisos(Ruta_Particion,Posicion_Inicio_Particion,Contenido.toStdString(),ID_Usuario,ugo);
                Contenido.append("/");
            }
        }else{
            //no es recursivo
            Permisos *Nuevo_Permiso=new Permisos();
            Nuevo_Permiso->Cambio_Permisos(Ruta_Particion,Posicion_Inicio_Particion,path,ID_Usuario,ugo);
        }
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char Nombreenvio[11]="";
        QString qstr = QString::fromStdString(path);
        QStringList list1 = qstr.split('/');
        QString Contenido;
        strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        char rutaenviar[60]="";
        char tipoenvio[10]="A o C";
        char Descripcionenvio[25]="Cambio de Permisos";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

        std::cin.get();
        QProcess::execute("clear");
    }else{
        std::cout<<"No Se Cumpleron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }
}

void Admin_Archivos::Ejecutar_CHOWN(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    //comprobacion de ruta
    int cantObligatoria=0;
    std::string path=Analizador_C->ruta;
    std::string R=Analizador_C->R;
    std::string user=Analizador_C->Usuario;
    int ID_nueva;

    std::string id_montura;
    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;

    if(path.length()!=0){cantObligatoria++;}
    if(user.length()!=0){cantObligatoria++;}
    if(cantObligatoria>=2){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
                id_montura=it2->Nombre;
            }
        }
        //obtenemos id del usuario
        std::fstream ficheroEntrada;
        QString frase;std::string linea;
        ficheroEntrada.open ( "teo/"+id_montura+"_Users.txt" , std::ios::in);
        while (! ficheroEntrada.eof() ) {
            getline (ficheroEntrada,linea);
            frase=QString::fromStdString(linea);
            //comprobacion si el usuario existe
            QStringList listaDatos =frase.split(',');
            if(listaDatos.count()>3){
                if(listaDatos[3].toStdString().compare(user.c_str())==0){
                    ID_nueva=listaDatos[0].toInt();
                }

            }
        }
        ficheroEntrada.close();
        //cambios
        std::cout<<"Ruta a Modificar Usuario: "<<path<<std::endl;
        std::cout<<"Usuario: "<<user<<std::endl;
        if(R.length()!=0){
            //es recursivo
            QString qstr = QString::fromStdString(path);
            QStringList list1 = qstr.split('/');
            QString Contenido;
            for(int posicion=0;posicion<list1.size();posicion++){

                Contenido.append(list1[posicion]);
                Permisos *Nuevo_Permiso=new Permisos();
                Nuevo_Permiso->Cambio_Propetario(Ruta_Particion,Posicion_Inicio_Particion,Contenido.toStdString(),ID_Usuario,ID_nueva);
                Contenido.append("/");
            }
        }else{
            //no es recursivo
            Permisos *Nuevo_Permiso=new Permisos();
            Nuevo_Permiso->Cambio_Propetario(Ruta_Particion,Posicion_Inicio_Particion,path,ID_Usuario,ID_nueva);
        }

        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char Nombreenvio[11]="";
        QString qstr = QString::fromStdString(path);
        QStringList list1 = qstr.split('/');
        QString Contenido;
        strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        char rutaenviar[60]="";
        char tipoenvio[10]="A o C";
        char Descripcionenvio[25]="Cambio de Usuario";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,0,tipoenvio,Nombreenvio,Descripcionenvio);

        std::cin.get();
        QProcess::execute("clear");
    }else{
        std::cout<<"No Se Cumpleron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }
}

void Admin_Archivos::Ejecutar_MKFILE(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();
    //comprobacion de ruta
    int cantObligatoria=0;
    int size=0;
    std::string ruta=Analizador_C->ruta;
    std::string P=Analizador_C->P;
    size=Analizador_C->tamanio;
    std::string cont_Ruta=Analizador_C->cont_ruta;

    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(ruta.length()!=0){cantObligatoria++;}
    if(size==0){size=0;}
    if(cantObligatoria>=1){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }

        std::cout<<"Archivo a Insertar:  "<<ruta<<std::endl;
        //obtenemos el super bloque
        char Nombreenvio[11]="";
        if(P.length()==0){
            BloqueArchivo *Bloque_nuevo=new BloqueArchivo();
            Bloque_nuevo->Busqueda_Archivo(Ruta_Particion,Posicion_Inicio_Particion,ruta,size,cont_Ruta,ID_Usuario);
            strcpy(Nombreenvio,ruta.c_str());
        }else{
            //Primero creo carpetas para el archivo
            //hago split y los inserto

            BloqueCarpeta *Bloque_nuevo=new BloqueCarpeta();
            QString qstr = QString::fromStdString(ruta);
            QStringList list1 = qstr.split('/');
            QString Contenido;
            strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
            if(list1.size()==1){
                //despues de crear analizamos
                strcpy(Nombreenvio,ruta.c_str());
                BloqueArchivo *Bloque_nuevo_Arch=new BloqueArchivo();
                Bloque_nuevo_Arch->Busqueda_Archivo(Ruta_Particion,Posicion_Inicio_Particion,ruta,size,cont_Ruta,ID_Usuario);
            }else{
                for(int posicion=0;posicion<list1.size()-1;posicion++){

                    Contenido.append(list1[posicion]);
                    Bloque_nuevo->Busqueda_Carpeta(Ruta_Particion,Posicion_Inicio_Particion,Contenido.toStdString(),ID_Usuario,1);
                    Contenido.append("/");
                }

                BloqueArchivo *Bloque_nuevo_Arch=new BloqueArchivo();
                Bloque_nuevo_Arch->Busqueda_Archivo(Ruta_Particion,Posicion_Inicio_Particion,ruta,size,cont_Ruta,ID_Usuario);
            }



        }
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char rutaenviar[60]="";
        char tipoenvio[10]="Archivo";
        char Descripcionenvio[25]="Crear Archivo";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

        std::cin.get();
        QProcess::execute("clear");
    }else{
        std::cout<<"No Se Cumplieron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }


}

void Admin_Archivos::Ejecutar_MKDIR(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    //comprobacion de ruta
    int cantObligatoria=0;
    std::string ruta=Analizador_C->ruta;
    std::string P=Analizador_C->P;
    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(ruta.length()!=0){cantObligatoria++;}
    if(cantObligatoria>=1){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        //obtenemos el super bloque
        std::cout<<"Carpeta a Insertar:  "<<ruta<<std::endl;
        char Nombreenvio[11]="";
        if(P.length()==0){
            //deo comprobar si existe la ruta para insertar
            BloqueCarpeta *Bloque_nuevo=new BloqueCarpeta();
            Bloque_nuevo->Busqueda_Carpeta(Ruta_Particion,Posicion_Inicio_Particion,ruta,ID_Usuario,1);

            strcpy(Nombreenvio,ruta.c_str());
        }else{
            //hago split y los inserto
            BloqueCarpeta *Bloque_nuevo=new BloqueCarpeta();
            QString qstr = QString::fromStdString(ruta);
            QStringList list1 = qstr.split('/');
            QString Contenido;
            for(int posicion=0;posicion<list1.size();posicion++){

                Contenido.append(list1[posicion]);
                Bloque_nuevo->Busqueda_Carpeta(Ruta_Particion,Posicion_Inicio_Particion,Contenido.toStdString(),ID_Usuario,1);
                Contenido.append("/");
            }
            strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        }
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char rutaenviar[60]="";
        char tipoenvio[10]="Carpeta";
        char Descripcionenvio[25]="Crear Carpeta";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

        std::cin.get();
        QProcess::execute("clear");
    }else{
        std::cout<<"No Se Cumplieron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }


}

void Admin_Archivos::Ejecutar_CAT(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    //comprobacion de ruta
    int cantObligatoria=0;
    std::string file=Analizador_C->file;

    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(file.length()!=0){cantObligatoria++;}
    if(cantObligatoria>=1){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        //Mostramos contenido
        std::cout<<"Ruta: "<<file<<std::endl;
        BloqueArchivo *Bloque_nuevo_Arch=new BloqueArchivo();
        Bloque_nuevo_Arch->Mostrar_Contenido(Ruta_Particion,Posicion_Inicio_Particion,file);
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char Nombreenvio[11]="";
        QString qstr = QString::fromStdString(file);
        QStringList list1 = qstr.split('/');
        QString Contenido;
        strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        char rutaenviar[60]="";
        char tipoenvio[10]="Archivo";
        char Descripcionenvio[25]="Mostrar Contenido";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,0,tipoenvio,Nombreenvio,Descripcionenvio);


        std::cin.get();
        QProcess::execute("clear");

    }else{
        std::cout<<"No Se Cumpleron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }
}

void Admin_Archivos::Ejecutar_EDIT(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    //comprobacion de ruta
    int cantObligatoria=0;
    std::string path=Analizador_C->ruta;
    std::string contenidoNuevo=Analizador_C->cont_ruta;

    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(path.length()!=0){cantObligatoria++;}
    if(contenidoNuevo.length()!=0){cantObligatoria++;}
    if(cantObligatoria>=2){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        //Editamos Contenido
        BloqueArchivo *Bloque_nuevo_Arch=new BloqueArchivo();
        QString temCon=QString::fromStdString(contenidoNuevo);
        char con[60];
        QByteArray ba = temCon.toLocal8Bit();
        const char *c_str2 = ba.data();
        strcpy(con,c_str2);
        Bloque_nuevo_Arch->Editar_Contenido(Ruta_Particion,Posicion_Inicio_Particion,path,con);
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char Nombreenvio[11]="";
        QString qstr = QString::fromStdString(path);
        QStringList list1 = qstr.split('/');
        QString Contenido;
        strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        char rutaenviar[60]="";
        char tipoenvio[10]="Archivo";
        char Descripcionenvio[25]="Editar Contenido";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);


        std::cin.get();
        QProcess::execute("clear");
    }else{

        std::cout<<"No Se Cumpleron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");

    }
}

void Admin_Archivos::Ejecutar_REN(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    //comprobacion de ruta
    int cantObligatoria=0;
    std::string path=Analizador_C->ruta;
    std::string Nombre;

    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(path.length()!=0){cantObligatoria++;}
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           Nombre=temporalstring2;
           cantObligatoria++;
        }
    }


    if(cantObligatoria>=2){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        //Editamos Nombre
        BloqueCarpeta *Bloque_nuevo=new BloqueCarpeta();
        QString temCon=QString::fromStdString(Nombre);
        char con[11];
        QByteArray ba = temCon.toLocal8Bit();
        const char *c_str2 = ba.data();
        strcpy(con,c_str2);
        std::cout<<"Renombrar Ruta"<<path<<std::endl;
        Bloque_nuevo->Renombrar(Ruta_Particion,Posicion_Inicio_Particion,path,con);
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char Nombreenvio[11]="";
        QString qstr = QString::fromStdString(path);
        QStringList list1 = qstr.split('/');
        QString Contenido;
        strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        char rutaenviar[60]="";
        char tipoenvio[10]="A o C";
        char Descripcionenvio[25]="Renombrar";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

        std::cin.get();
        QProcess::execute("clear");
    }else{

        std::cout<<"No Se Cumpleron Caracteres Obligatorios ren"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");

    }
}

void Admin_Archivos::Ejecutar_CP(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    //comprobacion de ruta
    int cantObligatoria=0;
    std::string path=Analizador_C->ruta;
    std::string Destino;

    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(path.length()!=0){cantObligatoria++;}
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "DEST";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           Destino=temporalstring2;
           cantObligatoria++;
        }
    }


    if(cantObligatoria>=2){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        //Editamos Nombre
        BloqueCarpeta *Bloque_nuevo=new BloqueCarpeta();
        std::cout<<"Copiar Datos de Ruta"<<path<<std::endl;
        std::cout<<"Destino de Datos"<<Destino<<std::endl;
        Bloque_nuevo->Copiar_Contenido(Ruta_Particion,Posicion_Inicio_Particion,path,Destino,ID_Usuario);
        //insertamos en la bitacora
        Bloque_Journali *BloqueJ=new Bloque_Journali();
        char Nombreenvio[11]="";
        QString qstr = QString::fromStdString(path);
        QStringList list1 = qstr.split('/');
        QString Contenido;
        strcpy(Nombreenvio,list1[list1.size()-1].toStdString().c_str());
        char rutaenviar[60]="";
        char tipoenvio[10]="A o C";
        char Descripcionenvio[25]="Copiar Contenido";
        BloqueJ->Insertar_BloqueJour(Ruta_Particion,Posicion_Inicio_Particion,rutaenviar,64,tipoenvio,Nombreenvio,Descripcionenvio);

        std::cin.get();
        QProcess::execute("clear");
    }else{

        std::cout<<"No Se Cumpleron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");

    }
}

void Admin_Archivos::Ejecutar_FIND(){
    Analizador_Caracteres_O *Analizador_C=new Analizador_Caracteres_O();
    Analizador_C->RecibirParametros(this->Parametros);
    Analizador_C->AnalisarCaracteres();

    //comprobacion de ruta
    int cantObligatoria=0;
    inicio=Analizador_C->ruta;

    std::string Ruta_Particion;
    int Posicion_Inicio_Particion;
    //validaciones
    if(inicio.length()!=0){cantObligatoria++;}
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           fin=temporalstring2;
           cantObligatoria++;
        }
    }
    if(cantObligatoria>=2){
        //obtener ruta para donde se encuentra super bloque
        QList  <Nodo_Mount> :: iterator it2;
        for(it2 = this->Lista_Montaje.begin(); it2 != this->Lista_Montaje.end(); ++it2){
            std::string temporalstring=it2->Id;
            if(id_montada.toStdString()==temporalstring){
                Ruta_Particion=it2->Ruta;
                Posicion_Inicio_Particion=it2->Posicion_Start;
            }
        }
        std::cout<<"Busqueda Desde "<<inicio<<std::endl;
        std::cout<<"Destino "<<fin<<std::endl;
        //Busqueda
        FILE *arch;
        arch=fopen(Ruta_Particion.c_str(),"r+b");
        if (arch==NULL){
            exit(1);
        }else{
            Super_Bloque Nodo_AP;
            fseek(arch,Posicion_Inicio_Particion,SEEK_SET);
            fread(&Nodo_AP, sizeof(Super_Bloque), 1, arch);
            //Agregar Contenido
            Graficar_Nodofind(Ruta_Particion,Posicion_Inicio_Particion,3,Nodo_AP.s_inode_start,"",false);
        }

        std::cin.get();
        QProcess::execute("clear");
    }else{

        std::cout<<"No Se Cumpleron Caracteres Obligatorios"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");

    }
}

void Admin_Archivos::Graficar_Nodofind(std::string rutabrir, int PosicionSuperB, int tipo, int posicion, std::string Contenido,bool bandera){
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
            //comprobacion si hay mas relaciones
            if(strcmp(Bloque_CP.b_name2,"..")!=0){
                //comprobamos las primeras dos posiciones
                if(Bloque_CP.b_inodo1!=-1 && strcmp(Bloque_CP.b_name1,".")!=0){
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                    int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo1*sizeof (Tabla_Inodo));
                    if(strcmp(Bloque_CP.b_name1,inicio.c_str())==0){
                        bandera=true;
                    }
                    if(bandera==true){
                        Contenido+="| ";
                        Contenido+=Bloque_CP.b_name1;
                        Contenido+="\n";
                    }
                    if(strcmp(Bloque_CP.b_name1,fin.c_str())==0){
                        std::cout<<Contenido<<std::endl;
                    }
                    Graficar_Nodofind(rutabrir,PosicionSuperB,3,posicion_inicio,Contenido, bandera);


                }
                if(Bloque_CP.b_inodo2!=-1){
                    Super_Bloque Super_B;
                    fseek(arch,PosicionSuperB,SEEK_SET);
                    fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                    int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo2*sizeof (Tabla_Inodo));
                    if(strcmp(Bloque_CP.b_name2,inicio.c_str())==0){
                        bandera=true;
                    }
                    if(bandera==true){
                        Contenido+="| ";
                        Contenido+=Bloque_CP.b_name2;
                        Contenido+="\n";
                    }
                    if(strcmp(Bloque_CP.b_name2,fin.c_str())==0){
                        std::cout<<Contenido<<std::endl;
                    }
                    Graficar_Nodofind(rutabrir,PosicionSuperB,3,posicion_inicio,Contenido,bandera);

                }
            }
            if(Bloque_CP.b_inodo3!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo3*sizeof (Tabla_Inodo));
                if(strcmp(Bloque_CP.b_name3,inicio.c_str())==0){
                    bandera=true;
                }
                if(bandera==true){
                    Contenido+="| ";
                    Contenido+=Bloque_CP.b_name3;
                    Contenido+="\n";
                }
                if(strcmp(Bloque_CP.b_name3,fin.c_str())==0){
                    std::cout<<Contenido<<std::endl;
                }
                Graficar_Nodofind(rutabrir,PosicionSuperB,3,posicion_inicio,Contenido,bandera);

            }
            if(Bloque_CP.b_inodo4!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_inode_start+(Bloque_CP.b_inodo4*sizeof (Tabla_Inodo));
                if(strcmp(Bloque_CP.b_name4,inicio.c_str())==0){
                    bandera=true;
                }
                if(bandera==true){
                    Contenido+="| ";
                    Contenido+=Bloque_CP.b_name4;
                    Contenido+="\n";
                }
                if(strcmp(Bloque_CP.b_name4,fin.c_str())==0){
                    std::cout<<Contenido<<std::endl;
                }
                Graficar_Nodofind(rutabrir,PosicionSuperB,3,posicion_inicio,Contenido,bandera);

            }

        }
        if(tipo==3){
            //inodo
            Tabla_Inodo Tabla_AP;
            fseek(arch,posicion,SEEK_SET);
            fread(&Tabla_AP, sizeof(Tabla_Inodo), 1, arch);
            //agregamos contenido
            Contenido.append("|Tabla");
            for(int pos=0;pos<15;pos++){
                if(pos<12){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Graficar_Nodofind(rutabrir,PosicionSuperB,Tabla_AP.i_type,posicion_inicio,Contenido,bandera);
                    }
                }
                if(pos==12){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Punteros(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,1,Contenido,bandera);
                    }
                }
                if(pos==13){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Punteros(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,2,Contenido,bandera);
                    }
                }
                if(pos==14){
                    if(Tabla_AP.i_block[pos]!=-1){
                        Super_Bloque Super_B;
                        fseek(arch,PosicionSuperB,SEEK_SET);
                        fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                        int posicion_inicio=Super_B.s_block_start+(Tabla_AP.i_block[pos]*sizeof (Bloque_Carpeta));
                        Punteros(rutabrir,posicion_inicio,Tabla_AP.i_type,PosicionSuperB,3,Contenido,bandera);
                    }
                }
            }
        }

    }
}

void Admin_Archivos::Punteros(std::string rutabrir, int posicionStart, int tipo,int PosicionSuperB ,int NumerodeApuuntadores,std::string Contenido,bool bandera){
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

        //creacion de relacion
        NumerodeApuuntadores--;
        for(int posicion=0;posicion<15;posicion++){
            if(Bloque_AP.b_pointers[posicion]!=-1){
                Super_Bloque Super_B;
                fseek(arch,PosicionSuperB,SEEK_SET);
                fread(&Super_B, sizeof(Super_Bloque), 1, arch);
                int posicion_inicio=Super_B.s_block_start+(Bloque_AP.b_pointers[posicion]*sizeof (Bloque_Carpeta));

                if(NumerodeApuuntadores>0){
                    Punteros(rutabrir,posicion_inicio,tipo,PosicionSuperB,NumerodeApuuntadores,Contenido,bandera);
                }else{
                    Graficar_Nodofind(rutabrir,PosicionSuperB,tipo,posicion_inicio,Contenido,bandera);
                    //fin de apuntadores
                }

            }
        }
    }
}

//comparador
int Admin_Archivos::case_insensitive_match(std::string s1, std::string s2) {
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings son iguales
   return 0; //no son iguales
}
