#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

string getCurrentDate() {

	time_t clock = time(NULL);
	struct tm* st;
	st = localtime(&clock);

	string day = to_string(st->tm_mday), month = to_string(st->tm_mon + 1), year = to_string(st->tm_year + 1900);

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

int timeToSecond(string time) {

	int hoursInSecond = 0;
	int minutesInSecond = 0;
	int second = 0;

	if (time.substr(0, 2) != "00")
	{
		hoursInSecond =  (stoi(time.substr(0, 2)) * 3600);
	}
	if (time.substr(3, 2) != "00")
	{
		minutesInSecond = (stoi(time.substr(3, 2)) * 60);
	}
	if (time.substr(6, 2) != "00")
	{
		second = stoi(time.substr(6, 2));
	}

	return second + minutesInSecond + hoursInSecond;
}

int dateToDay(string date) {

	int day = 0;
	int monthInDay = 0;
	int yearInDay = 0;

	if (date.substr(0, 2) != "00")
	{
		day = stoi(date.substr(0, 2));
	}
	if (date.substr(3, 2) != "00")
	{
		monthInDay = (stoi(date.substr(3, 2)) * 30);
	}
	if (date.substr(6, 2) != "00")
	{
		yearInDay = (stoi(date.substr(6, 4))*365);
	}

	return day + monthInDay + yearInDay;
}

class Nurse {

public:
	string nurseName;

	Nurse(string name) {
		this->nurseName = name;
	}
};

class Doctor {

public:
	string doctorName;

	Doctor(string name) {
		this->doctorName = name;
	}
};

class Medicine {

public:

	string medicineID;
	string medicineName;
	int quantity;

	Medicine(string medicineID, string medicineName, int quantity) {
		this->medicineID = medicineID;
		this->medicineName = medicineName;
		this->quantity = quantity;
	}
};

class MedicineNode {

public:
	Medicine* currentMedicine;
	MedicineNode* previousNode;
	MedicineNode* nextNode;
};

class MedicineLinkedList {

public:
	int size;
	MedicineNode* head;
	MedicineNode* tail;

	MedicineLinkedList() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	~MedicineLinkedList() {

		MedicineNode* current = head;
		MedicineNode* next;

		while (current != NULL) {
			next = current->nextNode;
			delete current;
			current = next;
		}
	};

	void appendMedicine(Medicine* medicine) {

		MedicineNode* newNode = new MedicineNode();
		newNode->currentMedicine = medicine;
		newNode->nextNode = NULL;
		newNode->previousNode = tail;
		tail = newNode;

		if (head == NULL) 
		{
			head = newNode;
		}
		else
		{
			newNode->previousNode->nextNode = newNode;
		}

		size++;
	}

	void deleteFirst() {

		MedicineNode* toDelete = head;
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

	void deleteAt(int index) {

		MedicineNode* prev = NULL;
		MedicineNode* next = NULL;
		MedicineNode* toDelete = head;

		if (index < size)
		{
			if (index == 0)
			{
				deleteFirst();
			}
			else
			{
				for (int i = 0; i < index; i++)
				{
					prev = toDelete;
					toDelete = toDelete->nextNode;
					next = toDelete->nextNode;

					if (i + 1 == index) // index will start from 1 because if 0 will run deleteFirst()
					{
						prev->nextNode = toDelete->nextNode;

						if (next != NULL) { // At last node, next will be NULL
							next->previousNode = toDelete->previousNode;
						}

						delete toDelete;
						size--;
					}
				}
			}
		}
		else
		{
			cout << "Medicine Does Not Exist!";
		}
	}

	int checkExistence(string medicineID) {

		int index = 0;
		MedicineNode* last = head;

		while (last != NULL) {
			if (last->currentMedicine->medicineID == medicineID)
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
	
	Medicine* getMedicineAt(int index) {

		MedicineNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		return last->currentMedicine;
	}

	void setMedicineAt(int index, Medicine* Medicine) {

		MedicineNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		last->currentMedicine = Medicine;
	}

	int getSize() {

		MedicineNode* current = head;
		int size = 0;

		while (current != NULL) {
			size = size + 1;
			current = current->nextNode;
		}

		return size;
	}

	void swap(int index1, int index2) {

		Medicine* medicine = getMedicineAt(index1);

		setMedicineAt(index1, getMedicineAt(index2));
		setMedicineAt(index2, medicine);
	}

	int getNextGap(int gap) {

		gap = (gap * 10) / 13;

		if (gap < 1) {
			return 1;
		}

		return gap;
	}

	void combSortID() {

		int gap = getSize();

		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {
				if (getMedicineAt(i)->medicineID > getMedicineAt(i + gap)->medicineID) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}

	void combSortName() {

		int gap = getSize();

		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {
				if (getMedicineAt(i)->medicineName > getMedicineAt(i + gap)->medicineName) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}

	void combSortQuantity() {

		int gap = getSize();

		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {
				if (getMedicineAt(i)->quantity > getMedicineAt(i + gap)->quantity) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}

	int binarySearchID(int j, int k, string id) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getMedicineAt(mid)->medicineID == id) {
			return mid;
		}
		else if (getMedicineAt(mid)->medicineID > id) {
			return binarySearchID(j, mid - 1, id);
		}
		else {
			return binarySearchID(mid + 1, k, id);
		}
	}

	int binarySearchName(int j, int k, string name) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getMedicineAt(mid)->medicineName == name) {
			return mid;
		}
		else if (getMedicineAt(mid)->medicineName > name) {
			return binarySearchName(j, mid - 1, name);
		}
		else {
			return binarySearchName(mid + 1, k, name);
		}
	}

	int exponentialSearchID(string id) {

		if (getMedicineAt(0)->medicineID == id) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getMedicineAt(i)->medicineID <= id) {

				i = i * 2;

				if (i > getSize()) {
					break;
				}
			}

			return binarySearchID(i / 2, min(i, getSize()), id);
		}
	}

	int exponentialSearchName(string name) {

		if (getMedicineAt(0)->medicineName == name) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getMedicineAt(i)->medicineName <= name) {

				i = i * 2;

				if (i > getSize()) {
					break;
				}
			}

			return binarySearchName(i / 2, min(i, getSize()), name);
		}
	}

	void display(int index, int term) {

		cout << "\033[1;33m---------------------------------------------------------------\n";

		if (term == 0)
		{
			cout << "                     Search Result - " + getMedicineAt(index)->medicineID + "\n";
		}
		else if (term == 1)
		{
			cout << "                   Search Result - " + getMedicineAt(index)->medicineName + "\n";
		}

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "\n";
		cout << "\033[1;33mMedicine ID: \033[0m" << getMedicineAt(index)->medicineID << "\n";
		cout << "\033[1;33mMedicine Name: \033[0m" << getMedicineAt(index)->medicineName << "\n";
		cout << "\033[1;33mMedicine Quantity: \033[0m" << getMedicineAt(index)->quantity << "\n";
		cout << "\n";
	}

	void display() {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                       Medicine List                       \n";

		if (head == NULL)
		{
			cout << "\033[1;33m---------------------------------------------------------------\n";
			cout << "\n";
			cout << "\033[1;31mList is empty!\033[0m" << endl;
			cout << "\n";
		}
		else
		{
			MedicineNode* current = head;

			while (current != NULL) {

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";
				cout << "\033[1;33mMedicine ID: \033[0m" << current->currentMedicine->medicineID << "\n";
				cout << "\033[1;33mMedicine Name: \033[0m" << current->currentMedicine->medicineName << "\n";
				cout << "\033[1;33mMedicine Quantity: \033[0m" << current->currentMedicine->quantity << "\n";
				cout << "\n";

				current = current->nextNode;
			}
		}
	}
};

class IndexNode {

public:

	int currentIndex;
	IndexNode* previousNode;
	IndexNode* nextNode;
};

class IndexLinkedList {

public:

	int size;
	IndexNode* head;
	IndexNode* tail;

	IndexLinkedList() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	~IndexLinkedList() {

		IndexNode* current = head;
		IndexNode* next;

		while (current != NULL) {
			next = current->nextNode;
			delete current;
			current = next;
		}
	};

