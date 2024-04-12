#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(string in, string floating, const set<string>& dict, set<string>& result);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;
    generateWords(in, floating, dict, result);
    return result;
}

// Define any helper functions here
void generateWords(string in, string floating, const set<string>& dict, set<string>& result) {
    size_t pos = in.find('-');
    if (pos == string::npos) { 
        if (dict.find(in) != dict.end()) { 
            result.insert(in);
        }
        return;
    }

    for (size_t i = 0; i < in.length(); ++i) {
        if(in[i] == '-'){
            if (!floating.empty()) {
                char currentChar = floating[0];
                string nextUnused = floating;
                nextUnused = nextUnused.substr(1);
                in[i] = currentChar;
                generateWords(in, nextUnused, dict, result); 
            }else {
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    in[i] = ch;
                    generateWords(in, floating, dict, result); 
                }
            }
            in[i] = '-';
        }
        
    } 
}

