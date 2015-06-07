// ITP 365 Spring 2015
// HW2 – ITP Phone
// Name: Mauricio Nunes de Oliveira
// Email: nunesdeo@usc.edu
// Platform: Windows

#pragma once
#include "map.h"

using std::string;



class PhoneSystem{

private:
	Map<string, string> areaCodes;
	Map<string, string> contacts;

public:
	//Prototypes

	//Function: Default constructor
	//Purpose: Loads information from 2 txt files into member variables
	//Input: none
	//Output: none
	PhoneSystem();

	//Function: lookUp
	//Purpose: look up a phone number
	//Input: Phone number(by reference)
	//Output: Name of contact(if its a known one), otherwise the location of area code, or UNKOWN
	string lookUp(string& phone);

	//Function: isValid
	//Purpose: Checks if the input is in a valid format
	//Input: string phone(by reference)
	//Output: true or false
	bool isValid(string& phone);

	//Function: GetPhoneNumber
	//Purpose: Receives input from the user
	//Input: none
	//Output: Either a string with the phone or an empty string
	string GetPhoneNumber();
};

