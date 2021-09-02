#include <iostream>
#include <string>
using namespace std;

class User {

protected:
	string UserID;
	string firstName;
	string lastName;
	int age;
	string gender;

public:

	User(string UserID, string firstName, string lastName, int age, string gender) {
		this->UserID = UserID;
		this->firstName = firstName;
		this->lastName = lastName;
		this->age = age;
		this->gender = gender;
	}

	string getUserID() {
		return UserID;
	}
};

class Patient : public User {

public:
	Patient(string UserID, string firstName, string lastName, int age, string gender) : User(UserID, firstName, lastName, age, gender) {}
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

private:
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

	void deletePatient(string patientID) {
		Node* last = head; // Assume there is one and only one node in the linkedlist
		while (last->currentPatient->getUserID() != patientID) { // Linear traverse until the node to be deleted is found
			last = last->nextNode;
		}
		last->previousNode->nextNode = last->nextNode;
		last->nextNode->previousNode = last->previousNode;
		delete last;
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

void printHeader() {
	cout << "\033[1;34m###############################################################" << endl;
	cout << "### \033[1;94mKlinik Sulaiman - Patient Queue Based Management System \033[1;34m###" << endl;
	cout << "###############################################################\n" << endl;;
};

void clear() // Clear the terminal when logout
{
	cout << "\x1B[2J\x1B[H";
};

int main() {

	LinkedList *waitingList = new LinkedList();

	Patient *patient1 = new Patient("U001", "Alex", "A", 17, "Male");
	Patient *patient2 = new Patient("U002", "Bob", "B", 23, "Male");
	Patient *patient3 = new Patient("U003", "Caitlin", "C", 21, "Female");

	waitingList->addPatient(patient1);
	waitingList->addPatient(patient2);
	waitingList->addPatient(patient3);

	////////////////////////////////////////////////////////////////

	int option;

	do 
	{
		cout << "\n";
		printHeader();
		cout << "\033[0mLogin As: " << endl;
		cout << "1. Nurse" << endl;
		cout << "2. Doctor \n" << endl;
		cout << "Option: ";
		cin >> option;
		cout << "\n";

		switch (option) {
			case 1:
				do
				{
					string search_term;
					string patientID, firstName, lastName, gender;
					int priority, age;

					printHeader();
					cout << "\033[1;32mLogged in as Nurse\033[0m\n" << endl;
					cout << "1. Add Patient to Waiting List" << endl;
					cout << "2. View Waiting List" << endl;
					cout << "3. Edit Waiting List Priority" << endl;
					cout << "4. Call Patient for Treatment" << endl;
					cout << "5. Logout \n" << endl;
					cout << "Action: ";
					cin >> option;
					cout << "\n";

					switch (option) {
					case 1:
					{
						cout << "Patient ID: ";
						cin >> patientID;
						// Auto generate next available UserID
						// Check for existance of patientID provided by user, if a match is found, skip the cin of other details

						cout << "First Name: ";
						cin >> firstName;
						cout << "Last Name: ";
						cin >> lastName;
						cout << "Age: ";
						cin >> age;
						cout << "Gender: ";
						cin >> gender;
						cout << "\n";

						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
						cout << "\n";

						Patient *newPatient = new Patient(patientID, firstName, lastName, age, gender);
						waitingList->addPatient(newPatient);

						option = 0;
						break;
					}
					case 2:
						waitingList->display();
						cout << "\n";

						do
						{
							cout << "1. Search Patient" << endl;
							cout << "2. Sort by Priority" << endl;
							cout << "3. Sort by Visit Time" << endl;
							cout << "4. Back \n" << endl;
							cout << "Action: ";
							cin >> option;
							cout << "\n";

							switch (option) {
							case 1:
								cout << "Patient ID or First Name: ";
								cin >> search_term;
								cout << "\n";

								option = 0;
								break;
							case 2:
								waitingList->display();
								cout << "\n";

								option = 0;
								break;
							case 3:
								waitingList->display();
								cout << "\n";

								option = 0;
								break;
							case 4:
								break;
							default:
								cout << "\033[1;31mInvalid Option!\033[0m" << endl;
								cout << "\n";
							}
						} while (option != 1 && option != 2 && option != 3 && option != 4);

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

						//waitingList->deletePatient(patientID);

						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been removed from waiting list!\033[0m" << endl;
						cout << "\n";

						option = 0;
						break;
					case 5:
						clear();
						break;
					default:
						cout << "\033[1;31mInvalid Option!\033[0m" << endl;
						cout << "\n";
					}

				} while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5);

				break;
			case 2:
				do
				{
					printHeader();
					cout << "\033[1;32mLogged in as Doctor\033[0m\n" << endl;
					cout << "1. View Waiting List" << endl;
					cout << "2. View Patient List" << endl;
					cout << "3. Logout \n" << endl;
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
					case 3:
						clear();
						break;
					default:
						cout << "\033[1;31mInvalid Option!\033[0m" << endl;
						cout << "\n";
					}
				} while (option != 1 && option != 2 && option != 3);

				break;
			default:
				cout << "\033[1;31mInvalid Option!\033[0m" << endl;
		}
	} while (option != 1 && option != 2);

	return 0;
}