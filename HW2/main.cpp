// ITP 365 Spring 2015
// HW2 – ITP Phone
// Name: Mauricio Nunes de Oliveira
// Email: nunesdeo@usc.edu
// Platform: Windows

#include <iostream>
#include <string>
#include "PhoneSystem.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char** argv)
{
	PhoneSystem myPhoneSystem;

	string request = "";
	
	while (request != "0")	//Will run until user requests to quit: '0'
	{	
		cout << "Type 1 to enter a phone number or 0 to exit" << endl;
		cin >> request;

		if (request == "1")
		{
			string phone = myPhoneSystem.GetPhoneNumber();
			while (phone.empty())	//GetPhoneNumber returns "" if the input is not valid
			{
				cout << "Invalid phone number!" << endl;
				phone = myPhoneSystem.GetPhoneNumber();
			}
			string output = myPhoneSystem.lookUp(phone);
			cout << output << endl;		//Program output, either contact name, area or UNKOWN
		}
		else if (request == "0")
		{
			break;
		}
		else
		{
			system("cls");
			cout << "Invalid input, please try again" << endl;
		}
	}



	return 0;
}

