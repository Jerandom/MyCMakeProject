// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

int findMedian(vector<int> arr) 
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

int diagonalDifference(vector<vector<int>> arr)
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

bool isPalindrome(const std::string& str, int start, int end) {
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

int palindromeIndex(string s)
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

int main() {
    palindromeIndex("aabaabcaweq");

    return 0;
}
