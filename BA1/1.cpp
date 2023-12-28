//Compiler Boss Attack 1-1 Scanner
//110403518 林晉宇 資工3B

#include<iostream>
#include<vector>
#include<string>
#include<cctype>

using namespace std;

string input;
struct Token{
    string type;
    string lexeme;
};
vector<Token> tokens;
char symbol[12] = {'+', '-', '*', '/', '=', '(', ')', '{', '}', '<', '>', ';'};

class Scanner {
private:
    string input;
    size_t pos = 0;

    char peek(){
        return pos < input.size() ? input[pos] : '\0';
    }

    char consume(){
        return input[pos++];
    }

    bool check(char c){
        for(auto i:symbol){
            if(c == i)  return true;
        }
        return false;
    }

public:
    Scanner(string& input): input(input) {}

    Token getNextToken(){
        while(peek() == ' ') consume();

        if(peek() == '\0')  return {"END", ""};
        else if(isdigit(peek())){
            string num = "";
            while(isdigit(peek())){
                num += consume();
            }
            return {"NUM", num};
        }
        else if(isalpha(peek()) || peek() == '_'){
            string id = "";
            while(isdigit(peek()) || isalpha(peek()) || peek() == '_'){
                id += consume();
            }
            if(id == "if" || id == "else" || id == "while"){
                return {"KEYWORD", id};
            }
            else{
                return {"IDENTIFIER", id};
            }
        }
        else if(check(peek())){
            string sym = "";
            sym += consume();
            return {"SYMBOL", sym};
        }
        else {
            consume();
            return {"Invalid", ""};
        }
        return {"Invalid", ""};
    }
};

int main(){
    string s;
    while(getline(cin, s)){
        input += s + " ";
    }
    // getline(cin, s);
    // input += s;
    Scanner scanner(input);
    Token t = scanner.getNextToken();
    while(t.type != "END"){
        tokens.push_back(t);
        t = scanner.getNextToken();
    }
    for(unsigned int i = 0; i < tokens.size(); i++){
        Token t = tokens[i];
        if(t.type == "Invalid"){
            cout << t.type << '\n';
        }
        else cout << t.type << ' ' << '\"' << t.lexeme << '\"' << '\n';
    }
    return 0;
}