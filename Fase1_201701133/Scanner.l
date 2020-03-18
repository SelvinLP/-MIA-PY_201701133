%option case-insensitive
%option yylineno
%option noyywrap
%option c++
%option nounput
%option header-file= "scanner.h"
%option outfile="scanner.cpp"
%{
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
%}


Digito (\-|\+)?[0-9]+
Ruta "\""[^"\""]*"\""
Id [a-zA-Z]+(([a-zA-Z]+)|{Digito}|"_"|".")*
RutasinComillas ([a-zA-Z]|\/)+(([a-zA-Z]+)|{Digito}|"_"|"."|" "|\/)*({Id}|[a-zA-Z])
%%

{Digito}          {std::cout <<"DIGITO " <<yytext<< std::endl;  }
{Ruta}            {std::cout <<"RUTA " << yytext<< std::endl;  }
{Id}              {std::cout <<"ID " << yytext<<std::endl;  }
{RutasinComillas} {std::cout <<"RUTA SIN COMILLAS" << yytext <<std::endl;  }
"\n"            {}
"-"             { }
"="             { }
[\t\r\f]        {return=0;}
" "                     {}
. {std::cout <<"NO RECONOCIDO" << std::endl;}

%%