	void prependIndex(int index) {
		
		IndexNode* newNode = new IndexNode();
		newNode->currentIndex = index;
		newNode->previousNode = NULL;
		newNode->nextNode = head;
		head = newNode;

		if (tail == NULL) {
			tail = newNode;
		}
		else {
			newNode->nextNode->previousNode = newNode;
		}
		
		size++;
	}

	void appendIndex(int index) {

		IndexNode* newNode = new IndexNode();
		newNode->currentIndex = index;
		newNode->previousNode = tail;
		newNode->nextNode = NULL;
		tail = newNode;

		if (head == NULL) {
			head = newNode;
		}
		else {
			newNode->previousNode->nextNode = newNode;
		}
		
		size++;
	}

	int getIndexAt(int index) {

		IndexNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		return last->currentIndex;
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
		this->priority = 1;
	}
};

class PatientNode {

public:
	Patient* currentPatient;
	PatientNode* previousNode;
	PatientNode* nextNode;
};

class History {

public:

	string visitDate;
	string visitTime;
	string sickness;
	string medicine;
	Patient* patient;
	Doctor* doctor;

	History(string visitDate, string visitTime, Patient* patient) {		
		this->visitDate = visitDate;
		this->visitTime = visitTime;
		this->sickness = "";
		this->medicine = "";
		this->patient = patient;
		this->doctor = NULL;
	}

