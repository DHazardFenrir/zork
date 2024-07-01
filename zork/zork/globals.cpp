#include "globals.h"
#include <sstream>
#include <iostream>

void Tokenize(const string& str, vector<string>& tokens) {
    istringstream iss(str);
    string token;
    while (getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
}

bool Same(const string& str1, const string& str2) {
    return str1 == str2;
}

bool CheckArgsSize(const vector<string>& args, size_t expected_size) {
    return args.size() == expected_size;
}

void PrintInvalidCommand() {
    cout << "\nSorry, I do not understand your command.\n";
}
