// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <regex>

using namespace std;

int main() {
    string text = "hello!~! world+-)";

    // Pattern to match alphabetic characters
    regex pattern("[a-zA-Z]+");

    sregex_iterator it(text.begin(), text.end(), pattern); // Create an iterator over all matches
    sregex_iterator end; // Default-constructed, represents end of iteration

    vector<string> words; // To store extracted words
    while (it != end) { // Loop over all matches
        words.push_back(it->str()); // Extract the matched string
        ++it; // Move to the next match
    }

    // Output all extracted alphabetic sequences
    cout << "Extracted words/letters: ";
    for (const auto& word : words) {
        cout << word << " ";
    }

    cout << endl;

    return 0;
}
