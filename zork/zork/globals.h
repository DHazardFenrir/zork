#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <string>
#include <vector>
#include <memory>

using namespace std;

// Tokenize function
void Tokenize(const string& str, vector<string>& tokens);

// Check if two strings are the same
bool Same(const string& str1, const string& str2);

// Helper functions
bool CheckArgsSize(const vector<string>& args, size_t expected_size);
void PrintInvalidCommand();

#endif // __GLOBALS_H__