	History(string visitDate, string visitTime, string sickness, string medicine, Patient* patient, Doctor* doctor) {
		this->visitDate = visitDate;				// For hardcoding dummy data
		this->visitTime = visitTime;
		this->sickness = sickness;
		this->medicine = medicine;
		this->patient = patient;
		this->doctor = doctor;	
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

	~HistoryLinkedList() {

		HistoryNode* current = head;
		HistoryNode* next;

		while (current != NULL) {
			next = current->nextNode;
			delete current;
			current = next;
		}
	};

	void appendHistory(History* history) {

		HistoryNode* newNode = new HistoryNode();
		newNode->currentHistory = history;
		newNode->nextNode = NULL;
		newNode->previousNode = tail;
		tail = newNode;

		if (head == NULL) 
		{
			head = newNode;
		}
		else
		{
			newNode->previousNode->nextNode = newNode;
		}

		size++;
	}

	void deleteFirst() {

		HistoryNode* toDelete = head;
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

	void deleteAt(int index) {

		HistoryNode* prev = NULL;
		HistoryNode* next = NULL;
		HistoryNode* toDelete = head;

		if (index < size)
		{
			if (index == 0)
			{
				deleteFirst();
			}
			else
			{
				for (int i = 0; i < index; i++)
				{
					prev = toDelete;
					toDelete = toDelete->nextNode;
					next = toDelete->nextNode;

					if (i + 1 == index) // index will start from 1 because if 0 will run deleteFirst()
					{
						prev->nextNode = toDelete->nextNode;

						if (next != NULL) { // At last node, next will be NULL
							next->previousNode = toDelete->previousNode;
						}

						delete toDelete;
						size--;
					}
				}
			}
		}
		else
		{
			cout << "Medicine Does Not Exist!";
		}
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

	History* getHistoryAt(int index) {

		HistoryNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		return last->currentHistory;
	}

	void setHistoryAt(int index, History* history) {

		HistoryNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		last->currentHistory = history;
	}

	int getSize() {

		HistoryNode* current = head;
		int size = 0;

		while (current != NULL) {
			size = size + 1;
			current = current->nextNode;
		}

		return size;
	}

	void combSortID() {

		int gap = getSize();

		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {

				if (getHistoryAt(i)->patient->UserID == getHistoryAt(i + gap)->patient->UserID) {
					if (dateToDay((getHistoryAt(i)->visitDate)) > dateToDay(getHistoryAt(i + gap)->visitDate)) {
						swap(i, i + gap);
						swapped = true;
					}
					else if (dateToDay((getHistoryAt(i)->visitDate)) == dateToDay(getHistoryAt(i + gap)->visitDate)) {
						if (timeToSecond((getHistoryAt(i)->visitTime)) > timeToSecond(getHistoryAt(i + gap)->visitTime)) {
							swap(i, i + gap);
							swapped = true;
						}
					}
				}
				else if (getHistoryAt(i)->patient->UserID > getHistoryAt(i + gap)->patient->UserID) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}


	void swap(int index1, int index2) {

		History* history = getHistoryAt(index1);

		setHistoryAt(index1, getHistoryAt(index2));
		setHistoryAt(index2, history);
	}

	int getNextGap(int gap) {

		gap = (gap * 10) / 13;

		if (gap < 1) {
			return 1;
		}

		return gap;
	}

	void combSortSickness() {

		int gap = getSize();
		
		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {

				if (getHistoryAt(i)->sickness == getHistoryAt(i + gap)->sickness) {
					if (dateToDay(getHistoryAt(i)->visitDate) > dateToDay(getHistoryAt(i + gap)->visitDate)) {
						swap(i, i + gap);
						swapped = true;
					}
					else if (dateToDay(getHistoryAt(i)->visitDate) == dateToDay(getHistoryAt(i + gap)->visitDate)) {
						if (timeToSecond((getHistoryAt(i)->visitTime)) >> timeToSecond(getHistoryAt(i + gap)->visitTime)) {
							swap(i, i + gap);
							swapped = true;
						}
					}
				}
				else if (getHistoryAt(i)->sickness > getHistoryAt(i + gap)->sickness) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}

	void combSortName() {

		int gap = getSize();

		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {

				if (getHistoryAt(i)->patient->firstName == getHistoryAt(i + gap)->patient->firstName) {
					if (dateToDay((getHistoryAt(i)->visitDate)) > dateToDay(getHistoryAt(i + gap)->visitDate)) {
						swap(i, i + gap);
						swapped = true;
					}
					else if (dateToDay((getHistoryAt(i)->visitDate)) == dateToDay(getHistoryAt(i + gap)->visitDate)) {
						if (timeToSecond((getHistoryAt(i)->visitTime)) > timeToSecond(getHistoryAt(i + gap)->visitTime)) {
							swap(i, i + gap);
							swapped = true;
						}
					}
				}
				else if (getHistoryAt(i)->patient->firstName > getHistoryAt(i + gap)->patient->firstName) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}

	void combSortTime() {

		int gap = getSize();

		bool swapped = true;

		while (gap != 1 || swapped == true) {

			gap = getNextGap(gap);
			swapped = false;

			for (int i = 0; i < getSize() - gap; i++) {

				if (timeToSecond(getHistoryAt(i)->visitTime) > timeToSecond(getHistoryAt(i + gap)->visitTime)) {
					swap(i, i + gap);
					swapped = true;
				}
			}
		}
	}

	int binarySearchSickness(int j, int k, string sickness) {

		if (j > k) 
		{
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getHistoryAt(mid)->sickness == sickness) {
			return mid;
		}
		else if (getHistoryAt(mid)->sickness > sickness) {
			return binarySearchSickness(j, mid - 1, sickness);
		}
		else {
			return binarySearchSickness(mid + 1, k, sickness);
		}
	}

	int exponentialSearchSickness(string sickness) {

		if (getHistoryAt(0)->sickness == sickness) 
		{
			return 0;
		}
		else 
		{
			int i = 1;

			while (i < getSize() && getHistoryAt(i)->sickness <= sickness) {

				i = i * 2;

				if (i > getSize()) {
					break;
				}
			}

			return binarySearchSickness(i / 2, min(i, getSize()), sickness);
		}
	}

	int binarySearchName(int j, int k, string name) {

		if (j > k) 
		{
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getHistoryAt(mid)->patient->firstName == name) {
			return mid;
		}
		else if (getHistoryAt(mid)->patient->firstName > name) {
			return binarySearchName(j, mid - 1, name);
		}
		else {
			return binarySearchName(mid + 1, k, name);
		}
	}

	int exponentialSearchName(string name) {

		if (getHistoryAt(0)->patient->firstName == name) 
		{
			return 0;
		}
		else 
		{
			int i = 1;

			while (i < getSize() && getHistoryAt(i)->patient->firstName <= name) {

				i = i * 2;

				if (i > getSize()) {
					break;
				}
			}
			return binarySearchName(i / 2, min(i, getSize()), name);
		}
	}

	int binarySearchID(int j, int k, string id) {
		if (j > k) 
		{
			return -1;
		}
			int mid = j + (k - j) / 2;

			if (getHistoryAt(mid)->patient->UserID == id) {
				return mid;
			}
			else if (getHistoryAt(mid)->patient->UserID > id) {
				return binarySearchID(j, mid - 1, id);
			}
			else {
				return binarySearchID(mid + 1, k, id);
			}

	}

	int exponentialSearchID(string id) {

		if (getHistoryAt(0)->patient->UserID == id) 
		{
			return 0;
		}
		else 
		{
			int i = 1;

			while (i < getSize() && getHistoryAt(i)->patient->UserID <= id) {

				i = i * 2;

				if (i > getSize()) {
					break;
				}
			}
			return binarySearchID(i / 2, min(i, getSize()), id);
		}
	}

	void searchRangeName(IndexLinkedList* indexList, int index, string search_term){

		if (index != -1) 
		{
			indexList->prependIndex(index);
		}

		int i = 1;

		if (index + 1 < getSize())	// waitinglist search name fix
		{	
			while (search_term == getHistoryAt(index + i)->patient->firstName) {

					indexList->appendIndex(index + i);
					i = i + 1;

					if (index+i >= getSize()) {		// waitinglist search name fix
						break;
					}
			}		
		}

		i = 1;

		if (index - 1 > -1) 
		{
			while (search_term == getHistoryAt(index - i)->patient->firstName) {

				indexList->prependIndex(index - i);
				i = i + 1;
			}
		}
	}

	void searchRangeSickness(IndexLinkedList* indexList, int index, string search_term) {

		if (index != -1) 
		{
			indexList->prependIndex(index);
		}


		int i = 1;

		if (index + 1 < getSize()) 	// waitinglist search name fix,if last then do loop
		{
			while (search_term == getHistoryAt(index + i)->sickness) {

				indexList->appendIndex(index + i);
				i = i + 1;

				if (index + i >= getSize()) {		// waitinglist search name fix
					break;
				}
			}
		}

		i = 1;

		if (index - 1 > -1) 
		{
			while (search_term == getHistoryAt(index - i)->sickness) {

				indexList->prependIndex(index - i);
				i = i + 1;
			}
		}
	}

	void searchRangeID(IndexLinkedList* indexList, int index, string search_term, int option) {		// option 1 for asc, 0 for desc

		if (index != -1) 
		{
			indexList->prependIndex(index);
		}

		int i = 1;

		if (index + 1 < getSize()) 
		{
			while (search_term == getHistoryAt(index + i)->patient->UserID) {

				if (option == 0) {
					indexList->prependIndex(index + i);
				}
				else if (option == 1) {
					indexList->appendIndex(index + i);
				}

				i = i + 1;

				if (index + i >= getSize()) {
					break;
				}
			}
		}

		i = 1;

		if (index - 1 > -1) //change
		{	
			while (search_term == getHistoryAt(index - i)->patient->UserID) {

				if (option == 0) {
					indexList->appendIndex(index - i);
				}
				else if (option == 1) {
					indexList->prependIndex(index - i);
				}

				i = i + 1;
			}
		}
	}

	void displaySpecific(int index) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                     Search Result - " + getHistoryAt(index)->patient->UserID + "\n";
		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "\n";
		
		cout << "\033[1;33mPatient ID: \033[0m" << getHistoryAt(index)->patient->UserID << "\n";
		cout << "\033[1;33mFirst Name: \033[0m" << getHistoryAt(index)->patient->firstName << "\n";
		cout << "\033[1;33mLast Name: \033[0m" << getHistoryAt(index)->patient->lastName << "\n";
		cout << "\033[1;33mGender: \033[0m" << getHistoryAt(index)->patient->gender << "\n";
		cout << "\033[1;33mAge: \033[0m" << getHistoryAt(index)->patient->age << "\n";
		cout << "\033[1;33mPhone Number: \033[0m" << getHistoryAt(index)->patient->phone << "\n";
		cout << "\033[1;33mAddress: \033[0m" << getHistoryAt(index)->patient->address << "\n";
		cout << "\033[1;33mDisability Option: \033[0m" << getHistoryAt(index)->patient->disability << "\n";
		cout << "\033[1;33mPriority: \033[0m" << getHistoryAt(index)->patient->priority << "\n";
		cout << "\033[1;33mVisit Date: \033[0m" << getHistoryAt(index)->visitDate << "\n";
		cout << "\033[1;33mVisit Time: \033[0m" << getHistoryAt(index)->visitTime << "\n";
		cout << "\033[1;33mSickness Description: \033[0m" << getHistoryAt(index)->sickness << "\n";
		cout << "\033[1;33mDoctor Assigned: \033[0m" << getHistoryAt(index)->doctor->doctorName << "\n";
		cout << "\033[1;33mMedicine Prescription: \033[0m" << getHistoryAt(index)->medicine << "\n";
		cout << "\n";
	}

	void displaySpecific2(int index) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                     Search Result - " + getHistoryAt(index)->patient->UserID + "\n";
		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "\n";

		cout << "\033[1;33mPatient ID: \033[0m" << getHistoryAt(index)->patient->UserID << "\n";
		cout << "\033[1;33mFirst Name: \033[0m" << getHistoryAt(index)->patient->firstName << "\n";
		cout << "\033[1;33mLast Name: \033[0m" << getHistoryAt(index)->patient->lastName << "\n";
		cout << "\033[1;33mGender: \033[0m" << getHistoryAt(index)->patient->gender << "\n";
		cout << "\033[1;33mAge: \033[0m" << getHistoryAt(index)->patient->age << "\n";
		cout << "\033[1;33mPhone Number: \033[0m" << getHistoryAt(index)->patient->phone << "\n";
		cout << "\033[1;33mAddress: \033[0m" << getHistoryAt(index)->patient->address << "\n";
		cout << "\033[1;33mDisability Option: \033[0m" << getHistoryAt(index)->patient->disability << "\n";
		cout << "\033[1;33mPriority: \033[0m" << getHistoryAt(index)->patient->priority << "\n";
		cout << "\033[1;33mVisit Date: \033[0m" << getHistoryAt(index)->visitDate << "\n";
		cout << "\033[1;33mVisit Time: \033[0m" << getHistoryAt(index)->visitTime << "\n";
		cout << "\n";
	}

	void display(int term) {

		cout << "\033[1;33m---------------------------------------------------------------\n";

		if(term == 0)
		{
			cout << "                       Patient List                       \n";
		}
		else if(term == 1)
		{
			cout << "                       Treating List                       \n";
		}
		else if (term == 2)
		{
			cout << "                       Waiting List                       \n";
		}

		if (head == NULL)
		{
			cout << "\033[1;33m---------------------------------------------------------------\n";
			cout << "\n";
			cout << "\033[1;31mList is empty!\033[0m" << endl;
			cout << "\n";
		}
		else
		{
			HistoryNode* current = head;

			while (current != NULL) {

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";
				cout << "\033[1;33mPatient ID: \033[0m" << current->currentHistory->patient->UserID << "\n";
				cout << "\033[1;33mFirst Name: \033[0m" << current->currentHistory->patient->firstName << "\n";
				cout << "\033[1;33mLast Name: \033[0m" << current->currentHistory->patient->lastName << "\n";
				cout << "\033[1;33mGender: \033[0m" << current->currentHistory->patient->gender << "\n";
				cout << "\033[1;33mAge: \033[0m" << current->currentHistory->patient->age << "\n";
				cout << "\033[1;33mPhone Number: \033[0m" << current->currentHistory->patient->phone << "\n";
				cout << "\033[1;33mAddress: \033[0m" << current->currentHistory->patient->address << "\n";
				cout << "\033[1;33mDisability Option: \033[0m" << current->currentHistory->patient->disability << "\n";
				cout << "\033[1;33mPriority: \033[0m" << current->currentHistory->patient->priority << "\n";
				cout << "\033[1;33mVisit Date: \033[0m" << current->currentHistory->visitDate << "\n";
				cout << "\033[1;33mVisit Time: \033[0m" << current->currentHistory->visitTime << "\n";

				if (current->currentHistory->sickness != "" && current->currentHistory->doctor != NULL && current->currentHistory->medicine != "")
				{
					cout << "\033[1;33mSickness Description: \033[0m" << current->currentHistory->sickness << "\n";
					cout << "\033[1;33mDoctor Assigned: \033[0m" << current->currentHistory->doctor->doctorName << "\n";
					cout << "\033[1;33mMedicine Prescription: \033[0m" << current->currentHistory->medicine << "\n";
				}
				else
				{
					if (term != 2)
					{
						cout << "\033[1;33mSickness Description: " << "\033[1;31mTBD\033[0m" << "\n";
						cout << "\033[1;33mDoctor Assigned: " << "\033[1;31mTBD\033[0m" << "\n";
						cout << "\033[1;33mMedicine Prescription: " << "\033[1;31mTBD\033[0m" << "\n";
					}
				}

				cout << "\n";

				current = current->nextNode;
			}
		}
	}
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

	~PatientLinkedList() {

		PatientNode* current = head;
		PatientNode* next;

		while (current != NULL) {
			next = current->nextNode;
			delete current;
			current = next;
		}
	};

	void appendPatient(Patient* patient) {

		PatientNode* newNode = new PatientNode();
		newNode->currentPatient = patient;
		newNode->nextNode = NULL;
		newNode->previousNode = tail;
		tail = newNode;

		if (head == NULL) 
		{
			head = newNode;
		}
		else
		{
			newNode->previousNode->nextNode = newNode;
		}

		size++;
	}

	void deleteFirst() {

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

	Patient* getPatientAt(int index) {

		PatientNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		return last->currentPatient;
	}

	void setPatientAt(int index, Patient* patient) {

		PatientNode* last;

		if (index < round(size / 2))
		{
			last = head;

			for (int i = 0; i < index; i++)
			{
				if (last->nextNode != NULL) {
					last = last->nextNode;
				}
			}
		}
		else
		{
			last = tail;

			for (int i = 0; i < size - index - 1; i++)
			{
				if (last->previousNode != NULL) {
					last = last->previousNode;
				}
			}
		}

		last->currentPatient = patient;
	}

	int getSize() {

		PatientNode* current = head;
		int size = 0;

		while (current != NULL) {
			size = size + 1;
			current = current->nextNode;
		}

		return size;
	}

	void insertionSortPriority() {

		int j, key;

		for (int i = 1; i < getSize(); i++) {

			key = getPatientAt(i)->priority;
			Patient* keyObj = getPatientAt(i);
			j = i - 1;

			while (j >= 0 && key > getPatientAt(j)->priority) {
				setPatientAt(j + 1, getPatientAt(j));
				j = j - 1;
			}

			setPatientAt(j + 1, keyObj);
		}
	}

	void display(HistoryLinkedList* tempHistory, int index) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                     Search Result - " + getPatientAt(index)->UserID + "\n";
		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "\n";

		cout << "\033[1;33mPatient ID: \033[0m" << getPatientAt(index)->UserID << "\n";
		cout << "\033[1;33mFirst Name: \033[0m" << getPatientAt(index)->firstName << "\n";
		cout << "\033[1;33mLast Name: \033[0m" << getPatientAt(index)->lastName << "\n";
		cout << "\033[1;33mGender: \033[0m" << getPatientAt(index)->gender << "\n";
		cout << "\033[1;33mAge: \033[0m" << getPatientAt(index)->age << "\n";
		cout << "\033[1;33mPhone Number: \033[0m" << getPatientAt(index)->phone << "\n";
		cout << "\033[1;33mAddress: \033[0m" << getPatientAt(index)->address << "\n";
		cout << "\033[1;33mDisability Option: \033[0m" << getPatientAt(index)->disability << "\n";
		cout << "\033[1;33mPriority: \033[0m" << getPatientAt(index)->priority << "\n";

		int index2 = tempHistory->checkExistence(getPatientAt(index)->UserID);
		History* history = tempHistory->getHistoryAt(index2);

		cout << "\033[1;33mVisit Date: \033[0m" << history->visitDate << "\n";
		cout << "\033[1;33mVisit Time: \033[0m" << history->visitTime << "\n";
		cout << "\n";
	}

	void display(HistoryLinkedList* tempHistory) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                       Waiting List                       \n";

		if (head == NULL)
		{
			cout << "\033[1;33m---------------------------------------------------------------\n";
			cout << "\n";
			cout << "\033[1;31mList is empty!\033[0m" << endl;
			cout << "\n";
		}
		else
		{
			PatientNode* current = head;

			while (current != NULL) {

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";
				cout << "\033[1;33mPatient ID: \033[0m" << current->currentPatient->UserID << "\n";
				cout << "\033[1;33mFirst Name: \033[0m" << current->currentPatient->firstName << "\n";
				cout << "\033[1;33mLast Name: \033[0m" << current->currentPatient->lastName << "\n";
				cout << "\033[1;33mGender: \033[0m" << current->currentPatient->gender << "\n";
				cout << "\033[1;33mAge: \033[0m" << current->currentPatient->age << "\n";
				cout << "\033[1;33mPhone Number: \033[0m" << current->currentPatient->phone << "\n";
				cout << "\033[1;33mAddress: \033[0m" << current->currentPatient->address << "\n";
				cout << "\033[1;33mDisability Option: \033[0m" << current->currentPatient->disability << "\n";
				cout << "\033[1;33mPriority: \033[0m" << current->currentPatient->priority << "\n";

				int index = tempHistory->checkExistence(current->currentPatient->UserID);
				History* history = tempHistory->getHistoryAt(index);

				cout << "\033[1;33mVisit Date: \033[0m" << history->visitDate << "\n";
				cout << "\033[1;33mVisit Time: \033[0m" << history->visitTime << "\n";
				cout << "\n";

				current = current->nextNode;
			}
		}
	}
};

void printHeader() {
	cout << "\033[1;33m---------------------------------------------------------------" << endl;
	cout << "   Klinik Sulaiman - Patient Queue Based Management System" << endl;
	cout << "---------------------------------------------------------------\n" << endl;;
};

string checkPhone(string phone) {
	string result = "";
	for (int i = 0; i < phone.length(); i++) {
		if (phone[i] == '0' || phone[i] == '1' || phone[i] == '2' || phone[i] == '3' || phone[i] == '4' || phone[i] == '5' || phone[i] == '6' || phone[i] == '7' || phone[i] == '8' || phone[i] == '9') {
			result += phone[i];
		}
		else {
			cout << "\033[1;31mError! Check again.\033[0m" << endl;
			cout << "Phone Number: ";
			cin.clear();
			cin.ignore(123, '\n');
			cin >> phone;
			break;
		}
	}
	
	return result;
}

void clearTerminal() // Clear the terminal after logout
{
	cout << "\x1B[2J\x1B[H";
};

int main() {

	PatientLinkedList* waitingList = new PatientLinkedList();
	HistoryLinkedList* historyList = new HistoryLinkedList();
	HistoryLinkedList* tempHistory = new HistoryLinkedList();
	HistoryLinkedList* treatingList = new HistoryLinkedList();
	MedicineLinkedList* medicineList = new MedicineLinkedList();

	Patient* patient1 = new Patient("U001", "Alex", "Morgan", "Male", 16, "0123456789", "Street 1", "true");
	Patient* patient2 = new Patient("U002", "Bob", "Dylan", "Male", 23, "0123456789", "Street 2", "true");
	Patient* patient3 = new Patient("U003", "Caitlin", "Jenner", "Female", 19, "0123456789", "Street 3", "false");
	Patient* patient4 = new Patient("U004", "Daniel", "Lewis", "Male", 27, "0123456789", "Street 4", "false");
	Patient* patient5 = new Patient("U005", "Eva", "May", "Female", 26, "0123456789", "Street 5", "true");
	Patient* patient6 = new Patient("U006", "Fiona", "Lim", "Female", 22, "0123456789", "Street 6", "false");
	Patient* patient7 = new Patient("U007", "Griffin", "Johnson", "Male", 35, "0123456789", "Street 7", "false");

	Nurse* nurse1 = new Nurse("Mary");
	Nurse* nurse2 = new Nurse("Elizabeth");
	Nurse* nurse3 = new Nurse("Clara");

	Doctor* doctor1 = new Doctor("Dr. Nick");
	Doctor* doctor2 = new Doctor("Dr. Phil");
	Doctor* doctor3 = new Doctor("Dr. Miller");

	Medicine* medicine1 = new Medicine("M001", "Antibiotics", 115);
	Medicine* medicine2 = new Medicine("M002", "Vicodin", 15);
	Medicine* medicine3 = new Medicine("M003", "Simvastatin", 63);
	Medicine* medicine4 = new Medicine("M004", "Lisinopril", 91);
	Medicine* medicine5 = new Medicine("M005", "Levothyroxine", 53);
	Medicine* medicine6 = new Medicine("M006", "Azithromycin", 72);
	Medicine* medicine7 = new Medicine("M007", "Metformin", 45);
	Medicine* medicine8 = new Medicine("M008", "Lipitor", 83);
	Medicine* medicine9 = new Medicine("M009", "Amlodipine", 92);
	Medicine* medicine10 = new Medicine("M010", "Amoxicillin", 73);
	Medicine* medicine11 = new Medicine("M011", "Hydrochlorothiazide", 99);

	History* history1 = new History("21/02/2021", "11:05:33", "Vomit", "Antibiotics", patient1, doctor1);
	History* history2 = new History("10/03/2021", "09:30:55", "Fever", "Vicodin", patient2, doctor2);
	History* history3 = new History("19/06/2021", "14:55:06", "Headache", "Simvastatin", patient3, doctor3);
	History* history4 = new History("05/07/2021", "17:48:31", "Skin Allergic", "Lipitor", patient5, doctor2);
	History* history5 = new History("16/08/2021", "22:10:59", "Flu", "Amoxicillin", patient6, doctor1);

	historyList->appendHistory(history1);
	historyList->appendHistory(history2);
	historyList->appendHistory(history3);
	historyList->appendHistory(history4);
	historyList->appendHistory(history5);

	medicineList->appendMedicine(medicine1);
	medicineList->appendMedicine(medicine2);
	medicineList->appendMedicine(medicine3);
	medicineList->appendMedicine(medicine4);
	medicineList->appendMedicine(medicine5);
	medicineList->appendMedicine(medicine6);
	medicineList->appendMedicine(medicine7);
	medicineList->appendMedicine(medicine8);
	medicineList->appendMedicine(medicine9);
	medicineList->appendMedicine(medicine10);
	medicineList->appendMedicine(medicine11);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	string patientID, firstName, lastName, gender, phone, address, sickness, disability;
	int age, priority;
	Nurse* nurseOnDuty = nurse1;
	Doctor* doctorOnDuty = doctor1;

	string search_term, firstVisit, medicineID, medicineName;
	int loginAsNurse = 0, loginAsDoctor = 0, option, index, temp, medicineAmount;
	int totalPatient = 7;
	int totalMedicine = 11;

	do
	{
		cout << "\n";
		printHeader();
		cout << "\033[0mLogin As: " << endl;
		cout << "\n";
		cout << "1. Nurse" << endl;
		cout << "2. Doctor" << endl;
		cout << "3. Exit \n" << endl;
		cout << "Option: ";
		cin >> option;

		while (cin.fail())
		{
			cout << "\n";
			cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
			printHeader();
			cout << "\033[0mLogin As: " << endl;
			cout << "\n";
			cout << "1. Nurse" << endl;
			cout << "2. Doctor" << endl;
			cout << "3. Exit \n" << endl;
			cout << "Option: ";
			cin.clear();
			cin.ignore(123, '\n');
			cin >> option;
		}
		cout << "\n";

		switch (option) {
		case 1:
			do
			{
				while (loginAsNurse != 1 && loginAsNurse != 2 && loginAsNurse != 3)
				{
					cout << "\033[1;33m---------------------------------------------------------------\n";
					cout << "                  Select A Nurse To Login\n";
					cout << "\033[1;33m---------------------------------------------------------------\033[0m\n";
					cout << "\n";
					cout << "1. " + nurse1->nurseName + "\n";
					cout << "2. " + nurse2->nurseName + "\n";
					cout << "3. " + nurse3->nurseName + "\n";
					cout << "\n";
					cout << "Login As: ";
					cin >> loginAsNurse;

					while (cin.fail())
					{
						cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
						cout << "\033[1;33m---------------------------------------------------------------\n";
						cout << "                  Select A Nurse To Login\n";
						cout << "\033[1;33m---------------------------------------------------------------\033[0m\n";
						cout << "\n";
						cout << "1. " + nurse1->nurseName + "\n";
						cout << "2. " + nurse2->nurseName + "\n";
						cout << "3. " + nurse3->nurseName + "\n";
						cout << "\n";
						cout << "Login As: ";
						cin.clear();
						cin.ignore(123, '\n');
						cin >> loginAsNurse;
					}
					cout << "\n";

					switch (loginAsNurse) {
					case 1:
						nurseOnDuty = nurse1;
						clearTerminal();
						break;
					case 2:
						nurseOnDuty = nurse2;
						clearTerminal();
						break;
					case 3:
						nurseOnDuty = nurse3;
						clearTerminal();
						break;
					default:
						cout << "\033[1;31mInvalid Option!\033[0m" << endl;
						cout << "\n";
					}
				};
				
				printHeader();
				cout << "\033[1;92mLogged In As: Nurse " + nurseOnDuty->nurseName + "\033[0m\n" << endl;
				cout << "1. Add Patient to Waiting List" << endl;
				cout << "2. View Waiting List" << endl;
				cout << "3. Edit Waiting List Priority" << endl;
				cout << "4. Call Patient for Treatment" << endl;
				cout << "5. View Medicine List" << endl;
				cout << "6. Logout \n" << endl;
				cout << "Action: ";
				cin >> option;

				while (cin.fail())
				{
					cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
					printHeader();
					cout << "\033[1;92mLogged In As: Nurse " + nurseOnDuty->nurseName + "\033[0m\n" << endl;
					cout << "1. Add Patient to Waiting List" << endl;
					cout << "2. View Waiting List" << endl;
					cout << "3. Edit Waiting List Priority" << endl;
					cout << "4. Call Patient for Treatment" << endl;
					cout << "5. View Medicine List" << endl;
					cout << "6. Logout \n" << endl;
					cout << "Action: ";
					cin.clear();
					cin.ignore(123, '\n');
					cin >> option;
				}
				cout << "\n";

				switch (option) {
				case 1:				// Add Patient to Waiting List
				{
					cout << "New Patient? (true/false): ";
					cin >> firstVisit;
					transform(firstVisit.begin(), firstVisit.end(), firstVisit.begin(), ::tolower);

					if (firstVisit == "true")
					{
						if (totalPatient < 9)
						{
							patientID = "U00" + to_string(totalPatient + 1);
						}
						else if (8 < totalPatient && totalPatient < 99)
						{
							patientID = "U0" + to_string(totalPatient + 1);
						}
						else
						{
							patientID = "U" + to_string(totalPatient + 1);
						}

						totalPatient++;

						cout << "Patient ID: " + patientID + "\n"; //Patient ID
						cout << "First Name: "; //Input First Name
						cin >> firstName;
						cout << "Last Name: "; //Input Last Name
						cin >> lastName;
						cout << "Age: "; //Age
						cin >> age;				

						while (cin.fail())
						{
							cout << "\033[1;31mError! Check again.\033[0m" << endl;
							cout << "Age: ";
							cin.clear();
							cin.ignore(123, '\n');
							cin >> age;
						}

						cout << "Gender (Male/Female): "; //Gender
						cin >> gender;
						transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
						while (1)
						{
							if (gender == "male" || gender == "female")
							{
								break;
							}
							else
							{
								cout << "\033[1;31mError! Check again.\033[0m" << endl;
								cout << "Gender (Male/Female): ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> gender;
								transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
							}
						}

						cout << "Phone Number (e.g. 01(1)23456789): "; //Phone Number
						cin >> phone;
						while (1)//Phone Input Validation
						{
							string result = "";
							if (size(phone) < 10 || size(phone) > 11)
							{
								cout << "\033[1;31mError! Check again.\033[0m" << endl;
								cout << "Phone Number (e.g. 01(1)23456789): ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> phone;
							}
							else
							{
								for (int i = 0; i < phone.length(); i++) {
									if (phone[i] == '0' || phone[i] == '1' || phone[i] == '2' || phone[i] == '3' || phone[i] == '4' || phone[i] == '5' || phone[i] == '6' || phone[i] == '7' || phone[i] == '8' || phone[i] == '9') {
										result += phone[i];
									}
								}
								if (size(result) == size(phone)) {
									phone = result;
									break;
								}
								else {
									cout << "\033[1;31mError! Check again.\033[0m" << endl;
									cout << "Phone Number: ";
									cin.clear();
									cin.ignore(123, '\n');
									cin >> phone;
								}
							}
						}
						cin.ignore();
						cout << "Address: "; //Address
						getline(cin, address);

						cout << "Disability Option (true/false): "; //Disability
						cin >> disability;
						while (1)
						{
							if (disability == "true" || disability == "false")
							{
								break;
							}
							else
							{
								cout << "\033[1;31mError! Check again.\033[0m" << endl;
								cout << "Disability Option (true/false): ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> disability;
							}
						}
						cout << "\n";

						Patient* newPatient = new Patient(patientID, firstName, lastName, gender, age, phone, address, disability);
						waitingList->appendPatient(newPatient);
						History* currentVisit = new History(getCurrentDate(), getCurrentTime(), newPatient);
						tempHistory->appendHistory(currentVisit);

						cout << "\033[1;33mNew Record of Patient\033[1;36m " + patientID + "\033[1;33m has been saved!\033[0m" << endl;
						cout << "\n";
						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
						cout << "\n";
					}
					else if (firstVisit == "false")
					{
						cout << "Patient ID (e.g. U001): ";
						cin >> patientID;
						sickness = "";

						index = historyList->checkExistence(patientID);
						temp = waitingList->checkExistence(patientID);

						if (index != -1)
						{
							if (temp == -1)
							{
								History* pastVisit = historyList->getHistoryAt(index);
								Patient* newPatient = new Patient(pastVisit->patient->UserID, pastVisit->patient->firstName, pastVisit->patient->lastName, pastVisit->patient->gender, pastVisit->patient->age, pastVisit->patient->phone, pastVisit->patient->address, pastVisit->patient->disability);
								waitingList->appendPatient(newPatient);
								History* currentVisit = new History(getCurrentDate(), getCurrentTime(), newPatient);
								tempHistory->appendHistory(currentVisit);

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
					else
					{
						cout << "\n";
						cout << "\033[1;31mInvalid Option!\033[0m" << endl;
						cout << "\n";
					}

					option = 0;
					break;
				}
				case 2:		// View Waiting List
					tempHistory->combSortTime();
					waitingList->display(tempHistory);

					if (waitingList->head != NULL)
					{
						do
						{
							cout << "1. Search for Patient by Patient ID" << endl;
							cout << "2. Search for Patient by First Name" << endl;
							cout << "3. Sort by Visit Time" << endl;
							cout << "4. Back \n" << endl;
							cout << "Action: ";
							cin >> option;

							while (cin.fail())
							{
								cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
								cout << "1. Search for Patient by Patient ID" << endl;
								cout << "2. Search for Patient by First Name" << endl;
								cout << "3. Sort by Visit Time" << endl;
								cout << "4. Back \n" << endl;
								cout << "Action: ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> option;
							}
							cout << "\n";

							switch (option) {
							case 1:
								cout << "Patient ID (e.g. U001): ";
								cin >> search_term;
								cout << "\n";

								tempHistory->combSortID();
								index = tempHistory->exponentialSearchID(search_term);

								if (index != -1) {
									tempHistory->displaySpecific2(index);
								}
								else {
									cout << "\033[1;31mInvalid Patient ID!\033[0m" << endl;
									cout << "\n";
								}

								option = 0;
								break;
							case 2:
								cout << "Patient Name: ";
								cin >> search_term;
								cout << "\n";

								tempHistory->combSortName();
								index = tempHistory->exponentialSearchName(search_term);

								if (index != -1) {

									IndexLinkedList* indexList = new IndexLinkedList();
									tempHistory->searchRangeName(indexList, index, search_term);

									for (int i = 0; i < indexList->size; i++) {
										tempHistory->displaySpecific2(indexList->getIndexAt(i));
									}

									delete indexList;
								}
								else {
									cout << "\033[1;31mInvalid First Name!\033[0m" << endl;
									cout << "\n";
								}

								option = 0;
								break;
							case 3:
								tempHistory->combSortTime();
								tempHistory->display(2);

								option = 0;
								break;
							case 4:
								break;
							default:
								cout << "\033[1;31mInvalid Option!\033[0m" << endl;
								cout << "\n";
							}
						} while (option != 1 && option != 2 && option != 3 && option != 4);
					}

					option = 0;
					break;
				case 3:				// Edit Waiting List Priority
					cout << "Patient ID (e.g. U001): ";
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

							while (cin.fail())
							{
								cout << "\n";
								cout << "\033[1;31mUse numbers instead.\033[0m" << endl << endl;
								cout << "Priority (3 - High, 2 - Medium, 1 - Low) : ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> priority;
							}
							cout << "\n";

							if (priority == 1 || priority == 2 || priority == 3)
							{
								Patient* patient = waitingList->getPatientAt(index);
								patient->priority = priority;
								waitingList->setPatientAt(index, patient);
								waitingList->insertionSortPriority();

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
				case 4:				// Call Patient for Treatment
				{
					cout << "Patient ID (e.g. U001): ";
					cin >> patientID;
					cout << "\n";

					index = waitingList->checkExistence(patientID);
					temp = tempHistory->checkExistence(patientID);

					if (index == 0)
					{
						waitingList->deleteFirst();

						History* history = tempHistory->getHistoryAt(temp);
						treatingList->appendHistory(history);
						tempHistory->deleteAt(temp);

						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been moved from waiting list to treating list!\033[0m" << endl;
						cout << "\n";
					}
					else if (index == -1)
					{
						cout << "\033[1;31mPatient Not Found!\033[0m" << endl;
						cout << "\n";
					}
					else
					{
						cout << "\033[1;31mPatient\033[1;36m " + patientID + "\033[1;31m is\033[1;36m " + to_string(index) + "\033[1;31m place away from being called!\033[0m" << endl;
						cout << "\n";
					}

					option = 0;
					break;
				}
				case 5:				// View Medicine List
					medicineList->combSortID();
					medicineList->display();

					do
					{
						cout << "1. Search for Medicine by Medicine ID " << endl;
						cout << "2. Search for Medicine by Medicine Name" << endl;
						cout << "3. Sort by Quantity" << endl;
						cout << "4. Edit Medicine" << endl;
						cout << "5. Add Medicine" << endl;
						cout << "6. Back \n" << endl;
						cout << "Action: ";
						cin >> option;

						while (cin.fail())
						{
							cout << "\n";
							cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
							cout << "1. Search for Medicine by Medicine ID " << endl;
							cout << "2. Search for Medicine by Medicine Name" << endl;
							cout << "3. Sort by Quantity" << endl;
							cout << "4. Edit Medicine" << endl;
							cout << "5. Add Medicine" << endl;
							cout << "6. Back \n" << endl;
							cout << "Action: ";
							cin.clear();
							cin.ignore(123, '\n');
							cin >> option;
						}
						cout << "\n";

						switch (option) {
						case 1:					// Search for Medicine by Medicine
							cout << "Medicine ID (e.g. M001): ";
							cin >> search_term;
							cout << "\n";

							medicineList->combSortID();

							index = medicineList->exponentialSearchID(search_term);

							if (index != -1) {
								medicineList->display(index, 0); 
							}
							else {
								cout << "\033[1;31mInvalid Medicine ID!\033[0m" << endl;
								cout << "\n";
							}

							option = 0;
							break;
						case 2:				// Search for Medicine by Medicine Name
							cout << "Medicine Name: ";
							cin >> search_term;
							cout << "\n";

							medicineList->combSortName();

							index = medicineList->exponentialSearchName(search_term);

							if (index != -1) {
								medicineList->display(index, 1);
							}
							else {
								cout << "\033[1;31mInvalid Medicine Name!\033[0m" << endl;
								cout << "\n";
							}

							option = 0;
							break;
						case 3:					// Sort by Quantity
							medicineList->combSortQuantity();
							medicineList->display();	

							option = 0;
							break;
						case 4:					// Edit Medicine
							medicineList->combSortID();
							medicineList->display();

							cout << "Medicine ID: ";
							cin >> medicineID;
							cout << "\n";

							index = medicineList->checkExistence(medicineID);

							if (index != -1)
							{
								do {
									cout << "1. Edit Quantity" << endl;
									cout << "2. Delete" << endl;
									cout << "3. Cancel" << endl;
									cout << "\n";
									cout << "Action: ";
									cin >> option;

									while (cin.fail())
									{
										cout << "\n";
										cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
										cout << "1. Edit Quantity" << endl;
										cout << "2. Delete" << endl;
										cout << "3. Cancel" << endl;
										cout << "\n";
										cout << "Action: ";
										cin.clear();
										cin.ignore(123, '\n');
										cin >> option;
									}
									cout << "\n";

									switch (option) {
									case 1:						// Edit Quantity
										cout << "New Quantity: ";
										cin >> medicineAmount;
										cout << "\n";

										medicineList->getMedicineAt(index)->quantity = medicineAmount;

										cout << "\033[1;33mQuantity of Medicine\033[1;36m " + medicineID + "\033[1;33m has been updated to\033[1;36m " + to_string(medicineAmount) + "\033[1;33m!\033[0m" << endl;
										cout << "\n";

										option = 0;
										break;
									case 2:						// Delete Medicine
										medicineList->deleteAt(index);

										cout << "\033[1;33mMedicine\033[1;36m " + medicineID + "\033[1;33m has been deleted!\033[0m" << endl;
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
							}
							else
							{
								cout << "\033[1;31mInvalid Medicine ID!\033[0m" << endl;
								cout << "\n";
							}

							option = 0;
							break;
						case 5:				// Add Medicine
						{
							cout << "Medicine Name: ";
							cin >> medicineName;
							cout << "\n";
							cout << "Medicine Quantity: ";
							cin >> medicineAmount;

							while (cin.fail())
							{
								cout << "\n";
								cout << "\033[1;31mInvalid Amount!\033[0m" << endl << endl;
								cout << "Medicine Quantity: ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> medicineAmount;
							}
							cout << "\n";

							if (totalMedicine < 9)
							{
								medicineID = "M00" + to_string(totalMedicine + 1);
							}
							else if (8 < totalMedicine && totalMedicine < 99)
							{
								medicineID = "M0" + to_string(totalMedicine + 1);
							}
							else
							{
								medicineID = "M" + to_string(totalMedicine + 1);
							}

							totalMedicine++;
							Medicine* newMedicine = new Medicine(medicineID, medicineName, medicineAmount);
							medicineList->appendMedicine(newMedicine);

							cout << "\033[1;33mNew Record of Medicine\033[1;36m " + medicineID + "\033[1;33m has been saved!\033[0m" << endl;
							cout << "\n";

							option = 0;
							break;
						}
						case 6:
							break;
						default:
							cout << "\033[1;31mInvalid Option!\033[0m" << endl;
							cout << "\n";
						}
					} while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6);

					option = 0;
					break;
				case 6:
					loginAsNurse = 0;
					clearTerminal();
					break;
				default:
					cout << "\033[1;31mInvalid Option!\033[0m" << endl;
					cout << "\n";
				}

			} while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6);

			break;
		case 2:
			do
			{
				while (loginAsDoctor != 1 && loginAsDoctor != 2 && loginAsDoctor != 3)
				{
					cout << "\033[1;33m---------------------------------------------------------------\n";
					cout << "                  Select A Doctor To Login\n";
					cout << "\033[1;33m---------------------------------------------------------------\033[0m\n";
					cout << "\n";
					cout << "1. " + doctor1->doctorName + "\n";
					cout << "2. " + doctor2->doctorName + "\n";
					cout << "3. " + doctor3->doctorName + "\n";
					cout << "\n";
					cout << "Login As: ";
					cin >> loginAsDoctor;

					while (cin.fail())
					{
						cout << "\n";
						cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
						cout << "\033[1;33m---------------------------------------------------------------\n";
						cout << "                  Select A Doctor To Login\n";
						cout << "\033[1;33m---------------------------------------------------------------\033[0m\n";
						cout << "\n";
						cout << "1. " + doctor1->doctorName + "\n";
						cout << "2. " + doctor2->doctorName + "\n";
						cout << "3. " + doctor3->doctorName + "\n";
						cout << "\n";
						cout << "Login As: ";
						cin.clear();
						cin.ignore(123, '\n');
						cin >> loginAsDoctor;
					}
					cout << "\n";

					switch (loginAsDoctor) {
					case 1:
						doctorOnDuty = doctor1;
						clearTerminal();
						break;
					case 2:
						doctorOnDuty = doctor2;
						clearTerminal();
						break;
					case 3:
						doctorOnDuty = doctor3;
						clearTerminal();
						break;
					default:
						cout << "\033[1;31mInvalid Option!\033[0m" << endl;
						cout << "\n";
					}
				};

				printHeader();
				cout << "\033[1;92mLogged In As: Doctor " + doctorOnDuty->doctorName.substr(4) + "\033[0m\n" << endl;
				cout << "1. View Waiting List" << endl;
				cout << "2. View Patient List" << endl;
				cout << "3. View Treating List" << endl;
				cout << "4. Logout \n" << endl;
				cout << "Action: ";
				cin >> option;

				while (cin.fail())
				{
					cout << "\n";
					cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
					printHeader();
					cout << "\033[1;92mLogged In As: Doctor " + doctorOnDuty->doctorName.substr(4) + "\033[0m\n" << endl;
					cout << "1. View Waiting List" << endl;
					cout << "2. View Patient List" << endl;
					cout << "3. View Treating List" << endl;
					cout << "4. Logout \n" << endl;
					cout << "Action: ";
					cin.clear();
					cin.ignore(123, '\n');
					cin >> option;
				}
				cout << "\n";

				switch (option) {
				case 1:				// View Waiting List
					waitingList->display(tempHistory);

					option = 0;
					break;
				case 2:				// View Patient List
					historyList->combSortID();
					historyList->display(0);

					do
					{
						cout << "1. Search Specific Patient by Patient ID" << endl;
						cout << "2. Search Patients by Sickness" << endl;
						cout << "3. Search Patients by First Name" << endl;
						cout << "4. Back \n" << endl;
						cout << "Action: ";
						cin >> option;

						while (cin.fail())
						{
							cout << "\n";
							cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
							cout << "1. Search Specific Patient by Patient ID" << endl;
							cout << "2. Search Patients by Sickness" << endl;
							cout << "3. Search Patients by First Name" << endl;
							cout << "4. Back \n" << endl;
							cout << "Action: ";
							cin.clear();
							cin.ignore(123, '\n');
							cin >> option;
						}
						cout << "\n";

						switch (option) {
						case 1:			// Search Specific Patient by Patient ID
						{
							cout << "Patient ID (e.g. U001): ";
							cin >> patientID;
							cout << "\n";

							historyList->combSortID();
							index = historyList->exponentialSearchID(patientID);
							temp = waitingList->checkExistence(patientID);
							IndexLinkedList* indexList = new IndexLinkedList();
							historyList->searchRangeID(indexList, index, patientID, 1);

							for (int i = 0; i < indexList->size; i++) {
								historyList->displaySpecific(indexList->getIndexAt(i));
							}

							delete indexList;

							if (index != -1)
							{
								do
								{
									cout << "1. Modify Patient Record" << endl;
									cout << "2. Sort by Visit History" << endl;
									cout << "3. Back \n" << endl;
									cout << "Action: ";
									cin >> option;

									while (cin.fail())
									{
										cout << "\n";
										cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
										cout << "1. Modify Patient Record" << endl;
										cout << "2. Sort by Visit History" << endl;
										cout << "3. Back \n" << endl;
										cout << "Action: ";
										cin.clear();
										cin.ignore(123, '\n');
										cin >> option;
									}
									cout << "\n";

									switch (option) {
									case 1:			// Modify Patient Record
									{
										cout << "New Age: ";
										cin >> age;
										while (cin.fail())
										{
											cout << "\033[1;31mError! Enter again.\033[0m" << endl;
											cout << "Age: ";
											cin.clear();
											cin.ignore(123, '\n');
											cin >> age;
										}
										cout << "New Phone Number (e.g. 01(1)23456789): ";
										cin >> phone;
										while (1)//Phone Input Validation
										{
											string result = "";
											if (size(phone) < 10 || size(phone) > 11)
											{
												cout << "\033[1;31mError! Check again.\033[0m" << endl;
												cout << "Phone Number: ";
												cin.clear();
												cin.ignore(123, '\n');
												cin >> phone;
											}
											else
											{
												for (int i = 0; i < phone.length(); i++) {
													if (phone[i] == '0' || phone[i] == '1' || phone[i] == '2' || phone[i] == '3' || phone[i] == '4' || phone[i] == '5' || phone[i] == '6' || phone[i] == '7' || phone[i] == '8' || phone[i] == '9') {
														result += phone[i];
													}
												}
												if (size(result) == size(phone)) {
													phone = result;
													break;
												}
												else {
													cout << "\033[1;31mError! Check again.\033[0m" << endl;
													cout << "Phone Number: ";
													cin.clear();
													cin.ignore(123, '\n');
													cin >> phone;
												}
											}
										}
										cin.ignore();
										cout << "New Address: ";
										getline(cin, address);
										cout << "\n";

										historyList->getHistoryAt(index)->patient->age = age;
										historyList->getHistoryAt(index)->patient->phone = phone;
										historyList->getHistoryAt(index)->patient->address = address;

										if (temp != -1)
										{
											waitingList->getPatientAt(temp)->age = age;
											waitingList->getPatientAt(temp)->phone = phone;
											waitingList->getPatientAt(temp)->address = address;
										}

										cout << "\033[1;33mRecord of Patient\033[1;36m " + patientID + "\033[1;33m has been updated accordingly!\033[0m" << endl;
										cout << "\n";

										option = 0;
										break;
									}
									case 2:			// Sort by Visit History
									{
										IndexLinkedList* indexList = new IndexLinkedList();
										historyList->searchRangeID(indexList, index, patientID, 0);

										for (int i = 0; i < indexList->size; i++) {
											historyList->displaySpecific(indexList->getIndexAt(i));
										}

										delete indexList;
										option = 0;
										break;
									}
									case 3:
										break;
									default:
										cout << "\033[1;31mInvalid Option!\033[0m" << endl;
										cout << "\n";
									}
								} while (option != 1 && option != 2 && option != 3);
							}
							else
							{
								cout << "\033[1;31mPatient not found!\033[0m" << endl;
								cout << "\n";
							}

							option = 0;
							break;
						}
						case 2:			// Search Patients by Sickness
						{
							cout << "Sickness Description: ";
							cin >> search_term;
							cout << "\n";

							historyList->combSortSickness();
							index = historyList->exponentialSearchSickness(search_term);

							if (index != -1) {

								IndexLinkedList* indexList = new IndexLinkedList();
								historyList->searchRangeSickness(indexList, index, search_term);

								for (int i = 0; i < indexList->size; i++) {
									historyList->displaySpecific(indexList->getIndexAt(i));
								}

								delete indexList;
							}
							else {
								cout << "\033[1;31mInvalid Sickness!\033[0m" << endl;
								cout << "\n";
							}

							option = 0;
							break;
						}
						case 3:			// Search Patients by First Name
						{
							cout << "First Name: ";
							cin >> search_term;
							cout << "\n";

							historyList->combSortName();
							index = historyList->exponentialSearchName(search_term);

							if (index != -1) {

								IndexLinkedList* indexList = new IndexLinkedList();
								historyList->searchRangeName(indexList, index, search_term);

								for (int i = 0; i < indexList->size; i++) {
									historyList->displaySpecific(indexList->getIndexAt(i));
								}

								delete indexList;

							}
							else {
								cout << "\033[1;31mInvalid First Name!\033[0m" << endl;
								cout << "\n";
							}

							option = 0;
							break;
						}
						case 4:
							break;
						default:
							cout << "\033[1;31mInvalid Option!\033[0m" << endl;
							cout << "\n";

							option = 0;
							break;
						}
					} while (option != 1 && option != 2 && option != 3 && option != 4);

					option = 0;
					break;

				case 3:				// View Treating List
					treatingList->display(1);

					if (treatingList->head != NULL)
					{
						do {
							cout << "1. Complete Treatment" << endl;
							cout << "2. Back" << endl;
							cout << "\n";
							cout << "Action: ";
							cin >> option;

							while (cin.fail())
							{
								cout << "\n";
								cout << "\033[1;31mInvalid Option!\033[0m" << endl << endl;
								cout << "1. Complete Treatment" << endl;
								cout << "2. Back" << endl;
								cout << "\n";
								cout << "Action: ";
								cin.clear();
								cin.ignore(123, '\n');
								cin >> option;
							}
							cout << "\n";

							switch (option)
							{
							case 1:			// Complete Treatment
								cout << "Patient ID (e.g. U001): ";
								cin >> patientID;
								index = treatingList->checkExistence(patientID);
								cout << "\n";

								if (index == -1)
								{
									cout << "\033[1;31mInvalid Patient ID!\033[0m" << endl;
									cout << "\n";
								}
								else
								{
									cout << "Sickness: ";
									cin >> sickness;
									cout << "\n";

									medicineList->display();

									cout << "Medicine ID (e.g. M001): ";
									cin >> medicineID;
									cout << "\n";

									if (medicineList->checkExistence(medicineID) == -1)
									{
										cout << "\033[1;31mInvalid Medicine ID!\033[0m" << endl;
										cout << "\n";
									}
									else
									{
										temp = medicineList->checkExistence(medicineID);
										if (medicineList->getMedicineAt(temp)->quantity != 0)
										{
											treatingList->getHistoryAt(index)->medicine = medicineList->getMedicineAt(temp)->medicineName;
											treatingList->getHistoryAt(index)->sickness = sickness;
											treatingList->getHistoryAt(index)->doctor = doctorOnDuty;
											History* history = treatingList->getHistoryAt(index);
											historyList->appendHistory(history);
											treatingList->deleteAt(index);
											medicineList->getMedicineAt(temp)->quantity = (medicineList->getMedicineAt(temp)->quantity) - 1;

											cout << "\033[1;33mTreatment for Patient\033[1;36m " + patientID + "\033[1;33m has been completed!\033[0m" << endl;
											cout << "\n";
											break;
										}
										else
										{
											cout << "\033[1;31mOut of Medicine!\033[0m" << endl;
											cout << "\n";
										}
									}
								}

								option = 0;
								break;
							case 2:
								break;
							default:
								cout << "\033[1;31mInvalid Option!\033[0m" << endl;
								cout << "\n";
							}
						} while (option != 1 && option != 2);
					}

					option = 0;
					break;
				case 4:
					loginAsDoctor = 0;
					clearTerminal();
					break;
				default:
					cout << "\033[1;31mInvalid Option!\033[0m" << endl;
					cout << "\n";
				}
			} while (option != 1 && option != 2 && option != 3 && option != 4 );

			break;
		case 3:
			cout << "\033[1;92mYou are successfully exit the system.\033[0m" << endl;
			return 0;
		default:
			cout << "\033[1;31mInvalid Option!\033[0m" << endl;
		}
	} while (option != 1 && option != 2 && option != 3);

	return 0;
};