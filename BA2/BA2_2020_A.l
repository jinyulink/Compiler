%{
#include <stdio.h>
%}

%%
\$\d{1,5}(\d{1,5})? { printf("transfer %s\n", yytext); }/* ATM 暗號 */

\+\d{1,3} { printf("after %s days\n", yytext); }/* Day 暗號 */

([01]?[0-9]|2[0-3]):[0-5][0-9] { printf("at %s\n", yytext); }/* Time 暗號 */

[A-Z][a-z.-]*[A-Z] { printf("at %s\n", yytext); }/* Place 暗號 */

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    yylex();
    return 0;
}

// \$[0-9]{1,6} {
//     int amount = atoi(yytext + 1); // 轉換數字部分，跳過 `$`
//     if (amount <= 100000) {
//         printf("%s\n", yytext);
//     }
// }
// 這裡，[0-9]{1,6} 匹配一串長度為 1 到 6 的數字。然後使用 atoi 將數字部分轉換為整數，並檢查是否小於或等於 100000。


// \+\d{1,3} {
//     int day = atoi(yytext + 1); // 轉換數字部分，跳過 `+`
//     if (day >= 0 && day <= 365) {
//         printf("%s\n", yytext);
//     }
// }

// ([01]?[0-9]|2[0-3]):[0-5][0-9] {
//     printf("%s\n", yytext);
// }
