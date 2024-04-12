#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

class InterviewQ 
{
public:
	int findMedian(std::vector<int> arr);

	int diagonalDifference(std::vector<std::vector<int>> arr);


	bool isPalindrome(const std::string& str, int start, int end);
	int palindromeIndex(std::string s);
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
