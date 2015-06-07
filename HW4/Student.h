// Mauricio Nunes de Oliveira
// ITP 365, Spring 2015
// Assignment 4
// nunesdeo@usc.edu
// Platform: Window

#pragma once
#include "map.h"
#include "vector.h"
using std::string;

class Student{

private:
	string name, ID;
	Map<string, Vector<int>* > courses;	//Course + section(compositeKey) is key and the values are the students grades
public:
	//Default Constructor
	Student();

	//Parameterized Constructor
	//Sets name, course and grades
	Student(string s_name, string s_ID, string compositeKey, Vector<int> grades);

	//Function: displayStudent
	//Purpose: Displays a student and all the information associated with it
	//Input: none
	//Output: none
	void displayStudent();

	//Function: addCourses
	//Purpose: Adds a course to the student info
	//Input: Course and grades to add
	//Output: none
	void addCourses(string compositeKey, Vector<int> grades);

	//Function: getName
	//Purpose: Get the student name
	//Input: none
	//Output: String containing the student name
	string getName();

	//Desttructor
	~Student();
};

