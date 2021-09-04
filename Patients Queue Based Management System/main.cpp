﻿#include <iostream>
#include <string>
using namespace std;

class User {

protected:
	string UserID;
	string firstName;
	string lastName;
	string gender;
	int age;

public:

	User(string UserID, string firstName, string lastName, string gender, int age) {
		this->UserID = UserID;
		this->firstName = firstName;
		this->lastName = lastName;
		this->gender = gender;
		this->age = age;
	}

	string getUserID() {
		return UserID;
	}

	void setUserID(string UserID) {
		this->UserID = UserID;
	}

	string getFirstName() {
		return firstName;
	}

	void setFirstName(string firstName) {
		this->firstName = firstName;
	}

	string getLastName() {
		return lastName;
	}

	void setLastName(string lastName) {
		this->lastName = lastName;
	}

	string getGender() {
		return gender;
	}

	void setGender(string gender) {
		this->gender = gender;
	}

	int getAge() {
		return age;
	}

	void setAge(int age) {
		this->age = age;
	}
};

class Patient : public User {

private:

	History history;

public:
	Patient(string UserID, string firstName, string lastName, string gender, int age, int priority) : 
		User(UserID, firstName, lastName, gender, age) {
		History* history = new History(priority);
	}

	History &getHistory() {
		return history;
	}

	void setHistory(History history) {
		this->history = history;
	}
};

class Doctor : public User {
};

class History {

private:

	int priority;

public:

	History() {}

	History(int priority) {
		this->priority = priority;
	}

	int getPriority() {
		return priority;
	}

	void setPriority(int priority) {
		this->priority = priority;
	}
};

class Node {

public:
	Patient* currentPatient;
	Node* previousNode;
	Node* nextNode;

};

class LinkedList {

public:

	int size;
	Node* head;
	Node* tail;

	LinkedList() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	~LinkedList() {};

	void appendPatient(Patient *patient) { 

		Node* newNode = new Node();
		newNode->currentPatient = patient;
		newNode->nextNode = NULL;
		newNode->previousNode = tail;
		tail = newNode;

		if (head == NULL) // If first node is empty (empty linked list)
		{
			head = newNode;
		}
		else
		{
			newNode->previousNode->nextNode = newNode;
		}
		size++;
	}

	void deleteFirstPatient() { 

		Node* toDelete = head;
		head = head->nextNode;
		delete toDelete;
		size--;

		if (head != NULL)
			head->previousNode = NULL;
		else
		{
			tail = NULL;
		}
	}

	int checkExistence(string patientID) {

		int index = 0;
		Node* last = head;
		while (last != NULL) { 
			if (last->currentPatient->getUserID() == patientID)
			{
				return index;
			}
			else
			{
				last = last->nextNode;
				index++;
			}
		}

		return -1;
	}

