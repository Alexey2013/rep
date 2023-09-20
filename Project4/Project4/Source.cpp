#define _CRT_SECURE_NO_WARNINGS
#include  "header.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
using namespace std;

Tvector::Tvector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Tvector::Tvector(double X, double Y, double Z) {
    this->x = X;
    this->y = Y;
    this->z = Z;
}

Tvector Tvector::operator+(const Tvector& v) {
    return Tvector(this->x + v.x, this->y + v.y, this->z + v.z);
}

Tvector Tvector::operator -(const Tvector& v) {
    return Tvector(this->x - v.x, this->y - v.y, this->z - v.z);
}

const Tvector& Tvector:: operator =(const Tvector& v) {
    if (this==&v) {
        return (*this);
    }
    x = v.x;
    y = v.y;
     z = v.z;
     return(*this);
}

double Tvector::operator *(const Tvector& v) const {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}

double Tvector::cos(const Tvector& b) const {
    Tvector a(this->x, this->y, this->z);
    if((a.get_length()==0)||(b.get_length() == 0))
    {return 0; }
    return(a * b / (a.get_length() * b.get_length()));
}

double Tvector::get_length() const {
    return sqrt(x * x + y * y + z * z);
}

void intro() {
    cout << "MENU:" << endl;
    cout << "1. Get vector addition." << endl;
    cout << "2. Get the vector difference." << endl;
    cout << "3. Get the scalar product of vectors." << endl;
    cout << "4. Get the length of the vector." << endl;
    cout << "5. Get the cosine value of the angle between these vectors." << endl;
    cout << "6. Exit the program." << endl;
    cout << "Your answer:";
}

void  menu() {
    Tvector v1;
    Tvector v2;
    int answer;
    do {
        intro();
        cin >> answer;
        if (answer != 6) {
            cout << "First vector:" << endl;
            cin >> v1;
            cout << "Second vector:" << endl;
            cin >> v2;
            switch (answer) {
            case 1: {cout << "Addition: " << v1 + v2; break; }
            case 2: {cout << "Difference:" << v1 - v2; break; }
            case 3: {cout << "Scalar product:" << v1 * v2 << endl; break; }
            case 4: {cout << "Length of the first vector:" << v1.get_length() << endl
                << "Length of the second vector:" << v2.get_length() << endl;
                break; }
            case 5: {cout << "Cosine value of the angle:" << v1.cos(v2) << endl; break; }
            }
        }
    } while (answer != 6);
}

istream& operator>>(istream& in, Tvector& v)
{
    cout << "Enter x coordinates:" << endl;
    in >> v.x;
    cout << "Enter y coordinates:" << endl;
    in >> v.y;
    cout << "Enter z coordinates:" << endl;
    in >> v.z;
    return in;
}

ostream& operator<<(ostream& out, const Tvector& v) 
{
    out << v.x << " " << v.y << " " << v.z << endl;
    return out;
}

