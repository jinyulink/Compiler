//Compiler Parser test

#include<iostream>
#include<string>
#include<cctype>
#include<vector>

using namespace std;

string input;
struct Token{
    string type;
    string lexeme;
};
vector<Token> tokens;

class Scanner {
private:
    string input;
    size_t pos = 0;
    size_t prevPos = 0;

    char peek(){
        return pos < input.size() ? input[pos] : '\0';
    }

    char consume(){
        return input[pos++];
    }

public:
    Scanner(string& input): input(input) {}

    void putBackToken() {
        pos = prevPos;
    }

    Token getNextToken(){
        while(peek() == ' ') consume();

        if(peek() == '\0')  return {"END", ""};
        else if(peek() == '.'){
            prevPos = pos;
            consume();
            return {"DOT", "."};
        }
        else if(peek() == '('){
            prevPos = pos;
            consume();
            return {"LBR", "("};
        }
        else if(peek() == ')'){
            prevPos = pos;
            consume();
            return {"RBR", ")"};
        }
        else if(peek() == '"'){
            string tmp = "\"";
            prevPos = pos;
            consume();
            while(peek() != '"' && peek() != '\0'){
                tmp += consume();
            }
            if(peek() == '"'){
                tmp += consume();
                return {"STRLIT", tmp};
            }
            else{
                return {"INVALID", ""};
            }
        }
        else if(isalpha(peek()) || peek() == '_'){
            string id = "";
            prevPos = pos;
            while(isdigit(peek()) || isalpha(peek()) || peek() == '_'){
                id += consume();
            }
            return {"ID", id};
        }

        return {"INVALID", ""}; // 
    }
};

bool PrimaryTail(Scanner& scanner);
bool Stmt(Scanner& scanner);

bool PrimaryTail(Scanner& scanner) {
    // cout << "primarytail\n";
    Token t = scanner.getNextToken();

    if(t.type == "INVALID"){
        cout << "invalid input\n";
        exit(0);
    }
    else if (t.type == "END")    return false;
    else if (t.type == "DOT") {
        tokens.push_back(t);
        Token next = scanner.getNextToken();
        if (next.type == "ID") {
            tokens.push_back(next);
            return PrimaryTail(scanner);
        }
    } else if (t.type == "LBR") {
        tokens.push_back(t);
        if (Stmt(scanner)) {
            Token rbr = scanner.getNextToken();
            if (rbr.type == "RBR") {
                tokens.push_back(rbr);
                return PrimaryTail(scanner);
            }
        }
    }
    else    scanner.putBackToken();
    return true;
}

bool Primary(Scanner& scanner) {
    // cout << "primary\n";
    Token t = scanner.getNextToken();
    // cout << t.type << " " << t.lexeme << '\n';
    if(t.type == "INVALID"){
        cout << "invalid input\n";
        exit(0);
    }
    else if (t.type == "END")    return false;
    else if (t.type == "ID") {
        tokens.push_back(t);
        return PrimaryTail(scanner);
    }
    else    scanner.putBackToken();
    return false;
}

bool Stmt(Scanner& scanner) {
    // cout << "stmt\n";
    if (Primary(scanner)) {
        return true;
    }

    Token t = scanner.getNextToken();
    // cout << t.type << " " << t.lexeme << '\n';
    if(t.type == "INVALID"){
        cout << "invalid input\n";
        exit(0);
    }
    else if (t.type == "END")    return false;
    else if (t.type == "STRLIT") {
        tokens.push_back(t);
        return true;
    }
    else    scanner.putBackToken();  // For the λ or empty case
    return true; 
}

bool Stmts(Scanner& scanner){
    // cout << "stmts\n";
    if(Stmt(scanner)){
        return Stmts(scanner);
    }
    return true; 
}

bool parseProg(Scanner& scanner){
    // cout << "prog\n";
    return Stmts(scanner);
}

int main(){
    string s;
    while(getline(cin, s)){
        input += s + " "; //空格很重要 在連續的行之間並沒有插入空格或換行符，這意味著連續的輸入行會連接成一個單一的詞彙單元，這可能導致解析錯誤。
    }
    Scanner scanner(input);

    if (parseProg(scanner)) {
        for(unsigned int i = 0; i < tokens.size(); i++){
            Token t = tokens[i];
            cout << t.type << ' ' << t.lexeme << '\n';
        }
    }
    return 0;
}