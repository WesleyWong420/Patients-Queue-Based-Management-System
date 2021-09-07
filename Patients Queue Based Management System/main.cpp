﻿#include <iostream>
#include <string>
#include <ctime>
using namespace std;

string getCurrentDate() {

	time_t clock = time(NULL);
	struct tm* st;
	st = localtime(&clock);

	string day = to_string(st->tm_mday) , month = to_string(st->tm_mon + 1), year = to_string(st->tm_year + 1900);

	if (day.length() != 2)
	{
		day = "0" + day;
	}

	if (month.length() != 2)
	{
		month = "0" + month;
	}

	string currentDate = day + "/" + month + "/" + year;
	return currentDate;
};

string getCurrentTime() {

	time_t clock = time(NULL);
	struct tm* st;
	st = localtime(&clock);

	string second = to_string(st->tm_sec), minute = to_string(st->tm_min), hour = to_string(st->tm_hour);

	if (second.length() != 2)
	{
		second = "0" + second;
	}

	if (minute.length() != 2)
	{
		minute = "0" + minute;
	}

	if (hour.length() != 2)
	{
		hour = "0" + hour;
	}

	string currentTime = hour + ":" + minute + ":" + second;
	return currentTime;
};

class Medicine {

public:

	string medicineName;
	int amount;

	Medicine(string medicineName, int amount) {
		this->medicineName = medicineName;
		this->amount = amount;
	}
};

class Patient {

public:

	string UserID;
	string firstName;
	string lastName;
	string gender;
	string phone;
	string address;
	string disability;
	int age;
	int priority;
	
	Patient(string UserID, string firstName, string lastName, string gender, int age, string phone, string address, string disability) {
		this->UserID = UserID;
		this->firstName = firstName;
		this->lastName = lastName;
		this->gender = gender;
		this->age = age;
		this->phone = phone;
		this->address = address;
		this->disability = disability;

		if (disability == "true")
		{
			this->priority = 2;
		}
		else
		{
			this->priority = 1;
		}
	}
};

class Doctor {

public:
	string doctorName;
};

class History {

public:
	
	string visitDate;
	string visitTime;
	string sickness;
	Patient* patient;
	Doctor* doctor;
	Medicine* medicine;

