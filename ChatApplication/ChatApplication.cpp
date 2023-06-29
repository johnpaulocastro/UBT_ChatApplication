// ChatApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#include "ServerInstance.h"
#include "ClientInstance.h"

int main()
{
	char _instanceType = 0;

	do {
		
		if (_instanceType != 0) cout << "You have entered an invalid option." << endl;
		cout << "Please select instance below:" << endl;
		cout << "[C]lient Instance" << endl;
		cout << "[S]erver Instance" << endl;
		cout << "Enter your answer: ";
		cin >> _instanceType;
		_instanceType = toupper(_instanceType);

	} while (_instanceType != char('C') && _instanceType != char('S'));

	if (_instanceType == char('C'))
	{
		Client();
	}

	if (_instanceType == char('S'))
	{
		Server();
	}

	return 0;
}