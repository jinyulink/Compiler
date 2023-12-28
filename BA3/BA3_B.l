%{
#include "BA3_B.tab.h"
#include <stdlib.h>
%}

%%

0|[1-9][0-9]*|-[1-9][0-9]*         { yylval = atoi(yytext); return NUMBER; }
"+"            { return ADD; }
"-"            { return SUB; }
"*"            { return MUL; }
"/"            { return DIV; }
[ \t\n\r]        { /* ignore whitespace */ }
.              { /* ignore everything else */ }

%%