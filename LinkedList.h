
	// ################################################################################################################
	// ##																											 ##
	// ##											    INCLUDES													 ##
	// ##																											 ##
	// ################################################################################################################

#pragma once
#include <string>
#include <sstream>
#include "LinkedListInterface.h"
#include <typeinfo>

using namespace std;

// Using a template class
template<class T>
class LinkedList: public LinkedListInterface<T>
{
private:

	// ################################################################################################################
	// ##																											 ##
	// ##											CREATING NODES													 ##
	// ##																											 ##
	// ################################################################################################################

	// Every node contains 2 parts... 1. Data 2. Pointer to the next node
	struct Node {
		T data; // The data we are storing
		Node* next; // A pointer to the next node
		Node(const T& the_data, Node* next_val = NULL) :
			data(the_data) {next = next_val;}
	};

	// Mu list and number of items
	Node *mylist;
	int num_items;

public:

	// ################################################################################################################
	// ##																											 ##
	// ##										CONSTRUCTOR / DESTRUCTOR											 ##
	// ##																											 ##
	// ################################################################################################################

	// This is the constructor
	LinkedList(void) {
		mylist = NULL;
		num_items = 0;
	};

	// This is the destructor
	virtual ~LinkedList(void) {};

	// ################################################################################################################
	// ##																											 ##
	// ##											FUNCTIONS													     ##
	// ##																											 ##
	// ################################################################################################################

	// INSERTHEAD: Inserts value at the beginning of the list (shouldn't allow duplicates)
	virtual void insertHead(T value) {

		int list_size = size();
		int already_exists = 0;

		// If the size of the list is zero, insert
		if (list_size == 0) {
			Node *ptr = mylist;
			mylist = new Node(value);
			mylist->next = ptr;
			already_exists = 1;
		}

		// Otherwise make sure the value doesn't already exist
		else {

			// Loop through the list
			for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {

				// Get the value of the pointer
				if (ptr->data == value) {

					// Give a message
					cout << "This data value already exists" << endl;
					already_exists = 1;
					break;
				}
			}
		}

		// Other wise we are good to go
		if(already_exists != 1) {
			Node *ptr = mylist;
			mylist = new Node(value);
			mylist->next = ptr;
		}

	};

	// #################################################################################################################
	// #################################################################################################################

	// INSERT TAIL: Node with given value inserted at the end of the list.
	virtual void insertTail(T value) {

		// If the size of the list is zero
		int list_size = size();
		int already_exists = 0;

		// If the size of the list is zero, insert
		if (list_size == 0) {
			Node *ptr = mylist;
			mylist = new Node(value);
			mylist->next = ptr;
			return;
		}

		// Make sure the value doesn't already exist
		for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {

			// Get the value of the pointer
			if (ptr->data == value) {

				// Give a message
				cout << "This data value already exists" << endl;
				already_exists = 1;
				break;
			}
		}

		// If the pointer doesn't already exist
		if(already_exists != 1){

			// Traverse through the list
			for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {

				// Last one if next pointer is NULL
				if(ptr->next == NULL) {

					// Create a new node
					Node* new_node = new Node(value);

					// Make the next of new node = to NULL
					new_node->next = NULL;

					// Make next of pointer = to new_node
					ptr->next = new_node;

					// Return
					break;
				}
			}
		}

	};

	// #################################################################################################################
	// #################################################################################################################

	// INSERT AFTER: Node with given value inserted after node equal to "insertionNode".
	// Only add if "insertionNode" exists. No duplicates.
	virtual void insertAfter(T value, T insertionNode) {

		int already_exists = 0;

		// Make sure the value doesn't already exist
		for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {

			// Get the value of the pointer
			if (ptr->data == value) {

				// Give a message
				cout << "This data value already exists" << endl;
				already_exists = 1;
				break;
			}
		}

		// If the data value doesn't already exist
		if(already_exists != 1) {

			// Traverse through the list
			for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {

				// Go until we find the node equal to the insertion value
				if(ptr->data == insertionNode) {

					// Create a new node
					Node* new_node = new Node(value);

					// Make the next of new node the next of ptr
					new_node->next = ptr->next;

					// Make next of pointer = to new_node
					ptr->next = new_node;

				}
			}
		}
	};

