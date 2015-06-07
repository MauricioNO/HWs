// Mauricio Nunes de Oliveira
// ITP 365, Spring 2015
// Assignment 4
// nunesdeo@usc.edu
// Platform: Windows

#include "gwindow.h"
#include "map.h"
#include "Professor.h"
#include "Student.h"
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::stoi;

//Function: PopulateProf/Stud
//Purpose: Populate the professors and students map
//Input: fileName to read info from and Map to modify(by reference)
//Output: none
void populateProf(string fileName, Map<int, Professor*>& professors);
void populateStud(string fileName, Map<int, Student*>& students);

int main(int argc, char** argv)
{
	cout << "Welcome to Blackboard!" << endl;
	//Populate professor map
	Map<int, Professor*> professors;	//Key is professor ID and value is pointer to professor object
	populateProf("professordata.txt", professors);

	//populate Students map
	Map<int, Student*> students;	//Key is the student ID(7 digit) and value is pointer to student object
	populateStud("studentdata.txt", students);


	int menu = 0;
	while (menu != 6)
	{
		cout << "Menu:\n1)Professors info\n2)Students info\n3)Professor list\n4)Student list\n6)Quit" << endl;
		cin >> menu;
	
		if (menu == 1)
		{
			for (int index : professors)
				professors.get(index)->displayProfessor();
			
		}
		else if (menu == 2)
		{
			for (int index : students)
				students.get(index)->displayStudent();
		}

		else if (menu == 3)
		{
			int submenu = 0;
			int index = 1;
			while (submenu == 0)
			{
				for (int key : professors.keys())
				{
					cout << index << ")" + professors.get(key)->getName() + "\n" << endl;
					index++;
				}
				cout << "Choose a professor to obtain more information: " << endl;
				cin >> submenu;

				if (submenu >= index || submenu <= 0)
				{
					cout << "Invalid option, please try again" << endl;
					index = 1;
					submenu = 0;
				}
				else // Valid choice, display professor info
				{
					//cout << professors.keys().get(submenu - 1) << endl;
					// the inside get returns a professor ID(as seen above), the outside gets its pointer to call display function
					professors.get(professors.keys().get(submenu-1))->displayProfessor();	//CHANGE THIS PLEASE
					
				}
				
			}
			
		}

		else if (menu == 4)
		{
			int submenu = 0;
			int index = 1;
			while (submenu == 0)
			{
				for (int key : students.keys())
				{
					cout << index << ")" + students.get(key)->getName() + "\n" << endl;
					index++;
				}
				cout << "Choose a student to obtain more information: " << endl;
				cin >> submenu;

				if (submenu >= index || submenu <= 0)
				{
					cout << "Invalid option, please try again" << endl;
					index = 1;
					submenu = 0;
				}
				else // Valid choice, display student info
				{
					//cout << student.keys().get(submenu - 1) << endl;
					// the inside get returns a student ID(as seen above), the outside gets its pointer to call display function
					students.get(students.keys().get(submenu - 1))->displayStudent();	//CHANGE THIS PLEASE

				}

			}
		}

		else if (menu == 6)
		{
			cout << "Goodbye!" << endl;
		}
		else
		{
			cout << "Invalid option" << endl;
		}

	}
	return 0;
}

void populateProf(string fileName, Map<int, Professor*>& professors)
{
	std::ifstream professorFile(fileName);
	if (professorFile.is_open())	//Check if the file loaded successfully
	{
		string name, line, str_section, str_ID;
		int ID, course;
		int section;

		
		while (!professorFile.eof())	// Will read until all lines of the file have been read
		{
			section = {};
			getline(professorFile, name);	//First line gets name
			getline(professorFile, str_ID);	//Second line gets ID as string
			ID = stoi(str_ID);				//Make ID an int
			getline(professorFile, line);	//Third line gets course and section
			course = stoi(line.substr(0, 3));	//get course
			str_section = line.substr(4);
			section = (stoi(str_section));	//Get section

			if (professors.containsKey(ID))	//If the professor has already been created
			{
				// Just add the new course/section
				professors.get(ID)->addCourses(course, section);
			}
			else
			{
				Professor* profPtr = new Professor(name, str_ID, course, section);
				professors.put(ID, profPtr);
			}
		}
		professorFile.close();
	}
	else
	{
		error("Failed to load file!");
	}
}
void populateStud(string fileName, Map<int, Student*>& students)
{
	std::ifstream studentFile(fileName);
	if (studentFile.is_open())	//Check if the file loaded successfully
	{
		string name, line, section, course, str_ID;
		std::istringstream str_grades;

		int ID;
		Vector<int> grades;


		while (!studentFile.eof())	// Will read until all lines of the file have been read
		{
			grades = {};
			str_grades.clear();
			getline(studentFile, name);	//First line gets name
			getline(studentFile, str_ID);	//Second line gets ID as string
			ID = stoi(str_ID);				//Make ID an int
			getline(studentFile, line);	//Third line gets course and section

			course = line.substr(0, 3);
			section = line.substr(4);
			string compositeKey = course + " " + section;
			getline(studentFile, line);		//Get grades
			str_grades.str(line);
			while (!str_grades.eof())	//Puts grades as integers in vector grades
			{
				int x;
				str_grades >> x;
				grades.push_back(x);
			}

			if (students.containsKey(ID))	//If the student has already been created
			{
				//Just add the new course and its grades
				
				students.get(ID)->addCourses(compositeKey, grades);
			}
			else
			{
				Student* stuPtr = new Student(name, str_ID, compositeKey, grades);
				students.put(ID, stuPtr);
			}


		}
		studentFile.close();
	}
	else
	{
		error("Failed to load file!");
	}
}
