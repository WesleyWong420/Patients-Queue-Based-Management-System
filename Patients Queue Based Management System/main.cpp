#include <iostream>
#include <string>
using namespace std;

class User {

protected:
	string firstName;
	string lastName;
	string UserID;
	string password;

public:
	User() {}

	User(string firstName, string lastName, string UserID, string password) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->UserID = UserID;
		this->password = password;
	}

	string getUserID() {
		return UserID;
	}
};

class Patient : public User {

public:
	Patient(string firstName, string lastName, string UserID, string password) : User(firstName, lastName, UserID, password) {}
};

class Nurse : public User {
};

class Doctor : public User {
};

class Node {

public:
	Patient* currentPatient;
	Node* previousNode;
	Node* nextNode;

};

class LinkedList {

	Node* head;

public:
	LinkedList() {
		head = NULL;
	}

	~LinkedList() {};

	void addPatient(Patient* patient) { // https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/

		Node* newNode = new Node();
		newNode->currentPatient = patient;
		newNode->nextNode = NULL;

		if (head == NULL) // If first node is empty (empty linked list)
		{
			head = newNode;
		}
		else
		{
			Node* last = head; // Assume there is one and only one node in the linkedlist
			while (last->nextNode != NULL) { // Linear traverse until the last node does not has a next node
				last = last->nextNode;
			}
			last->nextNode = newNode;
			newNode->previousNode = last;
		}
	}

	void display() {
		if (head == NULL)
		{
			cout << "List is empty!" << endl;
		}
		else
		{
			Node* temp = head;
			while (temp != NULL) {
				cout << temp->currentPatient->getUserID() << " ";
				temp = temp->nextNode;
			}
			cout << endl;
		}
	}
};

int main() {

	LinkedList* waitingList = new LinkedList();

	Patient* patient1 = new Patient("aa", "aa", "aa", "aa");
	Patient* patient2 = new Patient("b", "b", "b", "b");
	Patient* patient3 = new Patient("c", "c", "c", "c");

	waitingList->addPatient(patient1);
	waitingList->addPatient(patient2);
	waitingList->addPatient(patient3);

	waitingList->display();

	return 0;
}