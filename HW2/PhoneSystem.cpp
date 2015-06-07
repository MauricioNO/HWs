// ITP 365 Spring 2015
// HW2 – ITP Phone
// Name: Mauricio Nunes de Oliveira
// Email: nunesdeo@usc.edu
// Platform: Windows

#include "PhoneSystem.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

bool PhoneSystem::isValid(string& phone)
{
	if ((phone.length() == 12) && (phone[3] == '-') && (phone[7] == '-'))	// Checks if the input has the requested format
	{
		// Splits the phone number in 3 sections
		string sub1 = phone.substr(0, 3);
		string sub2 = phone.substr(4, 3);
		string sub3 = phone.substr(8);

		//this for loop checks if any of the individual characters if the substrings are numbers between 0 and 9
		int i;
		for (i = 0; i < sub1.length() - 1; i++)
		{
			if (!((int)sub1[i] - '0' < 10 && (int)sub2[i] - '0' < 10 && (int)sub3[i] - '0' < 10)) // If any single character os any of the substrings is not a number between 0 and 9, return false
			{
				return false;
			}
		}	//If it goes through the for loop without returning false, it means all the checked values are OK

		i++;
		if (!(sub3[i] - '0' < 10))	//Check for the last digit of sub3, which is one digit larger
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}

}

string PhoneSystem::GetPhoneNumber()
{
	string phone = "";
	cout << "Please enter a valid phone number(format XXX-XXX-XXXX): " << endl;
	cin >> phone;
	if (isValid(phone))
	{
		return phone;
	}
	else
	{
		return "";
	}
}


PhoneSystem::PhoneSystem()	// populate the maps from the txt files
{
	std::ifstream contactFile("contacts.txt");
	if (contactFile.is_open())	//Check if the file loaded successfully
	{
		while (!contactFile.eof())	// Will read until all lines of the file have been read
		{
			string line;
			std::getline(contactFile, line);
			if (line.length() <= 13 && line[3] != '-' && line[7] != '-' && line[12] != '|')	// Checks if the input has the expected format
			{
				error("Invalid data in file contacts.txt");
			}
			else
			{
				// Splits the line in two substrings, the first cointains the number(format XXX-XXX-XXXX) and the other one the rest(name of the contact)
				string phone = line.substr(0, 12);
				string name = line.substr(13);
				contacts.put(phone, name);
			}
		}
	}
	else
	{
		error("Failed to load file!");
	}
	// Area codes
	std::ifstream areaCodesFile("areacodes.txt");
	if (areaCodesFile.is_open())	//Check if the file loaded successfully
	{
		while (!areaCodesFile.eof())	// Will read until all lines of the file have been read
		{
			string line;
			std::getline(areaCodesFile, line);
			if (line.length() <= 4 && line[3] != '|')	// Checks if the input has the expected format
			{
				error("Invalid data in file areacodes.txt");
			}
			else
			{
				// Splits the line in two substrings, the first contains the code, the other on the rest(the area)
				string code = line.substr(0, 3);
				string area = line.substr(4);
				areaCodes.put(code, area);
			}
		}
	}
	else
	{
		error("Failed to load file!");
	}

	
}

string PhoneSystem::lookUp(string& phone)
{
	//If the contact exists, return its info
	if (contacts.containsKey(phone))
	{
		return contacts[phone];
	}
	//If there is no contact, return the area for the phone provided
	else if (areaCodes.containsKey(phone.substr(0,3)))
	{
		return areaCodes[phone.substr(0, 3)];
	}
	// Otherwise, return UNKOWN
	else
	{
		return "UNKOWN";
	}
}
