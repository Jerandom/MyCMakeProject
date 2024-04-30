// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to create a character frequency map from a given string
unordered_map<char, int> charFrequencyMap(const string& input) 
{
    unordered_map<char, int> charCount;
    for (const char& c : input) {
        charCount[c]++;
    }
    return charCount;
}

// Function to check if the character frequency of 'word' can be satisfied by 'inputCharMap'
bool canFormWord(const unordered_map<char, int>& inputCharMap, const unordered_map<char, int>& wordCharMap) {
    for (const auto& pair : wordCharMap) 
    {
        char c = pair.first;
        int wordCount = pair.second;

        // Check if 'c' exists in 'inputCharMap' with at least 'wordCount' times
        if (inputCharMap.find(c) == inputCharMap.end() || inputCharMap.at(c) < wordCount) 
        {
            return false;
        }
    }
    return true;
}

string findWord(vector<string> words, string input) 
{
    unordered_map<char, int> inputCharMap = charFrequencyMap(input);

    for (const auto word : words) 
    {
        unordered_map<char, int> wordCharMap = charFrequencyMap(word);

        // If 'inputCharMap' can form 'word', return the word
        if (canFormWord(inputCharMap, wordCharMap)) 
        {
            return word;
        }
    }
    return ""; // No matching word found
}

int main() 
{
    string input = "hasdhuoy";

    vector<string> words = { "hello", "world" , "how", "are", "you" };

	findWord(words, input);
    return 0;
}
