#include <iostream>
#include <cstring>

using namespace std;

int i = 1, j = 0, no = 0, tmpch = 80;

char str[100], leftVar[15], rightVar[15];

void findopr();
void explore();
void fleft(int);
void fright(int);

struct Exp {
    int pos;
    char op;
} k[15];

int main() {
    cout << "\t\tINTERMEDIATE CODE GENERATION\n\n";
    cout << "Enter the Expression: ";
    cin >> str;
    cout << "The intermediate code:\n";
    findopr();
    explore();
    return 0;
}

void findopr() {

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '*' || str[i] == '/')
            k[j].pos = i, k[j++].op = str[i];

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '+' || str[i] == '-')
            k[j].pos = i, k[j++].op = str[i];
}

void explore() {
    i = 0;
    while (i < j) {
        fleft(k[i].pos);
        fright(k[i].pos);
        str[k[i].pos] = tmpch++;
        cout << "\t" << str[k[i].pos] << " := " << leftVar << k[i].op << rightVar << endl;
        i++;
    }

    fright(-1);
    if (no == 0) {
        fleft(strlen(str));
        cout << "\t" << rightVar << " := " << leftVar << endl;
    } else {
        cout << "\t" << rightVar << " := " << str[k[--i].pos] << endl;
    }
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '=' && str[x] != '\0' &&
           str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) {
            leftVar[w++] = str[x];
            leftVar[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '\0' &&
           str[x] != '=' && str[x] != ':' && str[x] != '-' && str[x] != '/') {
        if (str[x] != '$' && flag == 0) {
            rightVar[w++] = str[x];
            rightVar[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
}
