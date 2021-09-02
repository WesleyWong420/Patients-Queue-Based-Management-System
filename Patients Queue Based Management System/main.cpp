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

	void addPatient(Patient *patient) { // https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/

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

	LinkedList *waitingList = new LinkedList();

	Patient *patient1 = new Patient("Alex", "A", "U001", "pass123");
	Patient *patient2 = new Patient("Bob", "B", "U002", "pass123");
	Patient *patient3 = new Patient("Caitlin", "C", "U003", "pass123");

	waitingList->addPatient(patient1);
	waitingList->addPatient(patient2);
	waitingList->addPatient(patient3);

	////////////////////////////////////////////////////////////////

	int option;

	do 
	{
		cout << "Klinik Sulaiman Patient Queue Based Management System \n" << endl;
		cout << "Login As: " << endl;
		cout << "1. Nurse" << endl;
		cout << "2. Doctor \n" << endl;
		cout << "Option: ";
		cin >> option;
		cout << "\n";

		switch (option) {
			case 1:
				do
				{
					string patientID;
					int priority;

					cout << "Klinik Sulaiman Patient Queue Based Management System \n" << endl;
					cout << "\033[1;32mLogged in as Nurse\033[0m\n" << endl;
					cout << "1. Add Patient to Waiting List" << endl;
					cout << "2. View Waiting List" << endl;
					cout << "3. Edit Waiting List Priority" << endl;
					cout << "4. Call Patient for Treatment \n" << endl;
					cout << "Action: ";
					cin >> option;
					cout << "\n";

					switch (option) {
					case 1:
						//Patient *newPatient = new Patient("Alex", "A", "U001", "pass123");
						//waitingList->addPatient(newPatient);

						option = 0;
						break;
					case 2:
						waitingList->display();

						option = 0;
						break;
					case 3:
						cout << "Patient ID: ";
						cin >> patientID;
						cout << "Priority (3 - High, 2 - Medium, 1 - Low) : ";
						cin >> priority;
						cout << "\n";
						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been moved to priority level\033[1;36m " + to_string(priority) +  "\033[0m" << endl;
						cout << "\n";

						option = 0;
						break;
					case 4:
						cout << "Patient ID: ";
						cin >> patientID;
						cout << "\n";
						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been removed from waiting list!\033[0m" << endl;
						cout << "\n";

						option = 0;
						break;
					default:
						cout << "\033[1;31mInvalid Option!\033[0m\n" << endl;
					}
				} while (option != 1 && option != 2 && option != 3 && option != 4);

				break;
			case 2:
				do
				{
					cout << "Klinik Sulaiman Patient Queue Based Management System \n" << endl;
					cout << "\033[1;32mLogged in as Doctor\033[0m\n" << endl;
					cout << "1. View Waiting List" << endl;
					cout << "2. View Patient List \n" << endl;
					cout << "Action: ";
					cin >> option;
					cout << "\n";

					switch (option) {
					case 1:
						waitingList->display();

						option = 0;
						break;
					case 2:
						waitingList->display();

						option = 0;
						break;
					default:
						cout << "\033[1;31mInvalid Option!\033[0m\n" << endl;
					}
				} while (option != 1 && option != 2);

				break;
			default:
				cout << "\033[1;31mInvalid Option!\033[0m\n" << endl;
		}
	} while (option != 1 && option != 2);

	return 0;
}