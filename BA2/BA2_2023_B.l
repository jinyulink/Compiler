%{
    // 2023 Compiler BA2 B
    #include<stdio.h>
    #include<stdbool.h>
    bool book = false;
    bool author = false;
    bool check_date(char* date) {
        int year = 0;
        int month = 0;
        int day = 0;
        sscanf(date, "%d/%d/%d", &year, &month, &day);
        if(month > 12 || month < 1) return false;
        if(month == 2 && day >29)   return false;
        else if(month <= 7 && month % 2 && day > 31)    return false;
        else if(month <= 7 && month % 2 == 0 && day > 30)   return false;
        else if(month >= 8 && month % 2 == 0 && day > 31)   return false;
        else if(month >= 8 && month % 2 && day > 30)    return false;
        return true;
    }
%}

%%
([A-Z][a-z]*)("_"[A-Z][a-z]*)* {if(!book){printf("Book name:%s\n", yytext);book = true;}}
[A-Z]+", "[A-Z][a-z]*"-"[A-Z][a-z]* {if(!author){printf("Author:%s\n", yytext);author = true;}}
[0-9]{4}"/"[0-9]{2}"/"[0-9]{2} {if(check_date(yytext)){printf("Publication date:%s\n", yytext);}}
"978-"[0-9]{1}"-"[0-9]{6}"-"[0-9]{2}"-"[0-9]{1} {printf("ISBN:%s\n", yytext);}
\n {book = false;author = false;}
. {;}
%%
int main(){
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

