#include <iostream>
#include <string>
#include <ctime>
using namespace std;

string getCurrentDate() {

	time_t clock = time(NULL);
	struct tm* st;
	st = localtime(&clock);
	string currentDate = to_string(st->tm_mday) + "/" + to_string(st->tm_mon + 1) + "/" + to_string(st->tm_year + 1900);

	return currentDate;
};

string getCurrentTime() {

	time_t clock = time(NULL);
	struct tm* st;
	st = localtime(&clock);
	string currentTime = to_string(st->tm_hour) + ":" + to_string(st->tm_min) + ":" + to_string(st->tm_sec);

	return currentTime;//hello
};

class Patient {

public:

	string UserID;
	string firstName;
	string lastName;
	string gender;
	int age;

	Patient(string UserID, string firstName, string lastName, string gender, int age) {
		this->UserID = UserID;
		this->firstName = firstName;
		this->lastName = lastName;
		this->gender = gender;
		this->age = age;
	}
};

class Doctor {};

class History {

public:
	int priority;
	string visitDate;
	string visitTime;
	Patient* patient;

	History(int priority, string visitDate, string visitTime, Patient *patient) {
		this->priority = priority;
		this->visitDate = visitDate;
		this->visitTime = visitTime;
		this->patient = patient;
	}
};

class HistoryNode {

public:
	History* currentHistory;
	HistoryNode* previousNode;
	HistoryNode* nextNode;
};

class HistoryLinkedList {

public:

	int size;
	HistoryNode* head;
	HistoryNode* tail;

	HistoryLinkedList() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	~HistoryLinkedList() {};

	void appendHistory(History* history) {

		HistoryNode* newNode = new HistoryNode();
		newNode->currentHistory = history;
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

	int checkExistence(string patientID) {

		int index = 0;
		HistoryNode* last = head;
		while (last != NULL) {
			if (last->currentHistory->patient->UserID == patientID && last->currentHistory->visitDate == getCurrentDate())
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

	History* getHistoryAt(int index) {

		HistoryNode* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
		}
		return last->currentHistory;
	}

	void setHistoryAt(int index, History* history) {

		HistoryNode* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
		}
		last->currentHistory = history;
	}

	void display() {
		if (head == NULL)
		{
			cout << "List is empty!" << endl;
		}
		else
		{
			HistoryNode* temp = head;
			while (temp != NULL) {
				cout << "Patient ID: " << temp->currentHistory->patient->UserID << "\n";
				cout << "First Name: " << temp->currentHistory->patient->firstName << "\n";
				cout << "Last Name: " << temp->currentHistory->patient->lastName << "\n";
				cout << "Gender: " << temp->currentHistory->patient->gender << "\n";
				cout << "Age: " << temp->currentHistory->patient->age << "\n";
				cout << "Priority: " << temp->currentHistory->priority << "\n";
				cout << "Visit Date: " << temp->currentHistory->visitDate << "\n";
				cout << "Visit Time: " << temp->currentHistory->visitTime << "\n";
				cout << "---------------------------------------\n";
				temp = temp->nextNode;
			}
			cout << endl;
		}
	}
};

class PatientNode {

public:
	Patient* currentPatient;
	PatientNode* previousNode;
	PatientNode* nextNode;
};

class PatientLinkedList {

public:

	int size;
	PatientNode* head;
	PatientNode* tail;

	PatientLinkedList() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	~PatientLinkedList() {};

	void appendPatient(Patient *patient) { 

		PatientNode* newNode = new PatientNode();
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

		PatientNode* toDelete = head;
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
		PatientNode* last = head;
		while (last != NULL) { 
			if (last->currentPatient->UserID == patientID)
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

		PatientNode* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
		}
		return last->currentPatient;
	}

	void setPatientAt(int index, Patient* patient) {

		PatientNode* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
		}
		last->currentPatient = patient;
	}

	int getSize() {

		PatientNode* last = head;
		while (last != NULL) {
			last = last->nextNode;
			size++;
		}

		return size/2;
	}

	void display(HistoryLinkedList* historyList) {
		if (head == NULL)
		{
			cout << "List is empty!" << endl;
		}
		else
		{
			PatientNode* temp = head;
			while (temp != NULL) {

				cout << "Patient ID: " << temp->currentPatient->UserID << "\n";
				cout << "First Name: " << temp->currentPatient->firstName << "\n";
				cout << "Last Name: " << temp->currentPatient->lastName << "\n";
				cout << "Gender: " << temp->currentPatient->gender << "\n";
				cout << "Age: " << temp->currentPatient->age << "\n";

				int index = historyList->checkExistence(temp->currentPatient->UserID);
				History* history = historyList->getHistoryAt(index);

				cout << "Priority: " << history->priority << "\n";
				cout << "Visit Date: " << history->visitDate << "\n";
				cout << "Visit Time: " << history->visitTime << "\n";

				cout << "---------------------------------------\n";
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

	PatientLinkedList *waitingList = new PatientLinkedList();
	PatientLinkedList *patientList = new PatientLinkedList();
	HistoryLinkedList *historyList = new HistoryLinkedList();

	Patient *patient1 = new Patient("U001", "Alex", "A", "Male", 17);
	Patient *patient2 = new Patient("U002", "Bob", "B", "Male", 23);
	Patient *patient3 = new Patient("U003", "Caitlin", "C", "Female", 21);

	History* history1 = new History(1, "21/5/2021", "11:5:33", patient1);
	History* history2 = new History(2, "10/8/2021", "9:30:55", patient2);
	History* history3 = new History(3, getCurrentDate(), getCurrentTime(), patient3);

	//waitingList->appendPatient(patient1);
	//waitingList->appendPatient(patient2);
	waitingList->appendPatient(patient3);

	patientList->appendPatient(patient1);
	patientList->appendPatient(patient2);
	patientList->appendPatient(patient3);

	historyList->appendHistory(history1);
	historyList->appendHistory(history2);
	historyList->appendHistory(history3);

	//////////////////////////////////////////////////////////////////////////////

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

								Patient* newPatient = new Patient(patientID, firstName, lastName, gender, age);
								waitingList->appendPatient(newPatient);
								patientList->appendPatient(newPatient);
								History* currentVisit = new History(priority, getCurrentDate(), getCurrentTime(), newPatient);
								historyList->appendHistory(currentVisit);

								cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
								cout << "\n";
								cout << "\033[1;33mNew Record of Patient\033[1;36m " + patientID + "\033[1;33m has been generated!\033[0m" << endl;
								cout << "\n";
							}
							else
							{
								cout << "Patient ID: ";
								cin >> patientID;
								cout << "Priority: ";
								cin >> priority;
								cout << "\n";

								index = patientList->checkExistence(patientID);
								temp = waitingList->checkExistence(patientID);

								if (index != -1)
								{
									if (temp == -1)
									{
										Patient *newPatient = patientList->getPatientAt(index);
										waitingList->appendPatient(newPatient);
										History* currentVisit = new History(priority, getCurrentDate(), getCurrentTime(), newPatient);
										historyList->appendHistory(currentVisit);
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
							waitingList->display(historyList);
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
										temp = historyList->checkExistence(patientID);
										History *history = historyList->getHistoryAt(temp);
										history->priority = priority;
										historyList->setHistoryAt(temp, history);
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
						waitingList->display(historyList);

						option = 0;
						break;
					case 2:
						historyList->display();

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