#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "header.h";
#include "header1.h";

student::student() {
	name = " ";
	surname = " ";
	date.day = 0;
	date.mounth = 0;
	date.year = 0;
	group_number = 0;
	phone_number = 0;
}

student::student(const string& first, const string& last_name, Date  date, int  group_number, int  phone_number) {
	this->name = first;
	this->surname = last_name;
	this->date = date;
	this->group_number = group_number;
	this->phone_number = phone_number;
}


group::group(const string& path) {
	int answer;
	do {
		this->n = amount(path);
		this->s = new student[n + this->step];
		answer = intro1();
		switch (answer) {
		case 1: {
			adding(path);
			ShowAllStudents(); break; }
		case 2: {
			string   Name, Surname;
			Date date;
			int  group_number, phone_number;
			adding(path);
			int answer2 = intro2();
			switch (answer2) {
			case 1: {
				cout << "Enter the name of the student to be searched for:";
				cin >> Name;
				int* a = SearchByName(Name);
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < sizeof(a); j++)
						if (i == a[j]) {
							cout << s[i];
						}
				}
				break;
			}
			case 2: {
				cout << "Enter the surname of the student to be searched for:";
				cin >> Surname;
				int a = SearchBySurname(Surname);
				cout << s[a];
				break;
			}
			case 3: {
				cout << "enter the student's birthday:";
				cin >> date.day;
				cout << "Enter the student's month of birth:";
				cin >> date.mounth;
				cout << "Enter the student's year of birth:";
				cin >> date.year;
				int a = SearchByDate(date);
				cout << s[a];
				break;
			}
			case 4: {
				cout << "Enter the number of group of the student to be searched for:";
				cin >> group_number;
				int* a = SearchByGroup(group_number);
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < sizeof(a); j++)
						if (i == a[j]) {
							cout << s[i];
						}
				}
				break; }
			case 5: { 
				cout << "Enter the number of phone of the student to be searched for:";
				cin >> phone_number;
				int a = SearchByPhone(phone_number);
				cout << s[a];
				break;   }
			}
			break;
		}
		case 3: {AddStudent(path); break; }
		case 4: {
			adding(path);
			RemoveStudent(path); break; }
		}
	} while (answer != 0);
}


group::~group() {
	delete[] this->s;
}
