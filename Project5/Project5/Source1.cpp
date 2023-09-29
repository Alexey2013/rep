#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "header.h";

int* group::SearchByName() {
	string Name;
	int j = 0;
	int* mas = new int[n];
	cout << "Enter the name of the student to be searched for:";
	cin >> Name;
	for (int i = 0; i < n; i++) {
		if (s[i].get_name() == Name) {
			mas[j] = i;
			j++;
		}
	}
	return mas;
}

int group::SearchBySurname() {
	string Surname;
	cout << "Enter the surname of the student to be searched for:";
	cin >> Surname;
	for (int i = 0; i < n; i++) {
		if (s[i].get_surname() == Surname) {
			return i;
		}
	}
	throw("No such students found");
}

int group::SearchByDate() {
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
			return i;
		}
	}
	throw("No such students found");
}

int* group::SearchByGroup() {
	int group;
	int j = 0;
	int* mas = new int[n];
	cout << "Enter the number of group of the student to be searched for:";
	cin >> group;
	for (int i = 0; i < n; i++) {
		if (s[i].get_group() == group) {
			mas[j] = i;
			j++;
		}
	}
	return mas;
}

int group::SearchByPhone() {
	int phone;
	int counter = 0;
	cout << "Enter the number of phone of the student to be searched for:";
	cin >> phone;
	for (int i = 0; i < n; i++) {
		if (s[i].get_phone() == phone) {
			return i;
		}
	}
	throw("No such students found");
}
