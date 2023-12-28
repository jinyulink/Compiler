#include "ast.h"
typedef struct Node* NodePtr;

NodePtr root = NULL;
int scope_count = 0, symbol_table_count = 0, param_stack_count = 0;
int depth = 0;
extern char *yytext;
extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at symbol %s on line %d\n", s, yytext, yylineno);
}

NodePtr create_node(NodePtr left, NodePtr right, char type) {
    NodePtr tmp = (NodePtr) malloc(sizeof(struct Node));
    tmp->type = type;
    tmp->id = "";
    tmp->value = 0;
    tmp->left = left;
    tmp->right = right;
    return tmp;
}

// 搜尋symbol table，找對應的下標
int get_symbol_table_index(char* tmp_id) {
    for (int i = 0; i < symbol_table_count; i++) 
        if ((strcmp(symbol_table[i].id, tmp_id) == 0) && (symbol_table[i].scope == scope_count)) 
            return i;
    return -1; //DNE
}

void remove_symbol_table_entry(int scope) { //移除所以特定function (scope)的所有變數
    for (int i = 0; i < symbol_table_count; i++) 
        if (symbol_table[i].scope == scope) 
            symbol_table[i].id = "";
            symbol_table_count--;
}

void insert_symbol_table(char type, char* id, int value, int scope, NodePtr fun) {
    symbol_table[symbol_table_count].type = type;
    symbol_table[symbol_table_count].id = id;
    symbol_table[symbol_table_count].value = value;
    symbol_table[symbol_table_count].scope = scope;
    symbol_table[symbol_table_count++].fun = fun;
}

