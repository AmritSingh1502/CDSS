%{
#include"y.tab.h"
%}
alpha [a-zA-Z]
digit [0-9]
%%
[ \t\n]
switch                       return SWITCH;
int                          return INT;
case                         return CASE;
break                        return BREAK;
default                      return DEFAULT;
{digit}+                     return NUM;
{alpha}({alpha}|{digit})*    return ID;
.                            return yytext[0];
%%