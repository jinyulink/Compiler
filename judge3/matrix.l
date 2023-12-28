%option noyywrap 
%{
    #include "y.tab.h"
    int errorIndex = 0;
%}
%%
\n      { /* do nothing */ }
[ \t]+  { errorIndex += yyleng; }
"+"|"-" { errorIndex += yyleng; yylval.loc = errorIndex; return ADDSUB; }
"*"     { errorIndex += yyleng; yylval.loc = errorIndex; return MUL; }
","     { errorIndex += yyleng; yylval.loc = errorIndex; return COMMA; }
"["     { errorIndex += yyleng; yylval.loc = errorIndex; return LSBC; }  // Left Square BraCket
"]"     { errorIndex += yyleng; yylval.loc = errorIndex; return RSBC; }  // Right Square BraCket
"("     { errorIndex += yyleng; yylval.loc = errorIndex; return LBC; }   // Left BraCket
")"     { errorIndex += yyleng; yylval.loc = errorIndex; return RBC; }   // Right BraCket
"^T"    { errorIndex += yyleng; yylval.loc = errorIndex; return TP; }    // TransPose
[0-9]+  { errorIndex += yyleng; yylval.loc = errorIndex; yylval.ival = atoi(yytext); return NUM; }
.       { /* do nothing */ }
%%