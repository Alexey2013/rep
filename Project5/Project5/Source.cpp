#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "header.h";

string get_path() {
	string path;
	do {
		cout << "Enter the file path:";
		cin >> path;
		ifstream in(path);
		if (!in.is_open()) {
			cout << "Ooops.....Something went wrong......" << endl;
		}
		else {
			in.close();
			return path;
		}
	} while (true);
}

int group::amount(const string& path)
{
	fstream file;
	file.open(path);
	string line;
	int count{ 0 };
	ifstream in(path);
	while (getline(in, line))
	{
		if (line != "\0") {
			count++;
		}
	}
	in.close();
	return count;
}

int intro1() {
	int answer;
	cout << "MENU:" << endl;
	cout << "1. Show all the students" << endl;
	cout << "2. Search for a student by criterion" << endl;
	cout << "3. Add a student" << endl;
	cout << "4. Delete entry" << endl;
	cout << "0. Exit the program." << endl;
	cout << "Your answer:";
	cin >> answer;
	return answer;
}

int intro2() {
	int answer;
	cout << "Criteria for searching a student:" << endl;
	cout << "1.Name" << endl;
	cout << "2.Last name" << endl;
	cout << "3.Date of Birth" << endl;
	cout << "4.Group number" << endl;
	cout << "5.Phone number" << endl;
	cout << "Your answer:";
	cin >> answer;
	return answer;
}

void group::ShowAllStudents() {
	cout << "List of all students:" << endl;
	for (int i = 0; i < n; i++) {
		cout << s[i];
	}
}

void group::AddStudent(const string& path) {
	Date date;
	string   name, last_name;
	int  group_number, phone_number;
	ofstream file;
	file.open(path, ios::app);
	cout << "Enter student name: ";
	cin >> name;
	cout << "Enter student surname: ";
	cin >> last_name;
	cout << "Enter the student's birthday:";
	cin >> date.day;
	cout << "Enter the student's month of birth:";
	cin >> date.mounth;
	cout << "Enter the student's year of birth:";
	cin >> date.year;
	cout << "Enter the number of group of the student:";
	cin >> group_number;
	cout << "Enter the number of phone of the student:";
	cin >> phone_number;
	file << endl<< name << ";" << last_name << ";" << date.day << ";" << date.mounth << ";" << date.year << ";" << group_number << ";" << phone_number << ";" << endl;
	step++;
}

void group::RemoveStudent(const string& path) {
	string Surname;
	cout << "Enter the surname of the student to be searched for:";
	cin >> Surname;
	int a = SearchBySurname(Surname);
	if(a!=0){
		for (int i = a; i < n - 1; i++) {
			s[i] = s[i+1];
		}
		n--;
		FileRewrite(path);
	}
	if (a == 0) {
	
		throw("No such students found");
	}
}

void group::FileRewrite(const string& path) {
	ofstream file;
	file.open(path);
	for (int i = 0; i < n; i++) {
		Date date = s[i].get_date();
		file << s[i].get_name() << ";" << s[i].get_surname() << ";" << date.day << ";" << date.mounth << ";" << date.year << ";" << s[i].get_group() << ";" << s[i].get_phone()<< ";" << endl;
	}
}

void student::adding(string& _name, string& _surname, Date _date, int _group_number, int  _phone_number)
{
	name = _name;
	surname = _surname;
	date = _date;
	group_number = _group_number;
	phone_number = _phone_number;
}


void group::adding(const string& path) {
	fstream file;
	Date date;
	string   name, last_name;
	int  group_number, phone_number;
	file.open(path);
	int i = 0, j = 0;
	string line, a;
	ifstream in(path);
	while (getline(in, line))
	{
		if (line == "\0") {
			continue;
		}
		stringstream ss(line);
		while (getline(ss, a, ';')) {
			switch (i) {
			case 0:
				name = a;
				break;
			case 1:
				last_name = a;
				break;
			case 2:
				date.day = stoi(a);
				break;
			case 3:
				date.mounth = stoi(a);
				break;
			case 4:
				date.year = stoi(a);
				break;
				case 5:
				group_number = stoi(a);
				break;
				case 6:
				phone_number = stoi(a);
				s[j].adding(name, last_name, date, group_number, phone_number);
				j++;
				i = -1;
				break;
			}
			i++;
		}
	}
	in.close();
}

ostream& operator<<(ostream& out, const student& s)
{
	out << s.name << " " << s.surname << " " << s.date.day << "." << s.date.mounth << "." << s.date.year << " " << s.group_number <<" "<< s.phone_number << endl;
	return out;
}

