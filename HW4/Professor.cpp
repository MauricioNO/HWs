// Mauricio Nunes de Oliveira
// ITP 365, Spring 2015
// Assignment 4
// nunesdeo@usc.edu
// Platform: Windows

#include "Professor.h"
using std::string;
using std::cout;
using std::endl;;

Professor::Professor()
{
	//Do nothing
}

Professor::Professor(string p_name, string p_ID, int course, int section)
{
	name = p_name;
	ID = p_ID;
    Vector<int>* temp = new Vector<int>;
    temp->push_back(section);
	courses.put(course, temp);

}

Professor::~Professor()
{
    for (int key : courses.keys())
    {
        Vector<int>* temp = courses.get(key);
        delete temp;
    }
}

void Professor::displayProfessor()
{
	cout << "------------------------------------------------" << endl;
	cout << "Name: " << name << endl;
	cout << "ID: " + ID << endl;
	for (int key : courses.keys())
	{
        Vector<int>* temp = courses.get(key);
        for (int i = 0; i < temp->size(); i++)	//For the amount of courses
        {
                cout << "Course: " << key << "\nSection: " << temp->get(i) << '\n' << endl;
				
        }
		
	}
	
}

void Professor::addCourses(int course, int section)
{
	if (courses.containsKey(course))	//If already contains course, just add section
	{        
        courses.get(course)->push_back(section);     
	}
	else // Does not contain course yet
	{
        Vector<int>* temp = new Vector<int>;
        temp->push_back(section);
		courses.put(course, temp);
	}
}

string Professor::getName()
{
	return name;
}