	// #################################################################################################################
	// #################################################################################################################

	// REMOVE: Node with given value is removed
	// If the value to be removed is not in the list...
	virtual void remove(T value) {

		// Get the size of the list
		int list_size = size();
		int found;

		// If the size of the list is zero
		if(list_size == 0){
			return;
		}

		// If there is only 1 pointer in the list
		if(list_size == 1) {
			Node *head = mylist;
			delete head;
			mylist = NULL;
			return;
		}



		// Traverse through the list
		for(Node *ptr = mylist; ptr->next != NULL; ptr = ptr->next) {


			// If the value to remove is the head of the list
			if(ptr->data == value) {
				mylist = ptr->next;
				delete ptr;
				return;
			}

			// Create a temporary new pointer
			Node* temp = ptr->next;


			// Go until we find the node equal to the insertion value
			if(temp->data == value) {

				// Debugging
				cout << "The remove value " << value << " was found " << endl;

				// Skip the next pointer
				ptr->next = temp->next;

				// Delete the temporary?
				delete temp;
				break;

			}


		}
	};

	// #################################################################################################################
	// #################################################################################################################

	// CLEAR: Remove all nodes from the list
	virtual void clear() {

		// If the list is empty
		int list_size = size();
		if(list_size == 0) {
			return;
		}

		// Get the head node
		Node *ptr = mylist;
		Node *temp = ptr->next;

		// Loop through
		while(temp!=NULL) {
			ptr->next = temp->next;
			temp->next = NULL;
			delete temp;
			temp = ptr->next;
		}

		// Get rid of the last pointer
		Node *head = mylist;
		delete head;
		mylist = NULL;

	};

	// #################################################################################################################
	// #################################################################################################################

	// AT: returns value of the node at the given index (list begins at 0).
	// Throw out of range if given index out of list
	virtual T at(int index) {

		// First check for size
		num_items = size();
		T return_data;

		// debuggin
		cout << "This is insit my at function " << endl;


			cout << "This is inside my try statement " << endl;
			if (num_items == 0 || index > num_items - 1 || index < 0) {

				cout << "This is inside my if statement before throw " << endl;
				throw out_of_range("out of range");

			}

		// Create a counter
		int counter = 0;

		cout << "Before the loop " << endl;

		// Loop through all of the nodes
		for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
			if(counter == index) {
				cout << "Value at index " << index << " is equal to " << ptr->data << endl;
				return_data = ptr->data;
				return(return_data);
			}

			// Otherwise augment the counter
			else{
				counter += 1;
			}
		}
		return 0;
	}


	// #################################################################################################################
	// #################################################################################################################


	// SIZE: Returns the number of nodes in the list
	virtual int size() {

		// Create a counter
		int counter = 0;

		// Loop through all of the nodes
		for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
			counter += 1;
			}
		cout << "The size of the list is " << counter << endl;
		return(counter);
	};

	// #################################################################################################################
	// #################################################################################################################


	// TO STRING: A LinkedList containing the value 1, 2, 3, 4, and 5 should return "1 2 3 4 5"
	virtual string toString() {

		// Create stringstream object
		stringstream ss;

		// Loop through all nodes, printing out vals and next pointer
		for(Node *ptr =mylist; ptr != NULL; ptr = ptr->next) {

			// Last one
			if(ptr->next == NULL) {
				ss << ptr->data;
			}
			else {
				ss << ptr->data << " ";
			}
		}

		// Return the string stream object
		return(ss.str());

	};

	// #################################################################################################################
	// #################################################################################################################

};
