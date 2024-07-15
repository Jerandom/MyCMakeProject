#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <regex>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <format>

using namespace std;

class InterviewQ 
{
public:
	int findMedian(std::vector<int> arr);

	int diagonalDifference(std::vector<std::vector<int>> arr);

	bool isPalindrome(const std::string& str, int start, int end);
	int palindromeIndex(std::string s);

	int TruckQuestion(std::vector<int> numberOfBoxes, std::vector<int> unitsPerBox, int truckSize);

	std::string reverse_words(std::string str);

	std::string timeConversion24Hr(std::string s);

	std::vector<int> matchingStrings(std::vector<std::string> strings, std::vector<std::string> queries);

	std::vector<int> frequencyStrings(std::vector<std::string> strings);

	std::vector<int> countingSort(std::vector<int> num);

	std::vector<int> climbingLeaderboard(std::vector<int> ranked, std::vector<int> player);

	unordered_map<char, int> charFrequencyMap(const string& input);
	bool canFormWord(const unordered_map<char, int>& inputCharMap, const unordered_map<char, int>& wordCharMap);
	string findWord(vector<string> words, string input);
};

#if 0
{
	// Define a struct for the node of the linked list
	struct Node 
	{
		int data;
		Node* next;

		// Constructor to initialize data and next pointer
		Node(int val) : data(val), next(nullptr) {}
	};

	// Define a class for the linked list
	class LinkedList 
	{
	private:
		Node* head; // Pointer to the head of the linked list

	public:
		// Constructor to initialize the head pointer
		LinkedList() : head(nullptr) {}

		// Function to insert a new node at the beginning of the linked list
		void insertAtBeginning(int val)
		{
			Node* newNode = new Node(val);
			newNode->next = head;
			head = newNode;
		}

		// Function to print the linked list
		void printList()
		{
			Node* temp = head;
			while (temp != nullptr)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << endl;
		}

		// Function to merge two linked lists
		LinkedList* mergeLists(LinkedList* head1, LinkedList* head2)
		{
			if (head1->head == nullptr)
			{
				return head2;
			}
			if (head2->head == nullptr)
			{
				return head1;
			}

			Node* temp = head1->head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = head2->head;

			return head1;
		}

		// Function to sort a linked list using std::sort
		void sortLinkedList(LinkedList* head)
		{
			// Copy elements of linked list to a vector
			vector<int> elements;
			Node* temp = head->head;
			while (temp != nullptr)
			{
				elements.push_back(temp->data);
				temp = temp->next;
			}

			// Sort the vector
			sort(elements.begin(), elements.end());

			// Update the linked list with sorted elements
			temp = head->head;
			for (int element : elements)
			{
				temp->data = element;
				temp = temp->next;
			}
		}
	};
}
#endif
