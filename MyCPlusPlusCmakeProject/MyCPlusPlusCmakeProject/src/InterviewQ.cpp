#include "InterviewQ.h"

int InterviewQ::findMedian(std::vector<int> arr)
{
    std::sort(arr.begin(), arr.end());

    if (arr.size() % 2 == 0)
    {
        int middle1 = arr[arr.size() / 2];
        int middle2 = arr[arr.size() / 2 - 1];
        return (middle1 + middle2) / 2.0;
    }
    else
    {
        return arr[arr.size() / 2];
    }
}

int InterviewQ::diagonalDifference(std::vector<std::vector<int>> arr)
{
    int primaryDiagonalSum = 0;
    int secondaryDiagonalSum = 0;

    int n = arr.size(); // Assuming it's a square matrix

    // Calculate sum of primary diagonal (top-left to bottom-right)
    for (int i = 0; i < n; i++)
    {
        primaryDiagonalSum += arr[i][i];
    }

    // Calculate sum of secondary diagonal (top-right to bottom-left)
    for (int i = 0; i < n; i++)
    {
        secondaryDiagonalSum += arr[i][n - 1 - i];
    }

    // Calculate absolute difference between the two diagonals
    int diagonalDiff = abs(primaryDiagonalSum - secondaryDiagonalSum);

    return diagonalDiff;
}

bool InterviewQ::isPalindrome(const std::string& str, int start, int end)
{
    // Check if the substring str[start:end+1] is a palindrome
    while (start < end)
    {
        if (str[start] != str[end])
        {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int InterviewQ::palindromeIndex(std::string s)
{
    int start = 0;
    int end = s.length() - 1;

    while (start < end)
    {
        if (s[start] != s[end])
        {
            // Try removing either start or end character
            if (isPalindrome(s, start + 1, end))
            {
                return start;
            }
            if (isPalindrome(s, start, end - 1))
            {
                return end;
            }
            // If neither removal makes it a palindrome, return -1
            return -1;
        }
        start++;
        end--;
    }
    // String is already a palindrome or empty
    return -1;
}

int InterviewQ::TruckQuestion(std::vector<int> numberOfBoxes, std::vector<int> unitsPerBox, int truckSize)
{
    int highestUnits = 0;
    int index = 0;
    int sizeOfTruck = 0;

    int total = 0;

    for (int i = 0; i < numberOfBoxes.size(); i++)
    {
        if (highestUnits <= unitsPerBox[i])
        {
            highestUnits = unitsPerBox[i];
            index = numberOfBoxes[i];
            sizeOfTruck++;
            total += highestUnits;
            index--;

            while (index >= 1 && sizeOfTruck < truckSize)
            {
                sizeOfTruck++;
                index--;
                total += highestUnits;
            }

            highestUnits--;
        }

        if (sizeOfTruck == truckSize)
        {
            break;
        }
    }

    return total;
}

std::string InterviewQ::reverse_words(string str)
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

std::string InterviewQ::timeConversion24Hr(std::string s)
{
    tm time_info = {};
    stringstream ss(s);
    ss >> get_time(&time_info, "%I:%M:%S %p");

    // Check if the parsed hour is 12 (noon/midnight) and adjust accordingly
    if (s.find("PM") != string::npos && time_info.tm_hour != 12)
    {
        time_info.tm_hour += 12; // Add 12 hours for PM times (except for 12 PM)
    }
    else if (s.find("AM") != string::npos && time_info.tm_hour == 12)
    {
        time_info.tm_hour = 0; // Midnight
    }

    ostringstream oss;
    oss << put_time(&time_info, "%H:%M:%S");
    string time_24h_str = oss.str();
    return time_24h_str;
}

std::vector<int> InterviewQ::matchingStrings(std::vector<std::string> strings, std::vector<std::string> queries)
{
    unordered_map<string, int> freqMap;
    for (const string& str : strings)
    {
        freqMap[str]++;
    }

    vector<int> result;
    for (const string& query : queries)
    {
        result.push_back(freqMap[query]);
    }

    return result;
}

std::vector<int> InterviewQ::frequencyStrings(std::vector<std::string> strings)
{
    unordered_map<string, int> freqMap;
    vector<int> result;

    for (const string& str : strings)
    {
        freqMap[str]++;
    }

    for (const auto& pair : freqMap)
    {
        cout << pair.first << " : " << pair.second << endl;
        result.push_back(pair.second);
    }

    return result;
}

std::vector<int> InterviewQ::countingSort(std::vector<int> num)
{
    map<int, int> arrMap;
    vector<int> value;
    for (auto& count : num)
    {
        arrMap[count]++;
    }

    for (int i = 0; i < 100; i++)
    {
        if (arrMap.find(i) != arrMap.end())
        {
            value.push_back(arrMap[i]);
        }
        else
        {
            value.push_back(0);
        }
    }
    return value;
}

unordered_map<char, int> InterviewQ::charFrequencyMap(const string& input)
{
    unordered_map<char, int> charCount;
    for (const char& c : input) 
    {
        charCount[c]++;
    }
    return charCount;
}

bool InterviewQ::canFormWord(const unordered_map<char, int>& inputCharMap, const unordered_map<char, int>& wordCharMap)
{
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

string InterviewQ::findWord(vector<string> words, string input)
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