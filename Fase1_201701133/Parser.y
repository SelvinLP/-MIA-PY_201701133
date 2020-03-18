%{
#include "scanner.h"
#include "tokens.h"
#include <iostream>
extern char *yytext;
extern tokens *raiz; // Raiz del arbol


int yyerror(const char* mens)
{
    std::cout << mens <<" "<<yytext<< std::endl;
    return 0;
}
%}
%defines "parser.h"
%output "parser.cpp"
%locations

%union
{
  char TEXT [256];
  class tokens *tq;
}



%token <TEXT> Digito
%token <TEXT> Ruta
%token <TEXT> Id
%token <TEXT> Tmenos
%token <TEXT> Tdiagonal
%token <TEXT> Tigual
%token <TEXT> Tpunto



%type <tq> INICIO;
%type <tq> COMANDO;
%type <tq> PARAMETRO;
%type <TEXT> CUERPO;
%type <TEXT> RUTASINCOMILLAS;
%start INICIO
%%
//Gramatica
INICIO : COMANDO { raiz = $$; }
;

COMANDO : Id PARAMETRO{$$= new tokens(yytext,""); $$->add($2);}
;

PARAMETRO : PARAMETRO Tmenos Id Tigual CUERPO {$$=$1; tokens *nodo = new tokens($3,$5);$$->add(*nodo);}
          | Tmenos Id Tigual CUERPO {$$ = new tokens($2,$4);}
;

CUERPO : Tdiagonal RUTASINCOMILLAS {$$ =$1+$2;}
        | Ruta {$$ =$1;}
        | Digito {$$ =$1;}
        | Id {$$ =$1;}
;

RUTASINCOMILLAS : RUTASINCOMILLAS Tdiagonal Id {$$=$1+$2+$3;}
                  | Tdiagonal Id {char hola[]=$1+$2;$$=hola;}
;
%%