	Patient* getPatientAt(int index){

		Node* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
		}
		return last->currentPatient;
	}

	void setPatientAt(int index, Patient* patient) {

		Node* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
		}
		last->currentPatient = patient;
	}

	int getSize() {

		Node* last = head;
		while (last != NULL) {
			last = last->nextNode;
			size++;
		}

		return size;
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
				cout << temp->currentPatient->getHistory()->getPriority() << " ";
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
	LinkedList *patientList = new LinkedList();

	Patient *patient1 = new Patient("U001", "Alex", "A", "Male", 17, 1);
	Patient *patient2 = new Patient("U002", "Bob", "B", "Male", 23, 2);
	Patient *patient3 = new Patient("U003", "Caitlin", "C", "Female", 21, 3);

	waitingList->appendPatient(patient1);
	waitingList->appendPatient(patient2);
	waitingList->appendPatient(patient3);

	patientList->appendPatient(patient1);
	patientList->appendPatient(patient2);
	patientList->appendPatient(patient3);

	////////////////////////////////////////////////////////////////

	string search_term, firstVisit;
	string patientID, firstName, lastName, gender;
	int option, index, temp, priority, age;

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
		clear();

		switch (option) {
			case 1:
				do
				{
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
							cout << "New Patient? (true/false):  ";
							cin >> firstVisit;

							if (firstVisit == "true")
							{
								cout << "First Name: ";
								cin >> firstName;
								cout << "Last Name: ";
								cin >> lastName;
								cout << "Age: ";
								cin >> age;
								cout << "Gender: ";
								cin >> gender;
								cout << "Priority: ";
								cin >> priority;
								cout << "\n";

								patientID =  "U00" + to_string((patientList->getSize()) + 1);

								Patient* newPatient = new Patient(patientID, firstName, lastName, gender, age, priority);
								waitingList->appendPatient(newPatient);
								patientList->appendPatient(newPatient);

								cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
								cout << "\n";
								cout << "\033[1;33mNew Record of Patient\033[1;36m " + patientID + "\033[1;33m has been generated!\033[0m" << endl;
								cout << "\n";
							}
							else
							{
								cout << "Patient ID: ";
								cin >> patientID;
								cout << "\n";

								index = patientList->checkExistence(patientID);
								temp = waitingList->checkExistence(patientID);

								if (index != -1)
								{
									if (temp == -1)
									{
										Patient* newPatient = patientList->getPatientAt(index);
										waitingList->appendPatient(newPatient);
										cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
										cout << "\n";
									}
									else
									{
										cout << "\033[1;31mPatient is already in the waiting list!\033[0m" << endl;
										cout << "\n";
									}
								}
								else
								{
									cout << "\033[1;31mPatient Not Found!\033[0m" << endl;
									cout << "\n";
								}
							}

							option = 0;
							break;
						}
						case 2:
							waitingList->display();
							cout << "\n";

							do
							{
								cout << "1. Search for Patient by Patient ID or First Name" << endl;
								cout << "2. Sort by Visit Time" << endl;
								cout << "3. Back \n" << endl;
								cout << "Action: ";
								cin >> option;
								cout << "\n";

								switch (option) {
								case 1:
									cout << "Patient ID or First Name: ";
									cin >> search_term;
									cout << "\n";

									// Patient found or not found? Search from waitingList

									option = 0;
									break;
								case 2:
									waitingList->display();
									cout << "\n";

									option = 0;
									break;
								case 3:
									break;
								default:
									cout << "\033[1;31mInvalid Option!\033[0m" << endl;
									cout << "\n";
								}
							} while (option != 1 && option != 2 && option != 3);

							option = 0;
							break;
						case 3:
							cout << "Patient ID: ";
							cin >> patientID;

							index = waitingList->checkExistence(patientID);

							if (index == -1)
							{
								cout << "\n";
								cout << "\033[1;31mPatient Not Found!\033[0m" << endl;
								cout << "\n";
							}
							else
							{
								do 
								{
									cout << "Priority (3 - High, 2 - Medium, 1 - Low) : ";
									cin >> priority;
									cout << "\n";

									if (priority == 1 || priority == 2 || priority == 3)
									{
										Patient *patient = waitingList->getPatientAt(index);
										patient->getHistory()->setPriority(priority);
										waitingList->setPatientAt(index, patient);
										cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been moved to priority level\033[1;36m " + to_string(priority) + "\033[0m" << endl;
										cout << "\n";
										break;
									}
									else
									{
										cout << "\033[1;31mInvalid Option!\033[0m" << endl;
										cout << "\n";
									}
								} while (priority != 3 && priority != 2 && priority != 1);	
							}

							option = 0;
							break;
						case 4:
							cout << "Patient ID: ";
							cin >> patientID;
							cout << "\n";
							index = waitingList->checkExistence(patientID);

							if (index == 0)
							{
								waitingList->deleteFirstPatient();

								cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been removed from waiting list!\033[0m" << endl;
								cout << "\n";
							}
							else if (index == -1)
							{
								cout << "\033[1;31mPatient Not Found!\033[0m" << endl;
								cout << "\n";
							}
							else
							{
								cout << "\033[1;31mPatient\033[1;36m " + patientID + "\033[1;31m is\033[1;36m " + to_string(index + 1) + "\033[1;31m place away from being called!\033[0m" << endl;
								cout << "\n";
							}

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
						patientList->display();

						do
						{
							cout << "1. Search Specific Patient by Patient ID" << endl;
							cout << "2. Search Patients by Sickness or First Name" << endl;
							cout << "3. Back \n" << endl;
							cout << "Action: ";
							cin >> option;
							cout << "\n";

							switch (option) {
							case 1:
								cout << "Patient ID: ";
								cin >> patientID;
								cout << "\n";

								// Patient found or not found? Search from patientList

								do
								{
									cout << "1. Modify Patient Record" << endl;
									cout << "2. Sort by Visit History" << endl;
									cout << "3. Back \n" << endl;
									cout << "Action: ";
									cin >> option;
									cout << "\n";

									switch (option) {
									case 1:
										option = 0;
										break;
									case 2:
										option = 0;
										break;
									case 3:
										break;
									default:
										cout << "\033[1;31mInvalid Option!\033[0m" << endl;
										cout << "\n";
									}
								} while (option != 1 && option != 2 && option != 3);

								option = 0;
								break;
							case 2:
								cout << "Sickness Description or First Name: ";
								cin >> search_term;
								cout << "\n";

								// Patient found or not found? Search from patientList

								option = 0;
								break;
							case 3:
								break;
							default:
								cout << "\033[1;31mInvalid Option!\033[0m" << endl;
								cout << "\n";
							}
						} while (option != 1 && option != 2 && option != 3);

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