// Mauricio Nunes de Oliveira
// ITP 365, Spring 2015
// Assignment 4
// nunesdeo@usc.edu
// Platform: Window

#include "Student.h"
using std::string;
using std::cout;
using std::endl;;

Student::Student()
{
	// Do nothing
}

Student::Student(string s_name, string s_ID, string compositeKey, Vector<int> grades)
{
	name = s_name;
	ID = s_ID;
	Vector<int>* temp = new Vector<int>;
	temp->addAll(grades);
	courses.put(compositeKey, temp);
}

Student::~Student()		//CHECK FUNCTION
{
	for (string key : courses.keys())
	{
		Vector<int>* temp = courses.get(key);
		delete temp;
	}
}

void Student::displayStudent()
{
	cout << "------------------------------------------------" << endl;
	cout << "Name: " << name << endl;
	cout << "ID: " + ID << endl;
	for (string key : courses.keys())
	{
		
		Vector<int>* temp = courses.get(key);
		cout << "Course: " << key << "\nGrades: " << *temp << '\n' << endl;	//Use temp->get(i) to get specific grade from vector

	}

}

void Student::addCourses(string compositeKey, Vector<int> grades)
{
	Vector<int>* temp = new Vector<int>;
	temp->addAll(grades);
	courses.put(compositeKey, temp);

}

string Student::getName()
{
	return name;
}
