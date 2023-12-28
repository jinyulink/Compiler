%{
    #include "parser.tab.h"
%}

separator [ \t\n\r]
letter [a-z]
digit [0-9]

number 0|[1-9]{digit}*|-[1-9]{digit}*
ID {letter}[{letter}{digit}-]*
bool-val #t|#f

%%
{separator}       {;}
[\(\)\+\-\*\/\>\<\=]   {return yytext[0];}
"mod"           {return MOD;}  
"and"           {return AND;}
"or"            {return OR;}
"not"           {return NOT;}
"if"            {return IF;}
"define"        {return DEFINE;}
"fun"           {return LAMBDA;}
"print-num"     {return PRINT_NUM; }
"print-bool"    {return PRINT_BOOL; }
{ID}*           {yylval.id = strdup(yytext); return ID;}
{number}        {yylval.ival = atoi(yytext); return NUMBER;}
{bool-val}      {yylval.ival = (yytext[1] == 't'); return BOOLEAN;}
.               {} 
%%