	History(string visitDate, string visitTime, string sickness, Patient *patient) {
		this->visitDate = visitDate;
		this->visitTime = visitTime;
		this->sickness = sickness;
		this->patient = patient;
		this->doctor = NULL;
		this->medicine = NULL;
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
			if (last->currentHistory->patient->UserID == patientID)
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

	void searchPatient(string patientID) {

		int found = 0;
		HistoryNode* last = head;
		while (last != NULL) {
			if (last->currentHistory->patient->UserID == patientID)
			{
				if (found == 0)
				{
					cout << "\033[1;33m---------------------------------------------------------------\n";
					cout << "                       Search Result                    \n";
					found++;
				}

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";

				cout << "\033[1;33mPatient ID: \033[0m" << last->currentHistory->patient->UserID << "\n";
				cout << "\033[1;33mFirst Name: \033[0m" << last->currentHistory->patient->firstName << "\n";
				cout << "\033[1;33mLast Name: \033[0m" << last->currentHistory->patient->lastName << "\n";
				cout << "\033[1;33mGender: \033[0m" << last->currentHistory->patient->gender << "\n";
				cout << "\033[1;33mAge: \033[0m" << last->currentHistory->patient->age << "\n";
				cout << "\033[1;33mPriority: \033[0m" << last->currentHistory->patient->priority << "\n";
				cout << "\033[1;33mVisit Date: \033[0m" << last->currentHistory->visitDate << "\n";
				cout << "\033[1;33mVisit Time: \033[0m" << last->currentHistory->visitTime << "\n";
				cout << "\n";
			}
			
			last = last->nextNode;
		}

		if (found == 0)
		{
			cout << "\n";
			cout << "\033[1;31mPatient Not Found!\033[0m" << endl;
			cout << "\n";
		}
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

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                       Patient List                       \n";

		if (head == NULL)
		{
			cout << "List is empty!" << endl;
		}
		else
		{
			HistoryNode* temp = head;
			while (temp != NULL) {

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";

				cout << "\033[1;33mPatient ID: \033[0m" << temp->currentHistory->patient->UserID << "\n";
				cout << "\033[1;33mFirst Name: \033[0m" << temp->currentHistory->patient->firstName << "\n";
				cout << "\033[1;33mLast Name: \033[0m" << temp->currentHistory->patient->lastName << "\n";
				cout << "\033[1;33mGender: \033[0m" << temp->currentHistory->patient->gender << "\n";
				cout << "\033[1;33mAge: \033[0m" << temp->currentHistory->patient->age << "\n";
				cout << "\033[1;33mPhone Number: \033[0m" << temp->currentHistory->patient->phone << "\n";
				cout << "\033[1;33mAddress: \033[0m" << temp->currentHistory->patient->address << "\n";
				cout << "\033[1;33mDisability Option: \033[0m" << temp->currentHistory->patient->disability << "\n";
				cout << "\033[1;33mPriority: \033[0m" << temp->currentHistory->patient->priority << "\n";
				cout << "\033[1;33mVisit Date: \033[0m" << temp->currentHistory->visitDate << "\n";
				cout << "\033[1;33mVisit Time: \033[0m" << temp->currentHistory->visitTime << "\n";
				cout << "\033[1;33mSickness Description: \033[0m" << temp->currentHistory->sickness << "\n";
				//cout << "\033[1;33mDoctor Assigned: \033[0m" << temp->currentHistory->doctor->doctorName<< "\n";
				//cout << "\033[1;33mMedicine Prescription: \033[0m" << temp->currentHistory->medicine->medicineName << "\n";
				cout << "\n";

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

	void display(HistoryLinkedList* historyList) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                       Waiting List                       \n";

		if (head == NULL)
		{
			cout << "\033[1;31mList is empty!\033[0m" << endl;
			cout << "\n";
		}
		else
		{
			PatientNode* temp = head;
			while (temp != NULL) {

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";

				cout << "\033[1;33mPatient ID: \033[0m" << temp->currentPatient->UserID << "\n";
				cout << "\033[1;33mFirst Name: \033[0m" << temp->currentPatient->firstName << "\n";
				cout << "\033[1;33mLast Name: \033[0m" << temp->currentPatient->lastName << "\n";
				cout << "\033[1;33mGender: \033[0m" << temp->currentPatient->gender << "\n";
				cout << "\033[1;33mAge: \033[0m" << temp->currentPatient->age << "\n";
				cout << "\033[1;33mPhone Number: \033[0m" << temp->currentPatient->phone << "\n";
				cout << "\033[1;33mAddress: \033[0m" << temp->currentPatient->address << "\n";
				cout << "\033[1;33mDisability Option: \033[0m" << temp->currentPatient->disability << "\n";
				cout << "\033[1;33mPriority: \033[0m" << temp->currentPatient->priority << "\n";
				//cout << "\033[1;33mVisit Date: \033[0m" << temp->currentHistory->visitDate << "\n";
				//cout << "\033[1;33mVisit Time: \033[0m" << temp->currentHistory->visitTime << "\n";
				//cout << "\033[1;33mSickness Description: \033[0m" << temp->currentHistory->sickness << "\n";
				cout << "\n";

				temp = temp->nextNode;
			}
			cout << endl;
		}
	}
};

void printHeader() {
	cout << "\033[1;34m---------------------------------------------------------------" << endl;
	cout << "   \033[1;94mKlinik Sulaiman - Patient Queue Based Management System \033[1;34m   " << endl;
	cout << "---------------------------------------------------------------\n" << endl;;
};

void clear() // Clear the terminal when logout
{
	cout << "\x1B[2J\x1B[H";
};

int main() {

	PatientLinkedList *waitingList = new PatientLinkedList();
	HistoryLinkedList *historyList = new HistoryLinkedList();

	Patient *patient1 = new Patient("U001", "Alex", "A", "Male", 17, "0123456789", "Street 1", "false");
	Patient *patient2 = new Patient("U002", "Bob", "B", "Male", 23, "0123456789", "Street 2", "false");
	Patient *patient3 = new Patient("U003", "Caitlin", "C", "Female", 21, "0123456789", "Street 3", "true");

	History* history1 = new History("21/05/2021", "11:05:33", "Vomit", patient1);
	History* history2 = new History("10/08/2021", "09:30:55", "Fever", patient2);
	History* history3 = new History("31/08/2021", "14:55:06", "Headache", patient3);

	//waitingList->appendPatient(patient1);
	//waitingList->appendPatient(patient2);
	//waitingList->appendPatient(patient3);

	historyList->appendHistory(history1);
	historyList->appendHistory(history2);
	historyList->appendHistory(history3);

	//////////////////////////////////////////////////////////////////////////////

	string patientID, firstName, lastName, gender, phone, address, sickness, disability;
	int age, priority;

	string search_term, firstVisit;
	int option, index, temp;
	int totalPatient = 3;

	History *currentVisit;

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
								cout << "Phone Number: ";
								cin >> phone;
								cout << "Address: ";
								cin >> address;
								cout << "Disability Option (true/false): ";
								cin >> disability;
								cout << "Sickness Description: ";
								cin >> sickness;
								cout << "\n";

								if (totalPatient < 9)
								{
									patientID = "U00" + to_string(totalPatient + 1);
								}
								else if (9 <= totalPatient <= 98)
								{
									patientID = "U0" + to_string(totalPatient + 1);
								}
								else
								{
									patientID = "U" + to_string(totalPatient + 1);
								}
								

								Patient *newPatient = new Patient(patientID, firstName, lastName, gender, age, phone, address, disability);
								waitingList->appendPatient(newPatient);
								currentVisit = new History(getCurrentDate(), getCurrentTime(), sickness, newPatient);

								cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
								cout << "\n";
								cout << "\033[1;33mNew Record of Patient\033[1;36m " + patientID + "\033[1;33m has been generated!\033[0m" << endl;
								cout << "\n";
							}
							else
							{
								cout << "Patient ID: ";
								cin >> patientID;
								cout << "Sickness Description: ";
								cin >> sickness;

								index = historyList->checkExistence(patientID);
								temp = waitingList->checkExistence(patientID);

								if (index != -1)
								{
									if (temp == -1)
									{
										History *pastVisit = historyList->getHistoryAt(index);
										Patient *newPatient = pastVisit->patient;
										waitingList->appendPatient(newPatient);
										currentVisit = new History(getCurrentDate(), getCurrentTime(), sickness, newPatient);

										cout << "\n";
										cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
										cout << "\n";
									}
									else
									{
										cout << "\n";
										cout << "\033[1;31mPatient is already in the waiting list!\033[0m" << endl;
										cout << "\n";
									}
								}
								else
								{
									cout << "\n";
									cout << "\033[1;31mPatient Not Found!\033[0m" << endl;
									cout << "\n";
								}
							}

							option = 0;
							break;
						}
						case 2:
							waitingList->display(historyList);

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
										Patient *patient = waitingList->getPatientAt(index);
										patient->priority = priority;
										waitingList->setPatientAt(index, patient);

										cout << waitingList->getPatientAt(index)->priority;

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
						{
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
						}
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

								index = historyList->checkExistence(patientID);
								historyList->searchPatient(patientID);

								if (index != -1)
								{
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
								}

								option = 0;
								break;
							case 2:
								cout << "Sickness Description or First Name: ";
								cin >> search_term;
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