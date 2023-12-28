%option noyywrap
%{
    #include "BA3_A.tab.h"
%}
%%
[0-9]*"."[0-9]+   { yylval.fval = atof(yytext); return NUMBER; }
[0-9]*"."[0-9]*   { yylval.fval = atof(yytext); return NUMBER; }
[0-9]+            { yylval.fval = atof(yytext); return NUMBER; }
"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return MULTIPLY; }
"/"               { return DIVIDE; }
[ \t\n\r]           {/* whitespace ignored */}
.                 { return INVALID; }
%%