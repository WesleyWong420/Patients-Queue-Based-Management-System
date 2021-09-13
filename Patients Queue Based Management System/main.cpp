#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
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

	~MedicineLinkedList() {};

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

		MedicineNode* last = head;

		for (int i = 0; i < index; i++)
		{
			if (last->nextNode != NULL) {
			last = last->nextNode;
			}
		}

		return last->currentMedicine;
	}

	void setMedicineAt(int index, Medicine* Medicine) {

		MedicineNode* last = head;

		for (int i = 0; i < index; i++)
		{
			last = last->nextNode;
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

	void selectionSortID() {

		int idx_min;

		for (int i = 0; i < getSize(); i++) {

			idx_min = i;

			for (int j = i + 1; j < getSize(); j++) {

				if (getMedicineAt(j)->medicineID < getMedicineAt(idx_min)->medicineID) {
					idx_min = j;
				}
			}

			swap(idx_min, i);
		}
	}

	void selectionSortName() {

		int idx_min;
		string min;

		for (int i = 0; i < getSize() - 1; i++) {

			idx_min = i;
			min = getMedicineAt(i)->medicineName;

			for (int j = i + 1; j < getSize(); j++) {

				if (getMedicineAt(j)->medicineName < min)
				{
					idx_min = j;
					min = getMedicineAt(j)->medicineName;
				}
			}

			swap(i, idx_min);
		}
	}

	void selectionSortQuantity() {

		int idx_min;

		for (int i = 0; i < getSize(); i++) {

			idx_min = i;

			for (int j = i + 1; j < getSize(); j++) {

				if (getMedicineAt(j)->quantity < getMedicineAt(idx_min)->quantity) {
					idx_min = j;
				}
			}

			swap(idx_min, i);
		}
	}

	int binarySearchID(int j, int k, string x) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getMedicineAt(mid)->medicineID == x) {
			return mid;
		}
		else if (getMedicineAt(mid)->medicineID > x) {
			return binarySearchID(j, mid - 1, x);
		}
		else {
			return binarySearchID(mid + 1, k, x);
		}
	}

	int binarySearchName(int j, int k, string x) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getMedicineAt(mid)->medicineName == x) {
			return mid;
		}
		else if (getMedicineAt(mid)->medicineName > x) {
			return binarySearchName(j, mid - 1, x);
		}
		else {
			return binarySearchName(mid + 1, k, x);
		}
	}

	int exponentialSearchID(string x) {


		if (getMedicineAt(0)->medicineID == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getMedicineAt(i)->medicineID <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}

			return binarySearchID(i / 2, min(i, getSize()), x);
		}
	}

	int exponentialSearchName(string x) {

		if (getMedicineAt(0)->medicineName == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getMedicineAt(i)->medicineName <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}

			return binarySearchName(i / 2, min(i, getSize()), x);
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
			MedicineNode* temp = head;

			while (temp != NULL) {

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";
				cout << "\033[1;33mMedicine ID: \033[0m" << temp->currentMedicine->medicineID << "\n";
				cout << "\033[1;33mMedicine Name: \033[0m" << temp->currentMedicine->medicineName << "\n";
				cout << "\033[1;33mMedicine Quantity: \033[0m" << temp->currentMedicine->quantity << "\n";
				cout << "\n";

				temp = temp->nextNode;
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

	void appendIndexFirst(int index) {
		
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

	void appendIndexLast(int index) {

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

		IndexNode* last = head;

		for (int i = 0; i < index; i++)
		{
			if (last->nextNode != NULL) {
				last = last->nextNode;
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

	~HistoryLinkedList() {};

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

	int getSize() {

		HistoryNode* current = head;
		int size = 0;

		while (current != NULL) {
			size = size + 1;
			current = current->nextNode;
		}

		return size;
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
					cout << "                       Search Result - " + last->currentHistory->patient->UserID + "\n";
					found++;
				}

				cout << "\033[1;33m---------------------------------------------------------------\n";
				cout << "\n";

				cout << "\033[1;33mPatient ID: \033[0m" << last->currentHistory->patient->UserID << "\n";
				cout << "\033[1;33mFirst Name: \033[0m" << last->currentHistory->patient->firstName << "\n";
				cout << "\033[1;33mLast Name: \033[0m" << last->currentHistory->patient->lastName << "\n";
				cout << "\033[1;33mGender: \033[0m" << last->currentHistory->patient->gender << "\n";
				cout << "\033[1;33mAge: \033[0m" << last->currentHistory->patient->age << "\n";
				cout << "\033[1;33mPhone Number: \033[0m" << last->currentHistory->patient->phone << "\n";
				cout << "\033[1;33mAddress: \033[0m" << last->currentHistory->patient->address << "\n";
				cout << "\033[1;33mDisability Option: \033[0m" << last->currentHistory->patient->disability << "\n";
				cout << "\033[1;33mPriority: \033[0m" << last->currentHistory->patient->priority << "\n";
				cout << "\033[1;33mVisit Date: \033[0m" << last->currentHistory->visitDate << "\n";
				cout << "\033[1;33mVisit Time: \033[0m" << last->currentHistory->visitTime << "\n";
				cout << "\033[1;33mSickness Description: \033[0m" << last->currentHistory->sickness << "\n";

				if (last->currentHistory->doctor != NULL && last->currentHistory->medicine != "")
				{
					cout << "\033[1;33mDoctor Assigned: \033[0m" << last->currentHistory->doctor->doctorName << "\n";
					cout << "\033[1;33mMedicine Prescription: \033[0m" << last->currentHistory->medicine << "\n";
				}

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

	void insertionSortID() {

		int j;
		string key;

		for (int i = 1; i < getSize(); i++) {

			key = getHistoryAt(i)->patient->UserID;
			History* keyObj = getHistoryAt(i);
			j = i - 1;

			while (j >= 0 && key < getHistoryAt(j)->patient->UserID) {
				setHistoryAt(j + 1, getHistoryAt(j));
				j = j - 1;
			}
			while (j >= 0 && key == getHistoryAt(j)->patient->UserID) {
				if (dateToDay(getHistoryAt(i)->visitDate) < dateToDay(getHistoryAt(j)->visitDate)) {
					setHistoryAt(j + 1, getHistoryAt(j));
					j = j - 1;
				}
				else if (dateToDay(getHistoryAt(i)->visitDate) == dateToDay(getHistoryAt(j)->visitDate)) {
					if (timeToSecond(getHistoryAt(i)->visitTime) < timeToSecond(getHistoryAt(j)->visitTime)) {
						setHistoryAt(j + 1, getHistoryAt(j));
						j = j - 1;
					}
				}
			}

			setHistoryAt(j + 1, keyObj);
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

	int binarySearchSickness(int j, int k, string x) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getHistoryAt(mid)->sickness == x) {
			return mid;
		}
		else if (getHistoryAt(mid)->sickness > x) {
			return binarySearchSickness(j, mid - 1, x);
		}
		else {
			return binarySearchSickness(mid + 1, k, x);
		}
	}

	int exponentialSearchSickness(string x) {

		if (getHistoryAt(0)->sickness == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getHistoryAt(i)->sickness <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}

			return binarySearchSickness(i / 2, min(i, getSize()), x);
		}
	}

	int binarySearchName(int j, int k, string x) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getHistoryAt(mid)->patient->firstName == x) {
			return mid;
		}
		else if (getHistoryAt(mid)->patient->firstName > x) {
			return binarySearchName(j, mid - 1, x);
		}
		else {
			return binarySearchName(mid + 1, k, x);
		}
	}

	int exponentialSearchName(string x) {

		if (getHistoryAt(0)->patient->firstName == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getHistoryAt(i)->patient->firstName <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}
			return binarySearchName(i / 2, min(i, getSize()), x); 
		}
	}

	int binarySearchID(int j, int k, string x) {

		if (j > k) { 
			return -1;
			
		}

		int mid = j + (k - j) / 2;

		if (getHistoryAt(mid)->patient->UserID == x) {
			return mid;
		}
		else if (getHistoryAt(mid)->patient->UserID > x) {
			return binarySearchID(j, mid - 1, x);
		}
		else {
			return binarySearchID(mid + 1, k, x);
		}
	}

	int exponentialSearchID(string x) {

		if (getHistoryAt(0)->patient->UserID == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getHistoryAt(i)->patient->UserID <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}

			return binarySearchID(i / 2, min(i, getSize()), x);
		}
	}

	void searchRangeName(IndexLinkedList* indexList, int index, string search_term){

		indexList->appendIndexFirst(index);
		cout << index;
		int i = 1;
		if (index < getSize()) { //waitinglist search name fix
			while (search_term == getHistoryAt(index + i)->patient->firstName) {
					indexList->appendIndexLast(index + i);
					i = i + 1;
					if (index+i >= getSize()) {//waitinglist search name fix
						break;
					}
			}		
		}

		i = 1;

		while (search_term == getHistoryAt(index - i)->patient->firstName) {

			if (index == -1) {
				break;
			}
			indexList->appendIndexFirst(index - i);
			i = i - 1;
			}
	}

	void searchRangeSickness(IndexLinkedList* indexList, int index, string search_term) {

		indexList->appendIndexFirst(index);
		int i = 1;

		if (index < getSize()) { //waitinglist search name fix
			while (search_term == getHistoryAt(index + i)->sickness) {
				indexList->appendIndexLast(index + i);
				i = i + 1;
				if (index + i >= getSize()) {//waitinglist search name fix
					break;
				}
			}
		}

		i = 1;

		while (search_term == getHistoryAt(index - i)->sickness) {

			if (index == -1) {
				break;
			}
			indexList->appendIndexFirst(index - i);
			i = i + 1;
		}
	}

	void searchRangeID(IndexLinkedList* indexList, int index, string search_term) {

		indexList->appendIndexFirst(index);
		int i = 1;

		if (index < indexList->size) {

			while (search_term == getHistoryAt(index + i)->patient->UserID) {
				indexList->appendIndexLast(index + i);
				i = i + 1;
				if (index + i >= indexList->size) {
					break;
				}
			}
		}

		i = 1;

		while (search_term == getHistoryAt(index - i)->patient->UserID) {

			if (index == -1) {
				break;
			}
			indexList->appendIndexFirst(index - i);
			i = i + 1;
		}
	}

	void displaySpecific(int index) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                       Search Result - " + getHistoryAt(index)->patient->UserID + "\n";
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
		cout << "                       Search Result - " + getHistoryAt(index)->patient->UserID + "\n";
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

	void display(int listNumber) {

		cout << "\033[1;33m---------------------------------------------------------------\n";

		if(listNumber == 0)
		{
			cout << "                       Patient List                       \n";
		}
		else if(listNumber == 1)
		{
			cout << "                       Treating List                       \n";
		}
		else if (listNumber == 2)
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

				if (temp->currentHistory->sickness != "" && temp->currentHistory->doctor != NULL && temp->currentHistory->medicine != "")
				{
					cout << "\033[1;33mSickness Description: \033[0m" << temp->currentHistory->sickness << "\n";
					cout << "\033[1;33mDoctor Assigned: \033[0m" << temp->currentHistory->doctor->doctorName << "\n";
					cout << "\033[1;33mMedicine Prescription: \033[0m" << temp->currentHistory->medicine << "\n";
				}
				else
				{
					if (listNumber != 2)
					{
						cout << "\033[1;33mSickness Description: " << "\033[1;31mTBD\033[0m" << "\n";
						cout << "\033[1;33mDoctor Assigned: " << "\033[1;31mTBD\033[0m" << "\n";
						cout << "\033[1;33mMedicine Prescription: " << "\033[1;31mTBD\033[0m" << "\n";
					}
				}

				cout << "\n";

				temp = temp->nextNode;
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

	~PatientLinkedList() {};

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

	/*int binarySearchID(int j, int k, string x) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getPatientAt(mid)->UserID == x) {
			return mid;
		}
		else if (getPatientAt(mid)->UserID > x) {
			return binarySearchID(j, mid - 1, x);
		}
		else {
			return binarySearchID(mid + 1, k, x);
		}
	}*/

	/*int exponentialSearchID(string x) {

		if (getPatientAt(0)->UserID == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getPatientAt(i)->UserID <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}

			return binarySearchID(i / 2, min(i, getSize()), x);
		}
	}*/

	/*int binarySearchName(int j, int k, string x) {

		if (j > k) {
			return -1;
		}

		int mid = j + (k - j) / 2;

		if (getPatientAt(mid)->firstName == x) {
			return mid;
		}
		else if (getPatientAt(mid)->firstName > x) {
			return binarySearchName(j, mid - 1, x);
		}
		else {
			return binarySearchName(mid + 1, k, x);
		}
	}*/

	/*int exponentialSearchName(string x) {

		if (getPatientAt(0)->firstName == x) {
			return 0;
		}
		else {
			int i = 1;

			while (i < getSize() && getPatientAt(i)->firstName <= x) {
				i = i * 2;
				if (i > getSize()) {
					break;
				}
			}

			return binarySearchName(i / 2, min(i, getSize()), x);
		}
	}*/

	void display(HistoryLinkedList* tempHistory, int index2) {

		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "                       Search Result - " + getPatientAt(index2)->UserID + "\n";
		cout << "\033[1;33m---------------------------------------------------------------\n";
		cout << "\n";

		cout << "\033[1;33mPatient ID: \033[0m" << getPatientAt(index2)->UserID << "\n";
		cout << "\033[1;33mFirst Name: \033[0m" << getPatientAt(index2)->firstName << "\n";
		cout << "\033[1;33mLast Name: \033[0m" << getPatientAt(index2)->lastName << "\n";
		cout << "\033[1;33mGender: \033[0m" << getPatientAt(index2)->gender << "\n";
		cout << "\033[1;33mAge: \033[0m" << getPatientAt(index2)->age << "\n";
		cout << "\033[1;33mPhone Number: \033[0m" << getPatientAt(index2)->phone << "\n";
		cout << "\033[1;33mAddress: \033[0m" << getPatientAt(index2)->address << "\n";
		cout << "\033[1;33mDisability Option: \033[0m" << getPatientAt(index2)->disability << "\n";
		cout << "\033[1;33mPriority: \033[0m" << getPatientAt(index2)->priority << "\n";

		int index = tempHistory->checkExistence(getPatientAt(index2)->UserID);
		History* history = tempHistory->getHistoryAt(index);

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

				int index = tempHistory->checkExistence(temp->currentPatient->UserID);
				History* history = tempHistory->getHistoryAt(index);

				cout << "\033[1;33mVisit Date: \033[0m" << history->visitDate << "\n";
				cout << "\033[1;33mVisit Time: \033[0m" << history->visitTime << "\n";
				cout << "\n";

				temp = temp->nextNode;
			}
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

	PatientLinkedList* waitingList = new PatientLinkedList();
	HistoryLinkedList* historyList = new HistoryLinkedList();
	HistoryLinkedList* tempHistory = new HistoryLinkedList();
	HistoryLinkedList* treatingList = new HistoryLinkedList();
	MedicineLinkedList* medicineList = new MedicineLinkedList();

	Patient* patient1 = new Patient("U001", "alex", "A", "Male", 17, "0123456789", "Street 1", "false");
	Patient* patient2 = new Patient("U002", "bob", "B", "Male", 23, "0123456789", "Street 2", "false");
	Patient* patient3 = new Patient("U003", "caitlin", "C", "Female", 21, "0123456789", "Street 3", "true");
	Patient* patient4 = new Patient("U004", "Daniel", "D", "Male", 25, "0135123411", "Street 4", "false");

	Doctor* doctor1 = new Doctor("Dr Nick");

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

	History* treating1 = new History("10/09/2021", "11:05:33", patient4);

	History* history1 = new History("21/05/2021", "11:05:33", "Vomit", "Antibiotics", patient1, doctor1);
	History* history2 = new History("10/08/2021", "09:30:55", "Fever", "Vicodin", patient2, doctor1);
	History* history3 = new History("31/08/2021", "14:55:06", "Headache", "Simvastatin", patient3, doctor1);

	//waitingList->appendPatient(patient1);
	//waitingList->appendPatient(patient2);
	//waitingList->appendPatient(patient3);

	historyList->appendHistory(history1);
	historyList->appendHistory(history2);
	historyList->appendHistory(history3);

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

	treatingList->appendHistory(treating1);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	string patientID, firstName, lastName, gender, phone, address, sickness, disability;
	int age, priority;

	string search_term, firstVisit, medicineID, medicineName;
	int option, index, temp, medicineAmount;
	int totalPatient = 4;
	int totalMedicine = 11;

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
				cout << "5. View Medicine List" << endl;
				cout << "6. Logout \n" << endl;
				cout << "Action: ";
				cin >> option;
				cout << "\n";

				switch (option) {
				case 1:				// Add Patient to Waiting List
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
						cout << "\n";

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

						Patient* newPatient = new Patient(patientID, firstName, lastName, gender, age, phone, address, disability);
						waitingList->appendPatient(newPatient);
						History* currentVisit = new History(getCurrentDate(), getCurrentTime(), newPatient);
						tempHistory->appendHistory(currentVisit);

						cout << "\033[1;33mNew Record of Patient\033[1;36m " + patientID + "\033[1;33m has been saved!\033[0m" << endl;
						cout << "\n";
						cout << "\033[1;33mPatient\033[1;36m " + patientID + "\033[1;33m has been added to waiting list!\033[0m" << endl;
						cout << "\n";
					}
					else
					{
						cout << "Patient ID: ";
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

					option = 0;
					break;
				}
				case 2:				// View Waiting List
					waitingList->display(tempHistory);

					do
					{
						cout << "1. Search for Patient by Patient ID"  << endl;
						cout << "2. Search for Patient by First Name" << endl;
						cout << "3. Sort by Visit Time" << endl;
						cout << "4. Back \n" << endl;
						cout << "Action: ";
						cin >> option;
						cout << "\n";

						switch (option) {
						case 1:
							cout << "Patient ID: ";
							cin >> search_term;
							cout << "\n";

							tempHistory->insertionSortID();
							tempHistory->display(2); //test
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
							tempHistory->display(2);
							// need to sort by visitTime

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
				case 3:				// Edit Waiting List Priority
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
					cout << "Patient ID: ";
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
						cout << "\033[1;31mPatient\033[1;36m " + patientID + "\033[1;31m is\033[1;36m " + to_string(index + 1) + "\033[1;31m place away from being called!\033[0m" << endl;
						cout << "\n";
					}

					option = 0;
					break;
				}
				case 5:				// View Medicine List
					medicineList->selectionSortID();
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
						cout << "\n";

						switch (option) {
						case 1:					// Search for Medicine by Medicine
							cout << "Medicine ID: ";
							cin >> search_term;
							cout << "\n";

							medicineList->selectionSortID();

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

							medicineList->selectionSortName();

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
							medicineList->selectionSortQuantity();
							medicineList->display();	

							option = 0;
							break;
						case 4:					// Edit Medicine
							medicineList->selectionSortID();
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
					clear();
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
				printHeader();
				cout << "\033[1;32mLogged in as Doctor\033[0m\n" << endl;
				cout << "1. View Waiting List" << endl;
				cout << "2. View Patient List" << endl;
				cout << "3. View Treating List" << endl;
				cout << "4. Logout \n" << endl;
				cout << "Action: ";
				cin >> option;
				cout << "\n";

				switch (option) {
				case 1:				// View Waiting List
					waitingList->display(tempHistory);

					option = 0;
					break;
				case 2:				// View Patient List
					historyList->insertionSortID();
					historyList->display(0);

					do
					{
						cout << "1. Search Specific Patient by Patient ID" << endl;
						cout << "2. Search Patients by Sickness" << endl;
						cout << "3. Search Patients by First Name" << endl;
						cout << "4. Back \n" << endl;
						cout << "Action: ";
						cin >> option;
						cout << "\n";

						switch (option) {
						case 1:			// Search Specific Patient by Patient ID
							cout << "Patient ID: ";
							cin >> patientID;

							index = historyList->checkExistence(patientID);
							temp = waitingList->checkExistence(patientID);
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
									case 1:			// Modify Patient Record
										cout << "New Age: ";
										cin >> age;
										cout << "New Phone Number: ";
										cin >> phone;
										cout << "New Address: ";
										cin >> address;
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
									case 2:			// Sort by Visit History
										index = historyList->exponentialSearchID(patientID);

										if (index != -1) {

											IndexLinkedList* indexList = new IndexLinkedList();
											historyList->searchRangeID(indexList, index, search_term);

											for (int i = 0; i < indexList->size; i++) {
												historyList->displaySpecific(indexList->getIndexAt(i));
											}

											delete indexList;
										}
										else {
											cout << "\033[1;31mInvalid PatientID!\033[0m" << endl;
											cout << "\n";
										}

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
						case 2:			// Search Patients by Sickness
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

						case 3:			// Search Patients by First Name
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

					do {
						cout << "1. Complete Treatment" << endl;
						cout << "2. Back" << endl;
						cout << "\n";
						cout << "Action: ";
						cin >> option;
						cout << "\n";

						switch (option)
						{
						case 1:			// Complete Treatment
							cout << "Patient ID: ";
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

								cout << "Medicine ID: ";
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
										treatingList->getHistoryAt(index)->doctor = doctor1;
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

					option = 0;
					break;
				case 4:
					clear();
					break;
				default:
					cout << "\033[1;31mInvalid Option!\033[0m" << endl;
					cout << "\n";
				}
			} while (option != 1 && option != 2 && option != 3 && option != 4 );

			break;
		default:
			cout << "\033[1;31mInvalid Option!\033[0m" << endl;
		}
	} while (option != 1 && option != 2);

	return 0;
}