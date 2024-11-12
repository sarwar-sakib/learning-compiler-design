#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("input2.txt");

    string line;
    int lineNumber = 1;

    while (getline(file, line)) {
        int roundCount = 0;  
        int curlyCount = 0;  
        int squareCount = 0; 

        bool isValid = true;  

        for (char ch : line) {
            if (ch == '(') {
                roundCount++;  
            } else if (ch == ')') {
                roundCount--;  
               
            } else if (ch == '{') {
                curlyCount++;  
            } else if (ch == '}') {
                curlyCount--; 
               
            } else if (ch == '[') {
                squareCount++; 
            } else if (ch == ']') {
                squareCount--;
                
            }
        }

        if (isValid) {
            if (roundCount == 0 && curlyCount == 0 && squareCount == 0) {
                cout << "Line " << lineNumber << ": Valid parentheses" << endl;
            } else {
                cout << "Line " << lineNumber << ": Invalid (unmatched parentheses)" << endl;
            }
        }

        lineNumber++;
    }

    file.close();
    return 0;
}
