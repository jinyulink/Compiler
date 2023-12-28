//Compiler First Set 
//110403518 資工3B 林晉宇
#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<string>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> first_sets;

void read_grammar(map<char, vector<string>>& grammar) {
    string line;
    while (getline(cin, line) && line != "END_OF_GRAMMAR") {
        char nonterminal = line[0];
        vector<string> productions;
        size_t pos = 2; // 跳過非終結符和空格
        while (pos < line.size()) {
            size_t next_pos = line.find('|', pos);
            if (next_pos == string::npos) {
                productions.push_back(line.substr(pos));
                break;
            }
            productions.push_back(line.substr(pos, next_pos - pos));
            pos = next_pos + 1;
            // 這個while裡面再做的就是把每個rule分開成個別的string，存在vector
        }
        grammar[nonterminal] = productions;
    }
}

void add_first_set(map<char, set<char>>& first_sets, char nonterminal, char symbol, const map<char, vector<string>>& grammar) {
    // 首先檢查符號是否是非終結符
    if (grammar.find(symbol) != grammar.end()) {
        // 如果符號是非終結符，則添加其 First Set
        for (char sym : first_sets[symbol]) {
            if (sym != ';') {  // 假設 ';' 代表 epsilon
                first_sets[nonterminal].insert(sym);
            }
        }
    } else {
        // 如果符號是終結符或 epsilon，直接添加到非終結符的 First Set 中
        first_sets[nonterminal].insert(symbol);
    }
}

void calculate_first_sets(const map<char, vector<string>>& grammar, map<char, set<char>>& first_sets) {
    for (auto& rule : grammar) {
        first_sets[rule.first] = set<char>(); // initialize first set
    }

    // 變數用於確定是否需要再次迭代
    bool changed;
    do {
        changed = false;
        for (const auto& rule : grammar) {
            char nonterminal = rule.first;
            for (const auto& production : rule.second) {
                size_t prev_size = first_sets[nonterminal].size();
                if (!production.empty()) {
                    // If the first symbol is a terminal or an epsilon, add it to the first set
                    if (islower(production[0]) || production[0] == ';' || production[0] == '$') {
                        first_sets[nonterminal].insert(production[0]);
                    } else {
                        // If the first symbol is a nonterminal, add its first set to the nonterminal's first set
                        // If it includes epsilon, continue with the next symbols
                        bool epsilon_found = true;
                        for (char prod_symbol : production) {
                            if (!epsilon_found) break;
                            epsilon_found = false;
                            add_first_set(first_sets, nonterminal, prod_symbol, grammar);
                            // Check if this symbol's first set contains epsilon
                            if (first_sets[prod_symbol].find(';') != first_sets[prod_symbol].end()) {
                                epsilon_found = true;
                            }
                        }
                        // If all symbols in the production can go to epsilon, add epsilon to the nonterminal's first set
                        if (epsilon_found) {
                            first_sets[nonterminal].insert(';');
                        }
                    }
                }
                // Check if we have added any new symbols to the first set in this iteration
                if (first_sets[nonterminal].size() != prev_size) {
                    changed = true;
                }
            }
        }
    } while (changed);
}

int main(){
    read_grammar(grammar);
    calculate_first_sets(grammar, first_sets);

    for(auto first_set : first_sets){
        if(first_set.first < 'A' || first_set.first > 'Z') {
            continue;
        }
        cout << first_set.first << " "; // 輸出 Nonterminal 字母
        for(char terminal : first_set.second){
            cout << terminal;
        }
        cout << '\n';
    }
    cout << "END_OF_FIRST\n";

    return 0;
}