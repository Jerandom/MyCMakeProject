// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <regex>
#include <algorithm>
#include <cassert>

using namespace std;

string reverse_words(string str) 
{
    string result = "";
    string matchWord = "";
    int currentPos = 0;
    int strPos = 0;
    regex pattern("[a-zA-Z0-9]+");

    sregex_iterator iterator(str.begin(), str.end(), pattern); 
    sregex_iterator end; 

    while (iterator != end)
    {
        smatch match = *iterator;

        //append the non match part
        strPos = match.position();
        result.append(str, currentPos, strPos - currentPos);

        //filter and reverse the words, then append to string
        matchWord = match.str();
        reverse(matchWord.begin(), matchWord.end());
        result.append(matchWord);

        currentPos = strPos + matchWord.length();

        ++iterator;
    }

    if (currentPos < str.length()) 
    {
        result.append(str, currentPos, str.length() - currentPos);
    }

    return result;
}

int main() {
    string test_str = "hello32!~! world+-)";
    assert(reverse_words(test_str) == "23olleh!~! dlrow+-)");

    test_str = "String; 2be reversed...";
    assert(reverse_words(test_str) == "gnirtS; eb2 desrever...");

    test_str = "@@(#*()#@*..@(#*@(";
    assert(reverse_words(test_str) == "@@(#*()#@*..@(#*@(");
    return 0;
}
