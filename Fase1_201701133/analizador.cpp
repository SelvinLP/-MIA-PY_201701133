#include "analizador.h"

Analizador::Analizador()
{
    this->AdminDiscos=new Admin_Disco();
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


    //REPORTES
    s2 = "REP";
    if(case_insensitive_match(resetm, s2)) {
       std::cout << "EVENTO REPORTE"<<std::endl;
       AdminDiscos->RecibirParametros(ListaParametros);
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


