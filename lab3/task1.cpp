#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

bool isValidIdentifier(string test) {
    if (!((test[0] >= 'A' && test[0] <= 'Z') || (test[0] >= 'a' && test[0] <= 'z') || test[0] == '_')) {
        return false;
    }
    for (int i = 1; i < test.length(); i++) {
        if (!((test[i] >= 'A' && test[i] <= 'Z') || (test[i] >= 'a' && test[i] <= 'z') || (test[i] >= '0' && test[i] <= '9') || test[i] == '_')) {
            return false;
        }
    }
    return true;
}

bool isKeyword(string token) {
    string keywords[] = {"int", "float", "double", "char", "return", "if", "else", "while", "for", "cout"};
    for (string keyword : keywords) {
        if (token == keyword) {
            return true;
        }
    }
    return false;
}

bool isOperator(string token) {
    string operators[] = {"+", "-", "*", "/", "%", "=", "<<", ">>", "<", ">"};
    for (string op : operators) {
        if (token == op) {
            return true;
        }
    }
    return false;
}

bool isPunctuation(char ch) {
    char punctuations[] = {',', ';', '{', '}'};
    for (char punc : punctuations) {
        if (ch == punc) {
            return true;
        }
    }
    return false;
}

int main() {
    // Save input to file
    ofstream MyFile("C://Users//student//Desktop//NewFile.txt");
    if (!MyFile) {
        cerr << "Could not create the file!" << endl;
        return 1;
    }
    MyFile << "int main\n{\nfloat a,b;\nint sum;\nsum = a+b;\ncout<<sum;\n}";
    MyFile.close();

    // Read from file
    ifstream file("C://Users//student//Desktop//NewFile.txt");
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    // Sets to store unique tokens
    set<string> keywords, identifiers, operators, punctuations;
    string token = "";
    string line;

    while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];

            // Handle multi-character operators (e.g., "<<", ">>")
            string twoCharOp = "";
            if (i + 1 < line.length()) {
                twoCharOp = line.substr(i, 2);
            }

            if (ch == ' ' || isOperator(string(1, ch)) || isPunctuation(ch) || (!twoCharOp.empty() && isOperator(twoCharOp))) {
                if (!token.empty()) {
                    if (isKeyword(token)) {
                        keywords.insert(token);
                    } else if (isValidIdentifier(token)) {
                        identifiers.insert(token);
                    }
                    token = ""; // Reset token for the next word
                }

                // Classify operators and punctuations
                if (!twoCharOp.empty() && isOperator(twoCharOp)) {
                    operators.insert(twoCharOp);
                    i++; // Skip the next character as it is part of a two-character operator
                } else if (isOperator(string(1, ch))) {
                    operators.insert(string(1, ch));
                } else if (isPunctuation(ch)) {
                    punctuations.insert(string(1, ch));
                }
            } else {
                // Add character to current token
                token += ch;
            }
        }

        // Final check for the last token in the line
        if (!token.empty()) {
            if (isKeyword(token)) {
                keywords.insert(token);
            } else if (isValidIdentifier(token)) {
                identifiers.insert(token);
            }
            token = "";
        }
    }

    file.close();

    // Display results
    cout << "Keywords: ";
    for (const auto &kw : keywords) cout << kw << " ";
    cout << endl;

    cout << "Identifiers: ";
    for (const auto &id : identifiers) cout << id << " ";
    cout << endl;

    cout << "Operators: ";
    for (const auto &op : operators) cout << op << " ";
    cout << endl;

    cout << "Punctuations: ";
    for (const auto &punc : punctuations) cout << punc << " ";
    cout << endl;

    return 0;
}