int traverseAST(NodePtr root) {
    if (root == NULL) {
        return 0;
    } 
    else if (root -> type == 'I') { //number
        return root -> value;
    } 
    else if (root -> type == 'B') { //boolean
        return root -> value;
    } 
    else if (root -> type == 'V') { //variable
        int index = get_symbol_table_index(root -> id);
        if (index != -1) { //if node exist
            if (symbol_table[index].type != 'f') { // 如果不是function，即是bool或integer，就直接回傳值
                return symbol_table[index].value;
            } 
            else {
                printf("want to return function\n");
            }
        } 
        else {
            yyerror("variable DNE");
            return -1;
        }
    } 
    // else if (root -> type == 'E') { //expression
    //     //理論上不該被呼叫到，因為node type會在traverse的時候被改掉
    //     return 0;
    // }   
    else if (root -> type == 'P') { // print_num
        int tmp_value = traverseAST(root -> left);
        printf("%d\n", tmp_value);
        return 0;
    } 
    else if (root -> type == 'p') { // print_bool
        int tmp_value = traverseAST(root -> left);
        printf(tmp_value == 1 ? "#t\n" : "#f\n");
        return 0;
    } 
    else if (root -> type == 'T') { //stmt
        traverseAST(root -> left);
        traverseAST(root -> right);
        return 0;
    } 
    else if (root -> type == 'D') { //def_stmt, eg.(define x 10): root->left=x / root->right=10
        symbol_table[symbol_table_count].id = root -> left -> id;
        symbol_table[symbol_table_count].scope = scope_count;
        if (root -> right -> type == 'F') { //如果右邊是function
            symbol_table[symbol_table_count].type = 'F';
            symbol_table[symbol_table_count].fun = root -> right;
            symbol_table[symbol_table_count].value = 0;
        } 
        else { //如果右邊是 數字 or boolean
            symbol_table[symbol_table_count].type = 'I';
            symbol_table[symbol_table_count].value = traverseAST(root -> right);
            symbol_table[symbol_table_count].fun = NULL;
        }
        symbol_table_count ++;
    } 
    else if (root -> type == '+') { 
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = 0;
        if (root -> right == NULL) {
            return tmp_1;
        } //如果右子節點是表達式或另一個乘法運算，則遞迴處理右子節點。
        else if (root -> right -> type == 'E' || root -> right -> type == '+') {
            root -> right -> type = '+';
            tmp_2 = traverseAST(root -> right); 
        } 
        else {
            printf("unexpected plus\n");
        }
        return tmp_1 + tmp_2;
    } 
    else if (root -> type == '-') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = traverseAST(root -> right);
        return tmp_1 - tmp_2;
    } 
    else if (root -> type == '*') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = 1;
        if (root -> right == NULL) {
            return tmp_1;
        } //如果右子節點是表達式或另一個乘法運算，則遞迴處理右子節點。
        else if (root -> right -> type == 'E' || root -> right -> type == '*') {
            root -> right -> type = '*';
            tmp_2 = traverseAST(root -> right); 
        } 
        else {
            printf("unexpected mul\n");
        }
        return tmp_1 * tmp_2;
    } 
    else if (root -> type == '/') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = traverseAST(root -> right);
        return tmp_1 / tmp_2;
    } 
    else if (root -> type == '%') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = traverseAST(root -> right);
        return tmp_1 % tmp_2;
    } 
    else if (root -> type == '>') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = traverseAST(root -> right);
        return tmp_1 > tmp_2;
    } 
    else if (root -> type == '<') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = traverseAST(root -> right);
        return tmp_1 < tmp_2;
    } 
    else if (root -> type == '=') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = 0;
        if (root -> right == NULL) {
            return tmp_1;
        } //如果右子節點是表達式或另一個乘法運算，則遞迴處理右子節點。
        else if (root -> right -> type == 'E' || root -> right -> type == '=') {
            root -> right -> type = '=';
            tmp_2 = traverseAST(root -> right); 
        } 
        else {
            printf("unexpected equal\n");
        }
        return tmp_1 == tmp_2;
    } 
    else if (root -> type == '&') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = 0;
        if (root -> right == NULL) {
            return tmp_1;
        } //如果右子節點是表達式或另一個乘法運算，則遞迴處理右子節點。
        else if (root -> right -> type == 'E' || root -> right -> type == '&') {
            root -> right -> type = '&';
            tmp_2 = traverseAST(root -> right); 
        } 
        else {
            printf("unexpected and\n");
        }

        return tmp_1 && tmp_2;
    } 
    else if (root -> type == '|') {
        int tmp_1 = traverseAST(root -> left);
        int tmp_2 = 0;
        if (root -> right == NULL) {
            return tmp_1;
        } //如果右子節點是表達式或另一個乘法運算，則遞迴處理右子節點。
        else if (root -> right -> type == 'E' || root -> right -> type == '|') {
            root -> right -> type = '|';
            tmp_2 = traverseAST(root -> right); 
        } 
        else {
            printf("unexpected or\n");
        }
        return tmp_1 || tmp_2;
    } 
    else if (root -> type == '^') { //not
        int value = traverseAST(root -> left);
        if(value!=1 && value!=0){
            yyerror("Type error!");
            return 0;
        }
        return value == 1 ? 0 : 1;
    } 
    else if (root -> type == 'S') { //fun_ids
        // 3 跟 x 連結
        insert_symbol_table('I', root -> left -> id, param_stack[param_stack_count - 1], scope_count, NULL);
        param_stack_count--;
        traverseAST(root -> right);
        return 0;
    }   
    else if (root -> type == 'F') { //fun_exp
        traverseAST(root -> left);
        return traverseAST(root -> right);
    } 
    else if (root -> type == 'C') { //fun_call
        traverseAST(root -> left);
        if (root -> right -> type == 'V') {
            int index = get_symbol_table_index(root -> right -> id);
            root -> right = symbol_table[index].fun;
        }
        scope_count += 1;
        int tmp_1 = traverseAST(root -> right);

        remove_symbol_table_entry(scope_count--);
        return tmp_1;
    } 
    else if (root -> type == 'A') { //params
        traverseAST(root -> right);
        int tmp_1 = traverseAST(root -> left);
        param_stack[param_stack_count++] = tmp_1; //把參數push到stack
        return 0;
    } 
    else if (root -> type == 'G') { //if_exp
        int tmp_1 = traverseAST(root -> left);
        root -> right -> value = tmp_1;
        int tmp_2 = traverseAST(root -> right);
        return tmp_2;
    } 
    else if (root -> type == 'X') { //if_exp
        int tmp = root -> value == 1 ? traverseAST(root -> left) : traverseAST(root -> right);
        return tmp;
    } 
    else {
        yyerror("unexpected type");
    }
}
