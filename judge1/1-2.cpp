//Compiler HW 1-2 Scanner
//110403518 林晉宇 資工3B
#include<iostream>

using namespace std;

string input;

void scan(string input){

    string tmp = "";

    for(unsigned int i = 0; i < input.size(); i++){

        char c = input[i];
        
        if(c - '0' >= 0 && c - '0' <= 9){
            tmp += c;
        }
        else if(tmp != ""){
            cout << "NUM " << tmp << '\n';
            tmp = "";
        }

        if(c == '+'){
            cout << "PLUS\n";
        }
        else if(c == '-'){
            cout << "MINUS\n";
        }
        else if(c == '*'){
            cout << "MUL\n";
        }
        else if(c == '/'){
            cout << "DIV\n";
        }
        else if(c == '('){
            cout << "LPR\n";
        }
        else if(c == ')'){
            cout << "RPR\n";
        }
    }
    if(tmp != ""){
        cout << "NUM " << tmp << '\n';
    }
}

int main(){
    char c;
    while(cin >> c){
        if(c != ' ')   input += c;
    }
    scan(input);
    return 0;
}