#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

bool isKeyword(const string &word) {
    const set<string> keywords = {
        "int", "float", "double", "char", "void", "return", "if", "else", "for", "while", "do", "switch", "case",
        "break", "continue", "default", "const", "main", "include", "define", "cout", "cin", "endl"
    };
    return keywords.find(word) != keywords.end();
}

bool isFunctionDeclaration(const string &line) {
    return line.find('(') != string::npos && line.find(')') != string::npos;
}

void extractVariables(const string &line, set<string> &variables) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
        if (isKeyword(word) || isFunctionDeclaration(line)) {
            continue;
        }
        while (!word.empty() && (word.back() == ',' || word.back() == ';' || word.back() == '=')) {
            word.pop_back();
        }
        if (!word.empty() && !isKeyword(word)) {
            variables.insert(word);
        }
    }
}

int main() {
    ifstream file("program.cpp");
    if (!file) {
        cerr << "Unable to open file!" << endl;
        return 1;
    }
    set<string> variables;
    set<string> preprocessors;
    string line;
    while (getline(file, line)) {
        if (line.find("#include") != string::npos) {
            preprocessors.insert("include");
        }
        if (line.find("#define") != string::npos) {
            preprocessors.insert("define");
        }

        if (line.find("int ") != string::npos) {
            extractVariables(line, variables);
        }
    }
    file.close();
    int varCount = 1;
    for (const string &var : variables) {
        cout << "Variable-" << varCount++ << ": " << var << endl;
    }
    cout << "Total number of variables: " << variables.size() << endl;

    int preprocessorCount = 1;
    for (const string &pre : preprocessors) {
        cout << "Preprocessor-" << preprocessorCount++ << ": " << pre << endl;
    }
    cout << "Total number of preprocessors: " << preprocessors.size() << endl;

    return 0;
}
