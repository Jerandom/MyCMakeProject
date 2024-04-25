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
