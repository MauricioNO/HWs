// Mauricio Nunes de Oliveira
// ITP 365, Spring 2015
// Assignment 4
// nunesdeo@usc.edu
// Platform: Windows

#pragma once
#include "map.h"
#include "vector.h"
using std::string;

class Professor{

private:
	string name, ID;
    
	Map<int, Vector<int>* > courses;	// Int is the course number, the vector holds all the sections that the professor teaches that course

public:
	//Default Constructor
	Professor();

	//Parameterized Constructor
	//Sets name, course and section
	Professor(string p_name, string p_ID, int course, int section);

	//Function: displayProfessor
	//Purpose: Displays a professor and all the information associated with it
	//Input: none
	//Output: none
	void displayProfessor();

	//Function: addCourses
	//Purpose: Adds a course to the professor info
	//Input: Course and section to add
	//Output: none
	void addCourses(int course, int section);

	//Function: getName
	//Purpose: Get the professor name
	//Input: none
	//Output: String containing the professor name
	string getName();

	//Destructor
    ~Professor();



};
