#include "analizador_caracteres_o.h"

Analizador_Caracteres_O::Analizador_Caracteres_O()
{

}
void Analizador_Caracteres_O::RecibirParametros(QList <std::string> P){
    Parametros.clear();
    this->Parametros=P;

}

void Analizador_Caracteres_O::AnalisarCaracteres(){
    //recorrer lista
    QList  <std::string> :: iterator it;
    for(it = this->Parametros.begin(); it != this->Parametros.end(); ++it){
        std::string temporalstring=*it;

        std::string s2;
        s2 = "SIZE";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temporalstring2=*it2;
           int valor=std::stoi(temporalstring2);
           if(valor>0){
               std::cout << "Valor "<<valor<<std::endl;
               tamanio=valor;
           }else{
               std::cout << "TAMANIO MENOR A 0: "<<temporalstring2<<std::endl;
           }
        }

        s2 = "PATH";
        if(case_insensitive_match(temporalstring, s2)) {
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

        s2 = "NAME";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           if(case_insensitive_match(temnombre, "mbr") ){
               tiponombre="mbr";
           }else{
               if(case_insensitive_match(temnombre, "disk") ){
                   tiponombre="disk";
               }else{
                   std::cout <<"Nombre Incorrecto debe ser disk o mbr"<<std::endl;
               }
           }
        }

        s2 = "ID";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           id=temnombre;
        }

        s2 = "USR";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           if(temnombre.length()>10){
               std::cout<<"El Usuario no puede tener mas de 10 Caracteres"<<std::endl;
           }else{
               Usuario=temnombre;
           }
        }

        s2 = "PWD";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           if(temnombre.length()>10){
               std::cout<<"El Password no puede tener mas de 10 Caracteres"<<std::endl;
           }else{
               Password=temnombre;
           }
        }

        s2 = "GRP";
        if(case_insensitive_match(temporalstring, s2)) {
           //insertamos contenido
           QList  <std::string> :: iterator it2=std::next(it);
           std::string temnombre=*it2;
           if(temnombre.length()>10){
               std::cout<<"El Grupo no puede tener mas de 10 Caracteres"<<std::endl;
           }else{
               Grupo=temnombre;
           }
        }

    }
}

//comparador
int Analizador_Caracteres_O::case_insensitive_match(std::string s1, std::string s2) {
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings son iguales
   return 0; //no son iguales
}
