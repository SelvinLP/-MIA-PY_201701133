#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <FlexLexer.h>
//analizador Manual
#include <analizador.h>
#include <list>
//Operaciones de disco

void Menu();
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Menu();

    return 0;
}
void Menu(){
    //Metodo para Analizar tokens
    Analizador *nuevo=new Analizador();
    bool Ciclo=true;

    while (Ciclo) {
        int opcion=0;
        std::cout<<"1. Ingresar Comando "<<std::endl;
        std::cout<<"2. Salir "<<std::endl;
        std::cin>>opcion;

         //INGRESO DEL COMANDO
         if(opcion==1){
             char Comando[200];
             std::string name;
             std::cout << "Ingrese Comando";
             std::cin.get();
             std::getline (std::cin,name);

             strcpy(Comando, name.c_str());
             //yyFlexLexer *token=new yyFlexLexer();
             //token->yylex();
             nuevo->AnalisarComando(Comando);

         }


         //SALIR
         if(opcion==2){
             Ciclo=false;
         }

    }

}
