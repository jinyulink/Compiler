%option noyywrap 
%{
    #include "y.tab.h"
    int errorIndex = 0;
%}
%%
"<"               { return OPEN_ANGLE; }
">"               { return CLOSE_ANGLE; }
"/"               { return SLASH; }
"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }
"true"          { return TRUE; }
"false"         { return FALSE; }
[ \t\n\r]+      ; /* 忽略空白 */
.               { /* 處理非法字符 */ }
%%