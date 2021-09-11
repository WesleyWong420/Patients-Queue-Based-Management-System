# Patients-Queue-Based-Management-System

Klinik Sulaiman

Nurses:
  - 1.1 Add a new patient on the waiting list.
  - 1.2 Change the patient order according to the priority on the waiting list. (For example, the disabled will meet the doctor first)
  - 1.3 View all patients on the original waiting list. Viewing mode: full list in single page
  - 1.4 Calling the patient to be treated. Automatically remove the patient from the waiting list and store in the patient’s visit history list
  - 1.5 Search patient from the waiting list based on Patient ID or First Name
  - 1.6 Sort the waiting list by patient's current visit time, display in ascending order. Viewing mode: page-by-page browsing that can move forward and backward
  - 1.7 Login / Logout

Doctors:
  - 2.1 View all patients on the original waiting list. Viewing mode: full list in single page
  - 2.2 Search Specific Patient from the patient's visit history and modify patient records.
  - 2.3 Sort and display all records from the patient's visit history list in descending order. Viewing mode: page-by-page browsing that can move forward and backward
  - 2.4 Search patients from the patient's visit history list based on sickness description or first name
  - 2.5 Login / Logout

Attributes:

Patient ID, First Name, Last Name, Age, Gender, Phone, Address, Sickness Description, Current Visit Date, Current Visit Time, Disability option, Doctor Name (set default value as NULL), Medicine Information (set default value as NULL)

Proposal:

  1. Introduce your group’s members.
  2. Identify what are the important data structures or classes (optional) will be included in your system.
  - Detailed explanation of the data structures and classes created, with proper justification on your decisions (include source code defining classes, data members, and method headers only).
  3. Briefly explain all of the workflows planning for your future system.
  - Use flowchart diagram to describe each of the functionalities’ workflows.
  - Provide a brief explanation about the algorithms that you plan to use in your function
  - Provide a proper justification on your decisions.
  4. Identify and explain what are the tasks will be assigned to each of the members.

CLI Menu Flow:

Login As:

	1. Nurse
		1. Add Patient to Waiting List ✅
		2. View Waiting List ✅
			1. Search for Patient by Patient ID [Selection Sort (No Repeat)]  (New List so 1.4 dont have to sort)
			2. Search for Patient by First Name [Comb Sort (Repeat)]
			3. Sort by Visit Time [Clone WaitingList -> Comb Sort -> Display] (New List so 1.4 dont have to sort)
			4. Back ✅
		3. Edit Waiting List Priority ✅
		4. Call Patient for Treatment ✅
		5. View Medicine List ✅
			1. Search for Medicine by Medicine ID or Name ✅
			2. Search for Medicine by Medicine Name ✅
			3. Sort by Quantity ✅
			4. Edit Medicine ✅
				1. Edit Amount ✅
				2. Delete ✅
				3. Cancel ✅
			5. Add Medicine ✅
			6. Back ✅
		5. Logout ✅

	2. Doctor
		1. View Waiting List ✅
		2. View Patient List [Sort By ID]
			1. Search Specific Patient by Patient ID ✅
				1. Modify Patient Record ✅
				2. Sort by Visit History [Default]
				3. Back ✅
			2. Search Patients by Sickness or First Name [Comb Sort (Repeat)] (New List)
			3. Search Patients by First Name [Comb Sort (Repeat)] (New List)
			4. Back ✅
		3. View Treating List ✅
			1. Complete Treament ✅
			2. Back ✅
		4. Logout ✅
