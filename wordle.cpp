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
void generateWords(const string& in, const string& floating, string& current, size_t index, const set<string>& dict, set<string>& result, map<char, int>& floatingCounts, size_t usedFloatingCount);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;
    string current = in;
    map<char, int> floatingCounts;
    for (char c : floating) {
        if (floatingCounts.find(c) == floatingCounts.end()) floatingCounts[c] = 1;
        else floatingCounts[c]++;
    }
    generateWords(in, floating, current, 0, dict, result, floatingCounts, 0);
    return result;
}

// Define any helper functions here
void generateWords(const string& in, const string& floating, string& current, size_t index, const set<string>& dict, set<string>& result, map<char, int>& floatingCounts, size_t usedFloatingCount) {
    if (index == in.length()) {
        if (dict.find(current) != dict.end() && usedFloatingCount == floating.size()) {
            result.insert(current);
        }
        return;
    }
    
    if (in[index] != '-') {
        generateWords(in, floating, current, index + 1, dict, result, floatingCounts, usedFloatingCount);
    } else {
        for (char c = 'a'; c <= 'z'; ++c) {
            bool usedFloating = false;
            if (floatingCounts.find(c) != floatingCounts.end() && floatingCounts[c] > 0) {
                usedFloating = true;
                floatingCounts[c]--;
                usedFloatingCount++;
            }
            current[index] = c;
            generateWords(in, floating, current, index + 1, dict, result, floatingCounts, usedFloatingCount);
            current[index] = '-';
            if (usedFloating) {
                floatingCounts[c]++;
                usedFloatingCount--;
            }
        }
    }
}