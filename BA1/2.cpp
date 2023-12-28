//Compiler Boss Attack 1-1 Parser
//110403518 林晉宇 資工3B

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
string month[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

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

    bool check(string m){
        for(auto i:month){
            if(m == i)  return true;
        }
        return false;
    }

public:
    Scanner(string& input): input(input) {}

    void putBackToken() {
        pos = prevPos;
    }
    Token getNextToken(){
        while(peek() == ' ') consume();

        if(peek() == '\0')  return {"END", ""};
        else if(peek() - 'A' <= 25 && peek() - 'A' >= 0){
            string tmp = "";
            prevPos = pos;
            tmp += consume();
            while(isdigit(peek())){
                tmp += consume();
            }
            if(tmp.length() == 10){
                return {"ID", tmp};
            }

            while(isalpha(peek())){
                tmp += consume();
            }
            if(check(tmp)){
                return {"MONTH", tmp};
            }
        }
        else if(peek() == '+'){
            prevPos = pos;
            consume();
            return {"PLUS", "+"};
        }
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
        else if(peek() == '/'){
            prevPos = pos;
            consume();
            return {"SLASH", "/"};
        }
        else if(peek() == '9'){
            prevPos = pos;
            string phone = "";
            while(isdigit(peek())){
                phone += consume();
            }
            if(phone.length() == 9){
                return {"PHONENUM", phone};
            }
            putBackToken();
        }

        if(isdigit(peek())){
            prevPos = pos;
            string nation = "";
            while(isdigit(peek())){
                nation += consume();
            }
            if(nation.length() == 3){
                return {"NATIONNUM", nation};
            }
            putBackToken();
        }

        if(peek() == '1' || peek() == '2'){
            prevPos = pos;
            string year = "";
            while(isdigit(peek())){
                year += consume();
            }
            if(year.length() == 4){
                return {"YEAR", year};
            }
            putBackToken();
        }

        if(isdigit(peek())){
            prevPos = pos;
            string day = "";
            while(isdigit(peek())){
                day += consume();
            }
            if(stoi(day) - 0 <= 31){
                return {"DAY", day};
            }
            putBackToken();
        }

        return {"INVALID", ""};
    }
};

bool Date(Scanner& scanner){
    Token t = scanner.getNextToken();
    if(t.type == "MONTH"){
        tokens.push_back(t);
        Token next = scanner.getNextToken();
        if(next.type == "DOT"){
            tokens.push_back(next);
            Token next = scanner.getNextToken();
            if(next.type == "DAY"){
                tokens.push_back(next);
                Token next = scanner.getNextToken();
                if(next.type == "DOT"){
                    tokens.push_back(next);
                    Token next = scanner.getNextToken();
                    if(next.type == "YEAR"){
                        tokens.push_back(next);
                        return true;
                    }
                    else    scanner.putBackToken();
                }
                else    scanner.putBackToken();
            }
            else    scanner.putBackToken();
        }
        else    scanner.putBackToken();
    }
    else if(t.type == "YEAR"){
        tokens.push_back(t);
        Token next = scanner.getNextToken();
        if(next.type == "SLASH"){
            tokens.push_back(next);
            Token next = scanner.getNextToken();
            if(next.type == "MONTH"){
                tokens.push_back(next);
                Token next = scanner.getNextToken();
                if(next.type == "SLASH"){
                    tokens.push_back(next);
                    Token next = scanner.getNextToken();
                    if(next.type == "DAY"){
                        tokens.push_back(next);
                        return true;
                    }
                    else    scanner.putBackToken();
                }
                else    scanner.putBackToken();
            }
            else    scanner.putBackToken();
        }
        else    scanner.putBackToken();
    }
    else    scanner.putBackToken();
    return false;
}

bool Phone(Scanner& scanner){
    Token t = scanner.getNextToken();
    if(t.type == "PLUS"){
        tokens.push_back(t);
        Token next = scanner.getNextToken();
        if(next.type == "LBR"){
            tokens.push_back(next);
            next = scanner.getNextToken();
            if(next.type == "NATIONNUM"){
                tokens.push_back(next);
                next = scanner.getNextToken();
                if(next.type == "RBR"){
                    tokens.push_back(next);
                    next = scanner.getNextToken();
                    if(next.type == "PHONENUM"){
                        tokens.push_back(next);
                        return true;
                    }
                    else    scanner.putBackToken();
                }
                else    scanner.putBackToken();
            }
            else    scanner.putBackToken();
        }
        else    scanner.putBackToken();
    }
    else    scanner.putBackToken();
    return false;
}

bool Stmt(Scanner& scanner){
    Token t = scanner.getNextToken();
    if(t.type == "ID"){
        tokens.push_back(t);
        return true;
    }
    else if(t.type == "INVALID"){
        cout << "Invalid input\n";
        exit(0);
    }
    else if (t.type == "END")    return false;
    else    scanner.putBackToken();

    if(Phone(scanner)){
        return true;
    }
    else if(Date(scanner)){
        return true;
    }
    return false;
}

bool parseProg(Scanner& scanner){
    // cout << "prog\n";
    return Stmt(scanner);
}

int main(){
    string s;
    while(getline(cin, s)){
        input += s + " "; 
    }
    // getline(cin,s);
    // input += s;
    Scanner scanner(input);

    if (parseProg(scanner)) {
        for(unsigned int i = 0; i < tokens.size(); i++){
            Token t = tokens[i];
            cout << t.lexeme << ' ' << t.type << '\n';
        }
    }
    else    cout << "Invalid input\n";
    return 0;
}