#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("input1.txt");

    string line;
    int lineNumber = 1;
    bool insideBlock = false;

    while (getline(file, line)) {
        int j = line.length() - 1;
        while (j >= 0 && line[j] == ' ') {
            j--;
        }

        bool opensBlock = false;
        bool closesBlock = false;

        for (char ch : line) {
            if (ch == '{') {
                opensBlock = true;
            }
            if (ch == '}') {
                closesBlock = true;
            }
        }

        if (opensBlock) {
            insideBlock = true;
        }
        if (closesBlock) {
            insideBlock = false;
        }

        if (insideBlock && !opensBlock && !closesBlock) {
            if (j >= 0 && line[j] != ';') {
                cout << "Line " << lineNumber << ": Invalid: missing semicolon (;)" << endl;
            } else {
                cout << "Line " << lineNumber << ": Valid" << endl;
            }
        }

        lineNumber++;
    }

    file.close();
    return 0;
}
