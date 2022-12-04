%{
    #include<stdio.h>
    #include<stdlib.h>
%}
%token ID NUM SWITCH CASE DEFAULT BREAK INT
%right '='
%%
program: switchstm {printf("Input accepted.\n");exit(0);}
        ;
switchstm: SWITCH '(' ID ')' '{' block '}'
            ;
block:    caselist
     |    caselist   defaultstm
            ;
caselist: casestm | casestm caselist ;

casestm:   CASE NUM ':' assign ';' BREAK ';'
            ;

defaultstm :    DEFAULT  ':' assign ';' BREAK ';'
            ;
assign    : ID '=' NUM {$1=$3;}
        ;

%%

#include "lex.yy.c"

int main(){
    return yyparse();
}

int yyerror( char * s ) { 
    myerror();
}

myerror(){
    printf(" Syntax Rejected \n ");
}

yywrap(){
    printf("PARSING OVER ");
}