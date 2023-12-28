# 執行
```bash
./make.sh
```
執行此shell script，即可編譯scanner.l、parser.y、ast.c，並且執行測資。
# 檔案
1. scanner.l - 解析token，解析token方式主要照題目所說。
2. parser.y - 分析語法，include "ast.h"，語意規則也是照題目所說。
3. ast.h - parser所需用到的function header file
4. ast.c - 實現function的c程式碼
5. make.sh - 編譯及測試測資的shell script

# 主要function
主要的程式都寫在ast.h / ast.c裡面，以下列出所有function以及資料結構的作用:
1. struct Node - 用來儲存每個node的資訊，包含token的type、id、value，以及child node的pointer (left跟right)。
    * char type
    * char* id
    * int value
    * Node* left
    * Node* right
2. struct symbol_table_node - 用來儲存symbol table的資訊，包含id、type、scope、value。
    * char type
    * char* id
    * int value
    * int scope
    * Node* fun 
    1. 當遇到新的變數名稱、function名稱時，就會新增一個symbol table node。
    2. 在不同function同名的變數，會有不同的scope，會依照scope來區分這些variable。
    3. 當需要呼叫一個變數名稱或function時，會透過呼叫get_symbol_table_index()來找到對應的symbol table node的下標。
    4. 如果呼叫一個未定義的變數，get_symbol_table_index()就會回傳-1。
3. int param_stack[1000] - 當function被呼叫時，將需要的參數push到param_stack裡面，並且在function結束時pop掉。
```
(define (addTwoNumbers a b)
  (+ a b))

(print-num (addTwoNumbers 3 5))
```
* 先識別出addTwoNumbers是一個function，並且將3跟5push到param_stack裡面。
* 進入addTwoNumbers function，並且從paramstack取值，將a跟b的值設定為3跟5。
* 執行 (+ a b)的分析，計算後得到結果8。
* function執行完成後，將param_stack pop掉 清空。 
4. int scope_count, symbol_table_count, param_stack_count
    * scope_count - 紀錄現在的scope是多少，當遇到新的function時，scope_count就會加1。
    * symbol_table_count - 紀錄現在symbol table裡面有多少個entry。
    * param_stack_count - 紀錄現在param_stack裡面有多少個參數數量。
5. create_node() - 創造一個新的node，並且初始化。
6. get_symbol_table_index() - 搜尋id在symbol table對應的下標。
7. remove_symbol_table_entry() - 將特定scope裡面的參數從symbol table移除。
8. insert_symbol_table() - 創建symbol table node。
    * type, id, value, scope, fun (node)
9. traverseAST() - 遍歷AST，並且執行每個node的function。

# 測資範例
```
(print-num ((fun (x) (+ x 1)) 3))
```
```
        print-num
           |
          fun
          / \
         /   \
        x    (+)
              / \
             x   1
```
3會被push到param_stack裡面，並且進入function，將x的值設定為3，執行(+ x 1)的分析，計算後得到結果4，function執行完成後，將param_stack pop掉 清空。

```
(print-num ((fun (a b) (+ a b)) 4 5))
```
```
        print-num
           |
          fun
         /   \
        /     \
      params   (+)
      /   \    / \
     a     b  a   b

```

4和5會被push到param_stack裡面，並且進入function，將a跟b的值設定為4跟5，執行(+ a b)的分析，計算後得到結果9，function執行完成後，將param_stack pop掉 清空。