#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "header.h";

int* group::SearchByName(const string& Name) {
	int j = 0;
	int* mas = new int[n];
	for (int i = 0; i < n; i++) {
		if (s[i].get_name() == Name) {
			mas[j] = i;
			j++;
		}
	}
	return mas;
}

int group::SearchBySurname(const string& Surname) {
	for (int i = 0; i < n; i++) {
		if (s[i].get_surname() == Surname) {
			return i;
		}
	}
	throw("No such students found");
}

int group::SearchByDate(Date date) {
	Date date2;
	int counter = 0;
	for (int i = 0; i < n; i++) {
		date2 = s[i].get_date();
		if ((date2.day == date.day) && (date2.mounth == date.mounth) && (date2.year == date.year)) {
			return i;
		}
	}
	throw("No such students found");
}

int* group::SearchByGroup(int group) {
	int j = 0;
	int* mas = new int[n];
	for (int i = 0; i < n; i++) {
		if (s[i].get_group() == group) {
			mas[j] = i;
			j++;
		}
	}
	return mas;
}

int group::SearchByPhone(int phone) {
	int counter = 0;
	for (int i = 0; i < n; i++) {
		if (s[i].get_phone() == phone) {
			return i;
		}
	}
	throw("No such students found");
}
