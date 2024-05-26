// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <regex>
#include <algorithm>
#include <cassert>

#include "QRGenerator/QrCodeManager.h"

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

int main() 
{

    QrCodeManager::instance().generateHighResQRCode("Hello World", 10, 1);
    cout<<"Hello World!";

    return 0;
}
