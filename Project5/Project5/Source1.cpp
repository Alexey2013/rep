#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "header.h";


void group::SearchByName() {
	string Name;
	int counter = 0;
	cout << "Enter the name of the student to be searched for:";
	cin >> Name;
	for (int i = 0; i < n; i++) {
		if (s[i].get_name() == Name) {
			cout << s[i];
			counter++;
		}
	}
	if (counter == 0) { cout << "There are no people with this name in the database" << endl; }
}

int group::SearchBySurname() {
	string Surname;
	cout << "Enter the surname of the student to be searched for:";
	cin >> Surname;
	for (int i = 0; i < n; i++) {
		if (s[i].get_surname() == Surname) {
			cout << s[i];
			return i;
		}
	}
	cout << "There are no people with this surname in the database" << endl;
	return -1;
}

void group::SearchByDate() {
	Date date;
	Date date2;
	int counter = 0;
	cout << "enter the student's birthday:";
	cin >> date.day;
	cout << "Enter the student's month of birth:";
	cin >> date.mounth;
	cout << "Enter the student's year of birth:";
	cin >> date.year;
	for (int i = 0; i < n; i++) {
		date2 = s[i].get_date();
		if ((date2.day == date.day) && (date2.mounth == date.mounth) && (date2.year == date.year)) {
			cout << s[i];
			counter++;
		}
	}
	if (counter == 0) { cout << "There are no people with this name in the database" << endl; }
}

void group::SearchByGroup() {
	int group;
	int counter = 0;
	cout << "Enter the number of group of the student to be searched for:";
	cin >> group;
	for (int i = 0; i < n; i++) {
		if (s[i].get_group() == group) {
			cout << s[i];
			counter++;
		}
	}
	if (counter == 0) { cout << "There are no people with this number of group in the database" << endl; }
}

void group::SearchByPhone() {
	int phone;
	int counter = 0;
	cout << "Enter the number of phone of the student to be searched for:";
	cin >> phone;
	for (int i = 0; i < n; i++) {
		if (s[i].get_phone() == phone) {
			cout << s[i];
			counter++;
		}
	}
	if (counter == 0) { cout << "There are no people with this number of phone in the database" << endl; }
}