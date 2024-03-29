#include "analizador.h"

Analizador::Analizador()
{
    this->AdminDiscos=new Admin_Disco();
    this->AdminUsuyG=new Admin_UsuariosyGrupos();
}
void Analizador::LeerArchivo(char Ruta[200]){

    std::fstream archivo(Ruta);
    if(archivo.fail()){
        printf("El archivo T no se logro abrir \n");
    }else{
        for (std::string linea; std::getline(archivo, linea); ){
            char Comando[200];
            strcpy(Comando, linea.c_str());
            //std::cout<<"RECIBIO"<<Comando<<std::endl;
            AnalisarComando(Comando);

        }
    }
}

void Analizador::AnalisarComando(char Comando[200]){
    this->ListaParametros.clear();
    //AnalisadorLexico
    int Estado=0;
    std::string contenido="";
    int i=0;
    while (Comando[i]) {
        //Estado 1
        if(Estado==1){
            int numcar = int(Comando[i]);
            if(numcar==34){
                Estado=0;
                ListaParametros.append(contenido);
                contenido="";
                i++;

            }else{
                contenido.push_back(Comando[i]);
            }
        }
        //Estado 4
        if(Estado==4){
            //se queda en comentario hasta que termine la linea
        }


        if(Estado==0){
            //ruta con comillas
            int numcar2 = int(Comando[i]);
            if(numcar2==34){
                Estado=1;
                numcar2 = int(Comando[i+1]);
                if(numcar2==47){
                    i++;
                }

            }
            //Cadena
            if(isalpha(Comando[i])){
                contenido+=Comando[i];
                Estado=2;
                i++;

            }

            //digito
            if(isdigit(Comando[i])){
                //mas menosde un digito
                if(Comando[i-1]==43 || Comando[i-1]==45){
                    contenido+=Comando[i-1];
                }
                contenido+=Comando[i];
                i++;
                Estado=3;
            }
            //Comentario
            int numcar3 = int(Comando[i]);
            if(numcar3==35){
                Estado=4;
            }
        }

        //Estado 2
        if(Estado==2){
            int numcar = int(Comando[i]);
            if(numcar==32 || numcar==61 || numcar==13){
                Estado=0;
                ListaParametros.append(contenido);
                contenido="";
                i--;

            }else{
                contenido+=Comando[i];
            }
        }
        //Estado 3
        if(Estado==3){
            if(isdigit(Comando[i])){
                contenido+=Comando[i];
            }else{
                Estado=0;
                ListaParametros.append(contenido);
                contenido="";
                i--;
            }
        }



        i++;
    }
    if(Estado==2||Estado==3){
        ListaParametros.append(contenido);
    }else{
        if(Estado==4){
             ListaParametros.append("COMENTARIO");
        }
        if(contenido==""){
             ListaParametros.append("SALTO DE LINEA");
        }
    }

    QList<std::string>::iterator no;
    for(no = this->ListaParametros.begin(); no != this->ListaParametros.end(); ++no){
        std::string temporalstring=*no;
    }
    EjecuarComando();

}

