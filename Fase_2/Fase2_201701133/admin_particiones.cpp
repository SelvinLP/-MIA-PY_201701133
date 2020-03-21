#include "admin_particiones.h"

Admin_Particiones::Admin_Particiones()
{

}
void Admin_Particiones::RecibirParametros(QList <std::string> P){
    this->pos=-1;
    Parametros.clear();
    this->Parametros=P;
    QList  <std::string> :: iterator it;
//    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
//        std::string temporalstring=*it;
//        std::cout <<temporalstring<<std::endl;
//    }

    //recibe lista de particiones

}

void Admin_Particiones::EventoParticion(){
    int cantObligatoria=0;
    //obligatorias
    std::string ruta;
    int size=1024;
    int tamaniovalor=1;
    char nombre[16];
    //no obligatorias
    char unit='K';
    char tipo[2]="P";
    char fit[3]="BF";
    int accion=2;//0 inserta, 1 elimina
    std::string des_accion;
    int agregarespacio;

    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;


        std::string s2;
        s2 = "SIZE";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           int valor=std::stoi(temporalstring2);
           if(valor>0){
               tamaniovalor=valor;
           }else{
               cantObligatoria--;
               std::cout << "TAMANIO MENOR A 0: "<<temporalstring2<<std::endl;
           }
        }

        s2 = "PATH";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           ruta=*it2;
        }

        s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           cantObligatoria++;
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           strcpy(nombre,temporalstring2.c_str());
        }
        //no obligatorias

        s2 = "UNIT";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;

           if(temporalstring2=="k" || temporalstring2=="K"){
               strcpy(&unit,"K");
           }else{
               if(temporalstring2=="m" || temporalstring2=="M"){
                   size=size*1024;
                   strcpy(&unit,"M");
               }else{
                   if(temporalstring2=="b" || temporalstring2=="B"){
                       size=size/1024;
                      strcpy(&unit,"B");
                   }else{
                       std::cout << "ERROR FORMATO INCORRECTO UNIT"<<temporalstring2<<std::endl;
                   }
               }
           }
        }

        s2 = "TYPE";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           if(temporalstring2=="e" || temporalstring2=="E"){
               strcpy(tipo,"E");
           }else{
               if(temporalstring2=="l" || temporalstring2=="L"){
                   strcpy(tipo,"L");
               }else{
                   if(temporalstring2=="p" || temporalstring2=="P"){
                       strcpy(tipo,"P");
                   }else{
                       std::cout << "ERROR FORMATO INCORRECTO TYPE"<<temporalstring2<<std::endl;
                   }
               }
           }
        }

        s2 = "FIT";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           if(temporalstring2=="FF"||temporalstring2=="BF"||temporalstring2=="WF"){
               char tem[3];
               strcpy(tem,temporalstring2.c_str());
               strcpy(fit,tem);
           }else{
               std::cout << "NO SE ACEPTO FIT "<<temporalstring2<<std::endl;
           }
        }

        s2 = "DELETE";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           accion=0;
           des_accion=temporalstring2;
        }

        s2 = "ADD";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           accion=1;
           agregarespacio=std::stoi(temporalstring2);
        }

    }


    //validacion de cantidad obligatoria
    if(cantObligatoria>=2){
        std::cout<<"Particion: "<<nombre<<std::endl;
        FILE *archivo;
        std::cout << ruta<<std::endl;
        if ((archivo = fopen(ruta.c_str(),"r+b")) == NULL){
            exit(1);
        }else{
        }        //comprobacion de final
        fseek(archivo,0,SEEK_END);
        int final=ftell(archivo);
        fclose(archivo);

        //VALIDACIONES
        //eliminar
        if(accion==0 ){
            std::cout << "PARA ELIMINAR "<<std::endl;
            //fast
            if(case_insensitive_match(des_accion, "FAST")) {
                bool bande=false;
                for(int lleno=0;lleno<4;lleno++){
                    if(strcmp(ArregloMBR[lleno].part_name, nombre) == 0){
                        std::cout<<"DESEA ELIMINAR EL PARTICION: "<<nombre<<std::endl;
                        std::cout<<"1.SI"<<std::endl;
                        std::cout<<"2.NO"<<std::endl;
                        int opcion;
                        std::cin >>opcion;
                        if(opcion==1){
                            strcpy(nuevo.part_status,"N");
                            nuevo.part_size=ArregloMBR[lleno].part_size;
                            this->pos=lleno-5;
                            bande=true;
                            break;
                        }

                    }
                }
                if(bande==1){
                    std::cout<<"Se ha eliminado la particion"<<std::endl;
                }
            }else{
                if(case_insensitive_match(des_accion, "FULL")) {
                    bool bande=false;
                    for(int lleno=0;lleno<4;lleno++){
                        if(strcmp(ArregloMBR[lleno].part_name, nombre) == 0){
                            std::cout<<"DESEA ELIMINAR EL PARTICION: "<<nombre<<std::endl;
                            std::cout<<"1.SI"<<std::endl;
                            std::cout<<"2.NO"<<std::endl;
                            int opcion;
                            std::cin >>opcion;
                            if(opcion==1){
                                strcpy(nuevo.part_status,"N");
                                nuevo.part_size=ArregloMBR[lleno].part_size;
                                this->pos=lleno-5;
                                bande=true;
                                break;
                            }

                        }
                    }
                    if(bande==1){
                        std::cout<<"Se ha eliminado la particion"<<std::endl;
                    }
                }else{
                    std::cout<<"El Delete No es Correcto"<<std::endl;
                }

            }


        }else{
            if(accion==1){
                //metodo add
            }else{
                //primaria o extendida
                if(strcmp(tipo,"P")==0 || strcmp(tipo,"E")==0){
                    //primera validacion si hay espacio en las particiones y si el nombre esat repetido
                    bool Disponibilidad=false;
                     for(int lleno=0;lleno<4;lleno++){
                         std::cout<<ArregloMBR[lleno].part_status<<std::endl;
                         if(strcmp(ArregloMBR[lleno].part_status, "N") == 0){
                             Disponibilidad=true;
                         }
                         if(strcmp(ArregloMBR[lleno].part_status, "S") == 0){
                             //ya existe uno con el mismo nombre
                             std::cout<<"NO Espacio"<<std::endl;
                             if(strcmp(ArregloMBR[lleno].part_name, nombre) == 0){
                                 Disponibilidad=false;
                                 std::cout<<"Mismo Nombre"<<std::endl;
                                 break;
                             }
                             //caso de que solo puede haer una extendida
                             if((strcmp(ArregloMBR[lleno].part_type, "E") == 0) && (strcmp(tipo, "E") == 0)){
                                 std::cout<<"Ya hay una extendida"<<std::endl;
                                 Disponibilidad=false;
                                 break;
                             }

                         }

                     }

                     //en vaso de que haya espacio
                     //tipo de ajuste
                     std::cout<<Disponibilidad<<std::endl;
                     if(Disponibilidad==1){
                         int posFinal;
                         int posInicial=TamanioMBRDisk;
                         float tamaniooparaInsertar;
                         //primer espacio vacio que queda
                         bool Insertado=false;
                         if(strcmp(fitdisk, "FF") == 0 ||strcmp(fitdisk, "BF") == 0 || strcmp(fitdisk, "WF") == 0){
                             //nos saltamos el tamaño del mbr del disco
                             this->pos=0;
                             for(int lleno=0;lleno<4;lleno++){
                                 if(strcmp(ArregloMBR[lleno].part_status, "S") == 0){
                                     posInicial+=ArregloMBR[lleno].part_size+1;
                                     this->pos=lleno+1;
                                 }else{
                                     //hay espacio para insertar
                                     for(int rrecorrido2=lleno;rrecorrido2<5;rrecorrido2++){
                                         if(strcmp(ArregloMBR[rrecorrido2].part_status, "S") == 0){
                                             posFinal+=ArregloMBR[rrecorrido2].part_start;
                                             break;
                                         }else{
                                             if(rrecorrido2==3){
                                                 posFinal=final;
                                                 break;
                                             }
                                         }
                                     }
                                     //comprobacion si cuple con el espacio
                                     //std::cout<<posFinal<<std::endl;
                                     //std::cout<<posInicial<<std::endl;
                                     tamaniooparaInsertar=(float)posFinal-(float)posInicial;
                                     //std::cout<<tamaniooparaInsertar<<std::endl;
                                     if(tamaniooparaInsertar>size*tamaniovalor){
                                         strcpy(nuevo.part_fit,fit);
                                         strcpy(nuevo.part_status,"S");
                                         strcpy(nuevo.part_type,tipo);
                                         nuevo.part_start=posInicial;
                                         nuevo.part_size=size*tamaniovalor;
                                         strcpy(nuevo.part_name,nombre);

                                         Insertado=true;
                                         std::cout << "INSERTADO MBR CORRECTAMENTE"<<std::endl;

                                         break;
                                     }else{
                                         std::cout << "NO HAY ESPACIO SUFICIENTE"<<std::endl;
                                     }
                                 }
                             }//fin FF

                         }

                         if(Insertado==0){
                             std::cout << "No hay espacio para almacenar"<<std::endl;
                         }

                     }


                }

            }

        }



        std::cin.get();
        QProcess::execute("clear");
    }else{
        std::cout << "NO SE CUMPLIERO LOS REQUISITOS OBLIGATORIOS"<<std::endl;
        std::cin.get();
        QProcess::execute("clear");
    }
}

MBR_Particion Admin_Particiones::RetornarParticionInsertada(){
    return nuevo;
}

int Admin_Particiones::Retornopos(){
    return pos;
}

//comparador
int Admin_Particiones::case_insensitive_match(std::string s1, std::string s2) {
   //convert s1 and s2 into lower case strings
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings are same
   return 0; //not matched
}
