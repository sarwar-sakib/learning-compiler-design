#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

// Function to check for balanced parentheses
bool areParenthesesBalanced(const string& str) {
    stack<char> s;
    for (char c : str) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty() || s.top() != '(') return false;
            s.pop();
        }
    }
    return s.empty();
}

// Function to check if a string is a valid integer expression
bool isValidIntExpression(const string& str) {
    for (char c : str) {
        if (!isalnum(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != ' ') {
            return false; // Invalid character for an int expression
        }
    }
    return true;
}

// Function to validate return types
bool isValidReturnType(const string& declaredType, const string& returnedValue) {
    if (declaredType == "int") {
        return !returnedValue.empty() && isValidIntExpression(returnedValue);
    } else if (declaredType == "bool") {
        return returnedValue == "true" || returnedValue == "false";
    } else if (declaredType == "float" || declaredType == "double") {
        bool hasDot = false;
        return !returnedValue.empty() && all_of(returnedValue.begin(), returnedValue.end(), [&hasDot](char c) {
            if (c == '.') {
                if (hasDot) return false;
                hasDot = true;
                return true;
            }
            return isdigit(c) || c == '-';
        });
    } else if (declaredType == "char") {
        return returnedValue.size() == 3 && returnedValue.front() == '\'' && returnedValue.back() == '\'';
    } else if (declaredType == "string") {
        return returnedValue.size() >= 2 && returnedValue.front() == '"' && returnedValue.back() == '"';
    } else if (declaredType == "void") {
        return returnedValue.empty();
    }
    return false;
}

// Function to check if a function name is valid
bool isValidFunctionName(const string& functionName) {
    if (functionName.empty() || !isalpha(functionName[0])) {
        return false; // Function name must start with an alphabet
    }
    for (char c : functionName) {
        if (!isalnum(c) && c != '_') {
            return false; // Function name must be alphanumeric or underscore
        }
    }
    return true;
}

// Function to validate function definitions
void checkFunctionDefinition(const string& function) {
 
    cout << "Line: " << function << endl;

    // Find the return type, function name, parameters, and return value
    size_t firstSpace = function.find(' ');
    size_t firstParen = function.find('(');
    size_t lastParen = function.rfind(')');
    size_t braceOpen = function.find('{');
    size_t returnPos = function.find("return");

    if (firstSpace == string::npos || firstParen == string::npos || lastParen == string::npos || braceOpen == string::npos) {
        cout << "Missing key components." << endl;
        return;
    }

    string returnType = function.substr(0, firstSpace);
    string functionName = function.substr(firstSpace + 1, firstParen - firstSpace - 1);
    string parameters = function.substr(firstParen + 1, lastParen - firstParen - 1);
    string returnedValue = (returnPos != string::npos) ? function.substr(returnPos + 7, function.find(';', returnPos) - returnPos - 7) : "";

    // Check if the function name is valid
    if (!isValidFunctionName(functionName)) {
        cout << "Invalid function name: " << functionName << "." << endl;
        return;
    }

    // Check for syntax errors in parameters
    if (parameters.find(",,") != string::npos) {
        cout << "Invalid function definition: Double commas found in parameter list." << endl;
        return;
    }
    if (!areParenthesesBalanced(parameters)) {
        cout << "Invalid: Unbalanced parentheses." << endl;
        return;
    }

    // Check return type and return value
    if (!isValidReturnType(returnType, returnedValue)) {
        cout << "Invalid return type or function definition for " << functionName << "." << endl;
    } else {
        cout << "Valid return type for " << functionName << " with proper definition." << endl;
    }

    cout << endl;
}

// Main function to demonstrate and test the program
int main() {
    vector<string> functions = {
        "int sum(int a, int b) { return a + b; }",
        "bool isValid(){return true;}",
        "bools isInvalid(){return false}",
        "int 123Valid() { return 0; }"
    };

    cout <<endl;
    for (const string& function : functions) {
        checkFunctionDefinition(function);
    }

    return 0;
}