void Analizador::EjecuarComando(){
    QList <std::string> :: iterator it;
    it = this->ListaParametros.begin();
    std::string resetm=*it;

    //CREACION DEL DISCO
    std::string s2;
    s2 = "MKDISK";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "CREACION DE DISCO"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->CrearArchivo();
    }

    //ELIMINACION DEL DISCO
    s2 = "RMDISK";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "ELIMINAR DISCO"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->EliminarArchivo();
    }

    //ADMINISTRADOR DE PARTICIONES
    s2 = "FDISK";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO PARA PARTICION"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->EventoParticion();
    }

    //MONTAR
    s2 = "MOUNT";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO MONTAR PARTICION"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->Montar();
    }
    s2 = "UNMOUNT";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO DESMONTAR PARTICION"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->Desmontar();
    }


    //FASE 2
    s2 = "MKFS";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO FORMATEO PARTICION"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->FormateoEXT();
    }
    //LOGIN
    s2 = "LOGIN";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO LOGIN"<<std::endl;
       AdminUsuyG->RecibirParametros(ListaParametros);
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       AdminUsuyG->Lista_Montaje.clear();
       AdminUsuyG->Lista_Montaje=this->Lista_Montaje;
       AdminUsuyG->Login();
    }
    s2 = "LOGOUT";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO LOGOUT"<<std::endl;
       AdminUsuyG->Logout();
    }
    s2 = "MKGRP";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO CREAR GRUPO"<<std::endl;
       AdminUsuyG->RecibirParametros(ListaParametros);
       AdminUsuyG->CrearGrupo();
    }
    s2 = "RMGRP";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO ELIMINAR GRUPO"<<std::endl;
       AdminUsuyG->RecibirParametros(ListaParametros);
       AdminUsuyG->EliminarGrupo();
    }
    s2 = "MKUSR";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO CREAR USUARIO"<<std::endl;
       AdminUsuyG->RecibirParametros(ListaParametros);
       AdminUsuyG->CrearUsuario();
    }
    s2 = "RMUSR";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO ELIMINAR USUARIO"<<std::endl;
       AdminUsuyG->RecibirParametros(ListaParametros);
       AdminUsuyG->EliminarUsuario();
    }


    //ADMINISTRACION DE ARCHIVOS

    s2 = "CHMOD";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO CHMOD"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_CHMOD();
    }
    s2 = "CHOWN";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO CHOWN"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_CHOWN();
    }
    s2 = "CHGRP";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO CHOWN"<<std::endl;
       AdminUsuyG->RecibirParametros(ListaParametros);
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       AdminUsuyG->Lista_Montaje.clear();
       AdminUsuyG->Lista_Montaje=this->Lista_Montaje;
       AdminUsuyG->Cambiar_Grupo();
    }
    s2 = "MKFILE";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO MKFILE"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_MKFILE();
    }
    s2 = "MKDIR";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO MKDIR"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_MKDIR();
    }
    s2 = "CAT";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO MOSTRAR CONTENIDO DE ARCHIVO"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_CAT();
    }
    s2 = "EDIT";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO EDITAR CONTENIDO"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_EDIT();
    }
    s2 = "REN";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO RENOMBRAR"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_REN();
    }
    s2 = "CP";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO COPIAR"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_CP();
    }
    s2 = "FIND";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO BUSQUEDA"<<std::endl;
       Admin_Archivos *Nuevo_Archivo=new Admin_Archivos();
       this->Lista_Montaje.clear();
       this->Lista_Montaje=AdminDiscos->Lista_Montaje;

       Nuevo_Archivo->Lista_Montaje.clear();
       Nuevo_Archivo->Lista_Montaje=this->Lista_Montaje;
       Nuevo_Archivo->id_montada=AdminUsuyG->Id_Particion;
       Nuevo_Archivo->ID_Usuario=AdminUsuyG->ID_Usuario;

       Nuevo_Archivo->RecibirParametros(ListaParametros);
       Nuevo_Archivo->Ejecutar_FIND();
    }

    //EVENTO PERDIDDA Y RECUPERACION
    s2 = "LOSS";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO LOSS"<<std::endl;
       int cantObligatoria=0;
       std::string id;
       //recorrer lista
       QList  <std::string> :: iterator it2;
       for(it2 = this->ListaParametros.begin(); it2 != this->ListaParametros.end(); ++it2){
           std::string temporalstring=*it2;

           std::string s2 = "ID";
           if(case_insensitive_match(temporalstring, s2)) {
              cantObligatoria++;
              QList  <std::string> :: iterator it3=std::next(it2);
              id=*it3;
           }
       }
       if(cantObligatoria>=1){
           Id_Loss.append(id);
           std::cout << "Se ha realizado un loss sobre: "<<id<<std::endl;
       }else{
           std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS"<<std::endl;
       }
    }
    s2 = "RECOVERY";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO RECOVERY"<<std::endl;
       int cantObligatoria=0;
       std::string id;
       //recorrer lista
       QList  <std::string> :: iterator it2;
       for(it2 = this->ListaParametros.begin(); it2 != this->ListaParametros.end(); ++it2){
           std::string temporalstring=*it2;

           std::string s2 = "ID";
           if(case_insensitive_match(temporalstring, s2)) {
              cantObligatoria++;
              QList  <std::string> :: iterator it3=std::next(it2);
              id=*it3;
           }
       }
       if(cantObligatoria>=1){
           for(int pos=0;pos<Id_Loss.size();pos++){
               if(Id_Loss[pos]==id){
                   Id_Loss.removeAt(pos);
                   std::cout << "Se han recuperado los datos de: "<<id<<std::endl;
               }
           }
       }else{
           std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS"<<std::endl;
       }
    }

    //PAUSA
    s2 = "PAUSE";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO PAUSA"<<std::endl;
       std::cout << "Presione Cualquier Tecla Para Continuar"<<std::endl;
       std::cin.get();
       QProcess::execute("clear");
    }

    //REPORTES
    s2 = "REP";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO REPORTE"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
       AdminDiscos->Id_Loss=Id_Loss;
       AdminDiscos->Reporte();
    }

    //EJECUTAR OTRO ARCHIVO DENTRO
    s2 = "EXEC";
    if(case_insensitive_match(resetm, s2)) {
       //comprobacion de ruta
       int cantObligatoria=0;
       std::string ruta;
       //recorrer lista
       QList  <std::string> :: iterator it2;
       for(it2 = this->ListaParametros.begin(); it2 != this->ListaParametros.end(); ++it2){
           std::string temporalstring=*it2;

           std::string s2 = "PATH";
           if(case_insensitive_match(temporalstring, s2)) {
              cantObligatoria++;
              QList  <std::string> :: iterator it3=std::next(it2);
              ruta=*it3;
           }
       }
       if(cantObligatoria>=1){
           char EnvioRuta[200];
           strcpy(EnvioRuta, ruta.c_str());
           LeerArchivo(EnvioRuta);
       }else{
           std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS"<<std::endl;
       }
    }

}



//comparador
int Analizador::case_insensitive_match(std::string s1, std::string s2) {
   //convert s1 and s2 into lower case strings
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings are same
   return 0; //not matched
}
