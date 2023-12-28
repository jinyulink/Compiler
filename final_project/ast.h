#ifndef _AST_H
#define _AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *);
int yylex(void);

// ast tree node
struct Node {
    char type;
    char* id;
    int value;
    struct Node* left;
    struct Node* right;
};

struct symbol_table_node {
    // F: function, B: bool, I: integer
    char type;   
    char* id;
    int value; 
    int scope;
    struct Node* fun;
};

extern struct Node* root;
struct symbol_table_node symbol_table[1000];
int param_stack[1000];
extern int scope_count, symbol_table_count, param_stack_count;
// for debug print tree
extern int depth;

// declare function here 
struct Node* create_node(struct Node* left, struct Node* right, char type);
// put variable to symbol table
void insert_symbol_table(char type, char* id, int value, int scope, struct Node* fun);
// get the index of the variable you want
int get_symbol_table_index(char* id);
// travese AST tree
int traverseAST(struct Node* root); 
void remove_symbol_table_entry(int scope);

#endif