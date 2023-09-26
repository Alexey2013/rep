#ifndef _HEADER_H
#define _HEADER_H
#include <string>
using namespace std;

struct Date {
	int day;
	int mounth;
	int year;
};

class student {
private:
	string  name;
	string  surname;
	Date date;
	int group_number;
	int  phone_number;
public:
	student();
	student(const string  name, const string  surname, Date  date, int  group_number, int  phone_number);
	void adding(string  _name, string  _surname, Date _date, int _group_number, int  _phone_number);
	friend ostream& operator<<(ostream& out, const student& s);
	friend istream& operator>>(istream& in, const student& s);
	string get_name() const { return name; } ;
	string get_surname() const { return surname; };
	Date get_date() const{ return date; };
	int get_group() const { return group_number; };
	int get_phone() const { return phone_number; };
};

class group {
private:
	student* s;
	int n;
	int step;
	int amount(const string& path);
public:
	group();
	~group();
	group(const string& path);
	void AddStudent(const string& path);
	void RemoveStudent(const string& path);
	int SearchBySurname();
	void SearchByName();
	void SearchByDate();
	void SearchByGroup();
	void SearchByPhone();
	void ShowAllStudents();
	void FileRewrite(const string& path);
	int  menu(const string& path);
};
int intro1();
int intro2();
string get_path();

#endif 
